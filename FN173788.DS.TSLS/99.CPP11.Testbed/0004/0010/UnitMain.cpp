//------------------------------------------------------------------------------
//	A condition variable is an object able to block the calling thread until notified to resume.
//	It uses a unique_lock<mutex> to lock the thread when one of its wait functions is called.
//	The thread remains blocked until woken up by another thread that calls a notification function on
//	the same condition_variable object.
//
//	Objects of type condition_variable always use unique_lock<mutex> to wait.
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

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
//------------------------------------------------------------------------------
std::mutex mu_cv;            	// mutex of the conditional variable
std::condition_variable cv;     // conditional variable to synchronize on

void print_id(int id)
{
	std::unique_lock<std::mutex> lk(mu_cv);  // acquire the mutex
	cv.wait(lk);		// release the mutex and suspend the thread execution
	// the thread is awakened, and the mutex is atomically reacquired

	// Protected Thread Body ///////////////////////////////////////////////////
	//
	std::cout << "thread " << id << " started ";
	// ...
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	// ...
	std::cout << "stopped" << std::endl;
	//
	// Automatically unlock mutex on function exit /////////////////////////////
}
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::thread> threads;
	int intN = threads.size();	// number of system threads

	for(int i = 0; i < 10; ++i, ++intN)
	{
		threads.push_back(std::thread(print_id, i));
	}

	std::cout << intN << " threads are waiting on...\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	cv.notify_all();			// all threads awakened but serialized on mu_cv

	for(auto& t : threads)
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

