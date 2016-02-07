#pragma once

#include "dc.ds.h"
#include "logger.h"

namespace dc
{
	auto build_dfa(logger *logger, const nfa &nfa) -> dfa;
	auto valid_and_find_default_actions(logger *logger, dfa &dfa) -> bool;
}

