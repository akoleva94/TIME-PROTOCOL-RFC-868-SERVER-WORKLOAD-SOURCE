//------------------------------------------------------------------------------
//	There are several solutions for protection of shared data:
//	- Semaphores
//	- Atomic references
//	- Monitors
//	- Condition codes
//	- Compare and swap
//	etc.
//
//	Here we use a special kind of semaphores called mutexes.
//	A mutex is a very simple object. Only one thread can obtain the lock on a mutex at the same time.
//	This simple (and powerful) property of a mutex allow us to use it to fix synchronization problems.
//
//	When you want to protect a whole block of code, std::lock_guard is a good solution
//	to avoid forgetting to release the lock. This class is a simple smart manager for a lock.
//	When the std::lock_guard is created, it automatically calls lock() on the mutex.
//	When the guard gets destructed, it also releases the lock.
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
#include <thread>
#include <vector>

#define SAFE_COUNTER
//------------------------------------------------------------------------------
struct Counter
{
	int value;

	Counter() : value(0)
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

struct ConcurrentSafeCounter
{
	std::mutex mutex;
	Counter counter;

	void increment()
	{
	#if defined(SAFE_COUNTER)
		std::lock_guard<std::mutex> guard(mutex);   // RAII
	#endif
		counter.increment();
	}

	void decrement()
	{
	#if defined(SAFE_COUNTER)
		std::lock_guard<std::mutex> guard(mutex);   // RAII
	#endif
		counter.decrement();
	}
};
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	ConcurrentSafeCounter safe_counter;
	std::vector<std::thread> threads;

	for(int i = 0; i < 10; ++i)
	{
		threads.push_back(std::thread([&safe_counter]()
			{
				for(int i = 0; i < 100000; i++)
				{
					safe_counter.increment();
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

	std::cout << safe_counter.counter.value << std::endl;

	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------
