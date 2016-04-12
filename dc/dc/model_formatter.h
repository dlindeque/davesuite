//
//  
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
    struct output_model_cpp {
	private:
		logger *_logger;
		std::string _compile_filename;
		std::string _path;

		auto process(DocumentAstProcessor &processor) const -> bool;
		auto write_cpp(DocumentAstProcessor &processor) const -> bool;
		auto write_h(DocumentAstProcessor &processor) const -> bool;
	public:
		output_model_cpp(logger *logger, const std::string &compile_filename, const std::string &path)
		: _logger(logger), _compile_filename(compile_filename), _path(path)
		{}

		inline auto operator()(DocumentAstProcessor &processor) const -> bool {
			if (!process(processor)) return false;
			bool ok = write_cpp(processor);
			ok &= write_h(processor);
			return ok;
		}
	};
}

