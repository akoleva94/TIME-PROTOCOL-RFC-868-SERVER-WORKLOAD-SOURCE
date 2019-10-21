//------------------------------------------------------------------------------
//	std::async() accepts a function to be executed and returns a future
//	that you can use to retrieve the result.
//
//	There are two ways in which async() can call your function:
//	- Creating a new thread to run your function asynchronously;
//	- Running your function at the time you call get() on the returned future.
//
//	If you call async() without additional arguments, the run-time library will
//	automatically choose one of the two methods depending on factors like
//	the number of processors in your system.
//
//	You can force the runtime to use one or the other method by specifying a
//	launch::async or launch::deferred policy argument, respectively.
//
//	Gregoire, Marc; Solter, Nicholas A.; Kleper, Scott J.. Professional C++ (p. 827). Wiley. Kindle Edition.
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

#include <future>
#include <thread>
//------------------------------------------------------------------------------
int Calculate(void)
{
	std::cout << "Async Task is running" << std::endl;
	return 123;
}
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    // Async Task will return a std::future declared as auto
//	auto fut = std::async(std::launch::async, Calculate);
//	auto fut = std::async(std::launch::deferred, Calculate);
	auto fut = std::async(Calculate);
//	auto fut = std::async(std::launch::async | std::launch::deferred, Calculate);

	// Do some more work in main thread in parallel with Ascync Task...       

	// Get result     
	int res = fut.get();
	std::cout << res << std::endl;

	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------

