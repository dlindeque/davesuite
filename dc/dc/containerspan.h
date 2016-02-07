#pragma once

#include "container.h"
#include "span.h"

namespace dc
{
	struct containerspan {
		containerspan()
		{}
		containerspan(const std::shared_ptr<container> &_cntr, const span &_spn)
		: cntr(_cntr), spn(_spn)
		{}
		containerspan(std::shared_ptr<container> &&_cntr, const span &_spn)
		: cntr(std::move(_cntr)), spn(_spn)
		{}
		containerspan(const containerspan &c)
		: cntr(c.cntr), spn(c.spn)
		{}
		containerspan(containerspan &&c)
		: cntr(std::move(c.cntr)), spn(c.spn)
		{}

		std::shared_ptr<container> cntr;
		span spn;

		inline auto operator =(const containerspan &c) -> containerspan& {
            cntr = c.cntr;
            spn = c.spn;
            return *this;
        }
        inline auto operator =(containerspan &&c) -> containerspan& {
        	if (this != &c) {
        		cntr = std::move(c.cntr);
        		spn = c.spn;
        	}
        	return *this;
        }

        friend inline auto operator == (const containerspan &v1, const containerspan &v2) -> bool {
            return v1.cntr == v2.cntr && v1.spn == v2.spn;
        }
        friend inline auto operator != (const containerspan &v1, const containerspan &v2) -> bool {
            return !(v1 == v2);
        }
        friend inline auto operator <(const containerspan &v1, const containerspan &v2) -> bool {
            if (v1.cntr == v2.cntr) {
                return v1.spn < v2.spn;
            } 
            else {
                return v1.cntr < v2.cntr;
            }
        }
        friend inline auto operator >(const containerspan &v1, const containerspan &v2) -> bool {
            if (v1.cntr == v2.cntr) {
                return v1.spn > v2.spn;
            } 
            else {
                return v1.cntr > v2.cntr;
            }
        }
        friend inline auto operator <=(const containerspan &v1, const containerspan &v2) -> bool {
            return !(v1 > v2);
        }
        friend inline auto operator >=(const containerspan &v1, const containerspan &v2) -> bool {
            return !(v1 < v2);
        }
	};
}

namespace std
{
    template<> struct hash<dc::containerspan> {
        inline auto operator()(const dc::containerspan &v) const -> size_t {
            return hash<std::shared_ptr<dc::container>>()(v.cntr) + hash<dc::span>()(v.spn);
        }
    };
}