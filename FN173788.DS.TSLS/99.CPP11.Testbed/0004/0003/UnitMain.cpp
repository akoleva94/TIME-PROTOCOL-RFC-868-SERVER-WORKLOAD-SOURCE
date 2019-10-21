//------------------------------------------------------------------------------
//	Starting each thread one after one and then storing them into a vector is a common way
//	to handle several threads. With that, you can change the number of threads.
//	Even with a little sample like this one, the results is not predictable, because of interleaving.
//	You have no way to control the order of execution of threads.
//	A thread can be preempted at any moment and the appends to the out stream are made one after one
//	(first the append of the string, then append the id and finally the new line),
//	so a thread can print its first part and then be interrupted to print its second part
//	after all the others threads.
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
#include <vector>
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::thread> threads;

	for(int i = 0; i < 5; ++i)
	{
		threads.push_back(std::thread([](){ std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl; }));
	}

	for(auto& thread : threads)
	{
		if(thread.joinable())
		{
			thread.join();
		}
	}

	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------

