//
//  smcpp.dc.h
//  dc
//
//  Created by David Lindeque on 30/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#pragma once

#include "dc.ds.h"
#include "logger.h"
#include "compiler.h"
#include <string>
#include <unordered_map>

namespace dc
{
    struct output_lexer_cpp {
	private:
		logger *_logger;
		std::string _compile_filename;
		std::string _path;

		auto write_cpp(DocumentAstProcessor &processor, const symbolreference &ns, const spantext &lexer_name) const -> bool;
		auto write_h(DocumentAstProcessor &processor, const symbolreference &ns, const spantext &lexer_name) const -> bool;
	public:
		output_lexer_cpp(logger *logger, const std::string &compile_filename, const std::string &path)
		: _logger(logger), _compile_filename(compile_filename), _path(path)
		{}

		inline auto operator()(DocumentAstProcessor &processor) const -> bool {
			// Find the lexer name
			symbolreference ns(processor.start_symbol());
			spantext name(ns.back());
			ns.pop_back();

			bool ok = write_cpp(processor, ns, name);
			ok &= write_h(processor, ns, name);
			return ok;
		}
	};
}

