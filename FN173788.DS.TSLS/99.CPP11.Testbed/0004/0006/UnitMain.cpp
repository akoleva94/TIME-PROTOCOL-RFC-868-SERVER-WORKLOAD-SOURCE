//------------------------------------------------------------------------------
#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

//------------------------------------------------------------------------------
#include <iostream>

#include <mutex>
#include <string>
#include <thread>
//------------------------------------------------------------------------------
std::mutex mutex;   // Should be declared global not local
void shared_print(const std::wstring& msg, int id)
{
	std::lock_guard<std::mutex> guard(mutex);   // RAII
	std::wcout << msg << "::" << id << std::endl;
}
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	// Strange, but
	// std::cout.sync_with_stdio(true) does not works in this context
	// and shared_print() is must.
	std::cout.sync_with_stdio(true);	// Make sure cout is thread-safe

	std::thread t1([]()
	{
		for(int i = 0; i > -10; i--)
		{
			shared_print(L"t1", i);
		}
	});

	for(int i = 0; i < 10; i++)
	{
		shared_print(L"main", i);
	}

	if(t1.joinable())
	{
		t1.join();
	}

	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------

