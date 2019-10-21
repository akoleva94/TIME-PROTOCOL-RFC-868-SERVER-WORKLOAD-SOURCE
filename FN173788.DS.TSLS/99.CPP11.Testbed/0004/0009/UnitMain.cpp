//------------------------------------------------------------------------------
//	Calling a function only once no matter the number of threads that are used.
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
#include <thread>
#include <mutex>
//------------------------------------------------------------------------------
std::once_flag flag;
std::mutex mutex;       // used to order access to std::cout

void do_something()
{
	std::lock_guard<std::mutex> guard(mutex);   // RAII

	std::call_once(flag, [](){ std::cout << "Part#1.Called once" << std::endl; });

	std::cout << "Part#2.Called each time" << std::endl;
}
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::thread t1(do_something);
	std::thread t2(do_something);
	std::thread t3(do_something);
	std::thread t4(do_something);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------

