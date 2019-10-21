//------------------------------------------------------------------------------
//	The C++11 Concurrency Library introduces Atomic Types as a template class std::atomic.
//	Using atomic types advantage is its performance over locks.
//	In most cases, the std::atomic operations are implemented with lock-free operations
//	that are much faster than locks.
//	You can use any Type you want with std::atomic that template class
//	and the operations on that variable will be atomic and so thread-safe.
//
//	It has to be taken into account that it is up to the library implementation to choose
//	which syncronization mechanism is used to make the operations on that type atomic.
//	On standard platforms for integral types like int, long, float, ...
//	it will be some lock-free technique.
//	If you want to make a big type (let's saw 2MB storage), you can use std::atomic as well,
//	but mutexes will be used as implementation. In this case, there will be no performance advantage.
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
#include <atomic>
#include <thread>
#include <vector>
//------------------------------------------------------------------------------
struct AtomicCounter
{
	std::atomic<int> value;

	AtomicCounter() : value(0)
	{
	}

	void increment()
	{
		++value;
	}

	void decrement()
	{
		--value;
	}
};
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	AtomicCounter atomic_counter;
	std::vector<std::thread> threads;

	for(int i = 0; i < 10; ++i)
	{
		threads.push_back(std::thread([&atomic_counter]()
		{
			for(int i = 0; i < 100000; i++)
			{
				atomic_counter.increment();
			}
		}));
	}

	for(auto& thread : threads)
	{
		if(thread.joinable())
		{
			thread.join();
		}
	}

	std::cout << atomic_counter.value << std::endl;

	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------

