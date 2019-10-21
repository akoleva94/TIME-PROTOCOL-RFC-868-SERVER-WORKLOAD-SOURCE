//------------------------------------------------------------------------------
//	Calling join() forces the current thread to wait for the other one.
//	In this case, the main thread has to wait for the thread t1 to finish.
//	If you omit this call, the result is undefined,
//	because the main thread can return from the main function before
//	the t1 thread finishes its execution.
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
//------------------------------------------------------------------------------
void hello(void);
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::thread t1(hello);

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
void hello(void)
{
	std::cout << "Hello from thread" << std::endl;
}
//------------------------------------------------------------------------------

