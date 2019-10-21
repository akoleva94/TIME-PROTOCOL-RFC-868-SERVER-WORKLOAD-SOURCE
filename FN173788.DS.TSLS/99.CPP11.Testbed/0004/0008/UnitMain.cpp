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
#include <chrono>
#include <mutex>
#include <thread>
//------------------------------------------------------------------------------
struct Box
{
	explicit Box(int num) : num_things{num} {}

	int num_things;
	std::mutex m;
};

void transfer(Box &from, Box &to, int num)
{
	// don't actually take the locks yet (defer it)
	std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
	std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

	// lock both unique_locks without deadlock
	std::lock(lock1, lock2);

	from.num_things -= num;
	to.num_things += num;

	// 'from.m' and 'to.m' mutexes unlocked in 'unique_lock' destructors
}
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	Box acc1(100);
	Box acc2(50);

	std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
	std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);

	t1.join();
	t2.join();

	std::cout << "Box acc1.num_things = " << acc1.num_things << std::endl;
	std::cout << "Box acc2.num_things = " << acc2.num_things << std::endl;

	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------

