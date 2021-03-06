#pragma once

#include <iostream>

#include "spanvalue.h"
#include "symbolreference.h"
#include "log.h"
#include "dc.ds.h"
#include "cpp_helpers.h"

namespace dc
{
	template<typename T>
	struct action_processor { };

	template<>
	struct action_processor<DfaAction> {
		template<class _Action> inline auto operator()(size_t state, const DfaAction &a, const _Action &action) const -> void {
            action(true, a.YieldAction);
		}
	};

	template<>
	struct action_processor<std::set<NfaAction, NfaActionLess>> {
		template<class _Action> inline auto operator()(size_t state, const std::set<NfaAction, NfaActionLess> &actions, const _Action &action) const -> void {
			for(auto &a : actions) {
				action(true, a);
			}
		}
	};

	template<typename T>
	struct transitions_processor { };

	template<>
	struct transitions_processor<std::vector<Transition>> {
		template<class _Action> inline auto operator()(const std::vector<Transition> &transitions, const _Action &action) const -> void
		{
			for(auto &t : transitions) {
				action(t);
			}
		}
	};

	template<>
	struct transitions_processor<std::map<size_t, std::vector<Transition>>> {
		template<class _Action> inline auto operator()(const std::map<size_t, std::vector<Transition>> &map, const _Action &action) const -> void
		{
			transitions_processor<std::vector<Transition>> p;
			for(auto &m : map) {
				p(m.second, action);
			}
		}
	};

	struct graph_formatter {
	private:
		std::wostream &_stm;
		static inline auto dot_str(const std::wstring &s) -> std::wstring {
			std::wstring r;
			for(auto &ch : s) {
				switch(ch) {
					case L'"': 
						r.append(L"\\\"");
						break;
					case L'\\':
						r.append(L"\\\\");
						break;
					default:
						r += ch;
				}
			}
			return r;
		}
	public:
		graph_formatter(std::wostream &stm)
		: _stm(stm)
		{}
		
		template<typename _Transitions, typename _Actions>  inline auto operator()(const std::wstring &graph_name, const _Transitions &transitions, const std::unordered_map<size_t, _Actions> &actions) const -> void {
			_stm << L"digraph " << graph_name << L" {" << std::endl;
			action_processor<_Actions> ap;
			auto &stm = _stm;
			for(auto &a : actions) {
				bool abs_final = false;
                _stm << L"    \"" << a.first << L"\" [label=\"" << a.first;
				ap(a.first, a.second, [&a, &abs_final, &stm](bool has_action, const NfaAction &action)
                   	{
                   		if (!has_action) {
                   			stm << L"\\nNO ACTION";
                   		}
                   		else {
                   			stm << L"\\n" << action.TokenName;
	                       	if (action.IsReturn) {
	                    		stm << L"\\nRETURN";
	                       	}
	                       	if (action.IsGoto) {
	                       		stm << L"\\nGOTO " << action.GotoAutomata;
	                       	}
                   		}
                   	});
                _stm << L"\"";
                if (abs_final) {
                	_stm << L",style=filled";
                }
                _stm << L"]" << std::endl;
			}

            transitions_processor<_Transitions> p;
            p(transitions, [&stm](const Transition &t)
              {
                  stm << L"    \""
                    << t.FromState
                    << L"\"->\""
                    << t.ToState
                    << L"\"";
                  if(t.IsEpsilon) {
                      stm << L" [style=dotted]";
                  } else if (t.First == L'\x0' && t.Last == L'\x0') {
                      stm << L" [label=\"exit\"]";
                  } else {
                      stm << L" [label=\"" << dot_str(log::printable(std::pair<wchar_t, wchar_t>(t.First, t.Last))) << L"\"]";
                  }
                  stm << std::endl;
              });
            _stm << L"}" << std::endl;
		}
	};


	struct output_nfa_gv {
	private:
		logger *_logger;
		std::string _compile_filename;
		std::string _path;
	public:
		output_nfa_gv(logger *logger, const std::string &compile_filename, const std::string &path)
		: _logger(logger), _compile_filename(compile_filename), _path(path)
		{}

		inline auto operator()(DocumentAstProcessor &processor) const -> bool {
			std::string fn = get_standard_output_filename(_compile_filename, _path, ".nfa.gv");
			log::info::WritingOutputFile(_logger, fn);
			std::wofstream stm(fn);
			if (!stm) {
				log::error::FailureOpeningFile(_logger, std::shared_ptr<container>(), span(), fn);
				return false;
			}
			graph_formatter fmt(stm);
			fmt(L"NFA", processor.nfa().transitions, processor.nfa().actions);
			return true;
		}
	};

	struct output_dfa_gv {
	private:
		logger *_logger;
		std::string _compile_filename;
		std::string _path;
	public:
		output_dfa_gv(logger *logger, const std::string &compile_filename, const std::string &path)
		: _logger(logger), _compile_filename(compile_filename), _path(path)
		{}

		inline auto operator()(DocumentAstProcessor &processor) const -> bool {
			std::string fn = get_standard_output_filename(_compile_filename, _path, ".dfa.gv");
			log::info::WritingOutputFile(_logger, fn);
			std::wofstream stm(fn);
			if (!stm) {
				log::error::FailureOpeningFile(_logger, std::shared_ptr<container>(), span(), fn);
				return false;
			}
            graph_formatter fmt(stm);
			fmt(L"DFA", processor.dfa().transitions, processor.dfa().actions);
			return true;
		}
	};

}