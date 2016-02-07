
#include <unordered_map>

namespace davecommon
{
	template<typename _QName, typename _Item> class symbol_table {
    public:
        class symbol {
        private:
            std::shared_ptr<container> _cntr;
            _Item _item;
        public:
            symbol(const std::shared_ptr<container> &cntr, const _Item &item)
            : _cntr(cntr), _item(item)
            { }
            symbol(const symbol &c)
            : _cntr(c.cntr()), _item(c._item)
            { }
            symbol(symbol &&c)
            : _cntr(std::move(c._cntr)), _item(std::move(c._item))
            { }
            inline auto cntr() const -> const std::shared_ptr<container>& { return _cntr; }
            inline auto item() const -> const _Item& { return _item; }
            
            inline auto operator =(const symbol &c) -> symbol& {
                _cntr = c._cntr;
                _item = c._item;
                return *this;
            }
            inline auto operator =(symbol &&c) -> symbol& {
                if (this != &c) {
                    _cntr = std::move(c._cntr);
                    _item = std::move(c._item);
                }
                return *this;
            }
        };
    private:
        std::unordered_map<_QName, symbol> _items; // fully qualified name -> symbol (container, item)
    public:
        class const_iterator {
        private:
            typedef typename std::unordered_map<_QName, symbol>::const_iterator underlying_iterator;
            underlying_iterator _i;
            underlying_iterator _end;
            bool _search_matching_item;
            
            inline auto advance_to_matching_item() -> void {
                if (!_search_matching_item) return;
            }
            
            const_iterator(const underlying_iterator &i)
            : _i(i), _search_matching_item(false)
            {}
            const_iterator(const underlying_iterator &i, const underlying_iterator &end)
            : _i(i), _end(end), _search_matching_item(true)
            {
                advance_to_matching_item();
            }
        public:
            
            inline auto operator ->() -> const symbol* {
                return &(_i->second);
            }
            
            inline auto operator++() -> const_iterator& {
                ++_i;
                advance_to_matching_item();
                return *this;
            }
            inline auto operator++(int) -> const_iterator {
                const_iterator x(*this);
                ++(*this);
                return x;
            }
            friend inline auto operator ==(const const_iterator &i1, const const_iterator &i2) -> bool {
                return i1._i == i2._i;
            }
            friend inline auto operator !=(const const_iterator &i1, const const_iterator &i2) -> bool {
                return !(i1 == i2);
            }
            
            friend symbol_table<_QName, _Item>;
        };
	public:
		inline auto find(const _QName &name, const std::vector<_QName> &search_namespaces) const -> std::pair<const_iterator, const_iterator> {
            auto f = _items.find(name);
            if (f == _items.end()) {
                // Item not found as fully qualified name - search all namespaces
                return std::pair<const_iterator, const_iterator>(const_iterator(f, _items.end()), const_iterator(_items.end()));
            } else {
                // Item matched exactly
                return std::pair<const_iterator, const_iterator>(const_iterator(f), const_iterator(_items.end()));
            }
		}
	};
}