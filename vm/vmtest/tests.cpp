#include "stdafx.h"
// Generated
 


#include "CppUnitTest.h"

#include <vector>
#include <memory>
#include <crtdbg.h>
#include "test_ctx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace davetests
{
	TEST_CLASS(g_tests)
	{
	public:

		#line 18 "cpu6502.g"
		TEST_METHOD(InvalidGherkinText2)
		{
#if _DEBUG
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
			
			_CrtMemState s1;
			_CrtMemCheckpoint(&s1);
#endif
			{
				test_ctx ctx;
			}
#if _DEBUG
            if (!_CrtCheckMemory()) {
                Assert::Fail(L"Corrupt memory");
            }
			_CrtMemState s2, s3;
			_CrtMemCheckpoint(&s2);
			auto leaks_found = _CrtMemDifference(&s3, &s1, &s2);
			if (leaks_found) {
				_CrtDumpMemoryLeaks();
			}
			#line 18 "cpu6502.g"
			Assert::AreEqual(0, leaks_found, L"Memory Leaks");
#endif
		}
		#line 19 "cpu6502.g"
		TEST_METHOD(InvalidGherkinText2)
		{
#if _DEBUG
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
			
			_CrtMemState s1;
			_CrtMemCheckpoint(&s1);
#endif
			{
				test_ctx ctx;
			}
#if _DEBUG
            if (!_CrtCheckMemory()) {
                Assert::Fail(L"Corrupt memory");
            }
			_CrtMemState s2, s3;
			_CrtMemCheckpoint(&s2);
			auto leaks_found = _CrtMemDifference(&s3, &s1, &s2);
			if (leaks_found) {
				_CrtDumpMemoryLeaks();
			}
			#line 19 "cpu6502.g"
			Assert::AreEqual(0, leaks_found, L"Memory Leaks");
#endif
		}
		#line 27 "cpu6502.g"
		TEST_METHOD(InvalidGherkinText2)
		{
#if _DEBUG
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
			
			_CrtMemState s1;
			_CrtMemCheckpoint(&s1);
#endif
			{
				test_ctx ctx;
			}
#if _DEBUG
            if (!_CrtCheckMemory()) {
                Assert::Fail(L"Corrupt memory");
            }
			_CrtMemState s2, s3;
			_CrtMemCheckpoint(&s2);
			auto leaks_found = _CrtMemDifference(&s3, &s1, &s2);
			if (leaks_found) {
				_CrtDumpMemoryLeaks();
			}
			#line 27 "cpu6502.g"
			Assert::AreEqual(0, leaks_found, L"Memory Leaks");
#endif
		}
		#line 1 "cpu6502.g"
		TEST_METHOD(cpu6502_addressing_mode_immediate)
		{
#if _DEBUG
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
			
			_CrtMemState s1;
			_CrtMemCheckpoint(&s1);
#endif
			{
				test_ctx ctx;
				{
					#line 2 "cpu6502.g"
					autumntests::table  data;
				data.set_headers({ "Register","Value" });
				data.add_row({ "A","0x0F" });
				data.add_row({ "Y","0x00" });
				data.add_row({ "X","0x00" });
				data.add_row({ "PC","0x0200" });
				data.add_row({ "S","0x00" });
				data.add_row({ "P","N=0;V=0;B=0;D=0;I=0;Z=0;C=0" });
				ctx.add_6502_cpu("slot1", data);
#if _DEBUG
					Assert::IsTrue(_CrtCheckMemory() != 0);
#endif
				}
				{
					#line 10 "cpu6502.g"
					ctx.add_mock_ram();
#if _DEBUG
					Assert::IsTrue(_CrtCheckMemory() != 0);
#endif
				}
				{
					#line 11 "cpu6502.g"
					ctx.compile_and_load_program(".ORG $0200\r\nAND #$11   ; And accumulator with 0x11\r\nLDA #$01   ; Load accumulator with 0x01\r\nSTA #$C000 ; Store A into 0xC000\r\n");
#if _DEBUG
					Assert::IsTrue(_CrtCheckMemory() != 0);
#endif
				}
			}
#if _DEBUG
            if (!_CrtCheckMemory()) {
                Assert::Fail(L"Corrupt memory");
            }
			_CrtMemState s2, s3;
			_CrtMemCheckpoint(&s2);
			auto leaks_found = _CrtMemDifference(&s3, &s1, &s2);
			if (leaks_found) {
				_CrtDumpMemoryLeaks();
			}
			#line 1 "cpu6502.g"
			Assert::AreEqual(0, leaks_found, L"Memory Leaks");
#endif
		}
		#line 49 "cpu6502.g"
		TEST_METHOD(InvalidGherkinText2)
		{
#if _DEBUG
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
			
			_CrtMemState s1;
			_CrtMemCheckpoint(&s1);
#endif
			{
				test_ctx ctx;
			}
#if _DEBUG
            if (!_CrtCheckMemory()) {
                Assert::Fail(L"Corrupt memory");
            }
			_CrtMemState s2, s3;
			_CrtMemCheckpoint(&s2);
			auto leaks_found = _CrtMemDifference(&s3, &s1, &s2);
			if (leaks_found) {
				_CrtDumpMemoryLeaks();
			}
			#line 49 "cpu6502.g"
			Assert::AreEqual(0, leaks_found, L"Memory Leaks");
#endif
		}
		#line 57 "cpu6502.g"
		TEST_METHOD(InvalidGherkinText2)
		{
#if _DEBUG
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
			
			_CrtMemState s1;
			_CrtMemCheckpoint(&s1);
#endif
			{
				test_ctx ctx;
			}
#if _DEBUG
            if (!_CrtCheckMemory()) {
                Assert::Fail(L"Corrupt memory");
            }
			_CrtMemState s2, s3;
			_CrtMemCheckpoint(&s2);
			auto leaks_found = _CrtMemDifference(&s3, &s1, &s2);
			if (leaks_found) {
				_CrtDumpMemoryLeaks();
			}
			#line 57 "cpu6502.g"
			Assert::AreEqual(0, leaks_found, L"Memory Leaks");
#endif
		}
		#line 31 "cpu6502.g"
		TEST_METHOD(cpu6502_addressing_mode_absolute)
		{
#if _DEBUG
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
			
			_CrtMemState s1;
			_CrtMemCheckpoint(&s1);
#endif
			{
				test_ctx ctx;
				{
					#line 32 "cpu6502.g"
					autumntests::table  data;
				data.set_headers({ "Register","Value" });
				data.add_row({ "A","0x0F" });
				data.add_row({ "Y","0x00" });
				data.add_row({ "X","0x00" });
				data.add_row({ "PC","0x0200" });
				data.add_row({ "S","0x00" });
				data.add_row({ "P","N=0;V=0;B=0;D=0;I=0;Z=0;C=0" });
				ctx.add_6502_cpu("slot1", data);
#if _DEBUG
					Assert::IsTrue(_CrtCheckMemory() != 0);
#endif
				}
				{
					#line 40 "cpu6502.g"
					ctx.add_mock_ram();
#if _DEBUG
					Assert::IsTrue(_CrtCheckMemory() != 0);
#endif
				}
				{
					#line 41 "cpu6502.g"
					ctx.compile_and_load_program(".ORG $0200\r\nAND $0308 ; And accumulator with data (0x22) at 0x0308\r\n.ORG $0308\r\n.BYTE $22\r\n");
#if _DEBUG
					Assert::IsTrue(_CrtCheckMemory() != 0);
#endif
				}
				{
					#line 48 "cpu6502.g"
					ctx.process_nexts_instruction();
#if _DEBUG
					Assert::IsTrue(_CrtCheckMemory() != 0);
#endif
				}
			}
#if _DEBUG
            if (!_CrtCheckMemory()) {
                Assert::Fail(L"Corrupt memory");
            }
			_CrtMemState s2, s3;
			_CrtMemCheckpoint(&s2);
			auto leaks_found = _CrtMemDifference(&s3, &s1, &s2);
			if (leaks_found) {
				_CrtDumpMemoryLeaks();
			}
			#line 31 "cpu6502.g"
			Assert::AreEqual(0, leaks_found, L"Memory Leaks");
#endif
		}
	};
}

