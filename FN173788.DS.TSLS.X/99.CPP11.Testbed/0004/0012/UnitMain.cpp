//------------------------------------------------------------------------------
//	Explore uncountability of std::condition_variable.
//
//	It is impossible for std::notify_one() to be delayed and unblock a thread
//	that started waiting just after the call to notify_one() was made.
//
//	The notifying thread does not need to hold the lock on the same mutex
//	as the one held by the waiting thread(s). In fact doing so is a pessimization,
//	since the notified thread would immediately block again,
//	waiting for the notifying thread to release the lock.
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
#include <vector>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>
//------------------------------------------------------------------------------
std::mutex mu_cv;            	// mutex of the conditional variable
std::condition_variable cv;     // conditional variable to synchronize on

void worker_thread(int id)
{
	std::unique_lock<std::mutex> lk(mu_cv);
	cv.wait(lk);

	std::wstring msg = std::to_wstring(id);
	std::wcout << "Notification #" << msg << " got" << std::endl;
}
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	cv.notify_one();
	std::cout << "Notify #1" << std::endl;

	cv.notify_one();
	std::cout << "Notify #2" << std::endl;

	cv.notify_one();
	std::cout << "Notify #3" << std::endl;

	std::vector<std::thread> vThreads;

	vThreads.push_back(std::thread(worker_thread, 1));
	vThreads.push_back(std::thread(worker_thread, 2));
	vThreads.push_back(std::thread(worker_thread, 3));
	vThreads.push_back(std::thread(worker_thread, 4));
	vThreads.push_back(std::thread(worker_thread, 5));

	cv.notify_one();
	std::cout << "Notify #4" << std::endl;

	cv.notify_one();
	std::cout << "Notify #5" << std::endl;

	for(auto& t : vThreads)
	{
		if(t.joinable())
		{
			t.join();
		}
	}

	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------

