//------------------------------------------------------------------------------
//	Project Name
//		WaitOnForMultipleEvents
//	Description
//		Explore technique to wait on std::condition_variable for multiple events.
//		This is going to be used in csp::alt() implementation.
//
//		The technique is based on using Predicate, second parameter of std::wait().
//		Calling of std::wait(lock, Predicate) is equivavelnt to
//		while (!Predicate())
//		{
//			wait(lock);
//		}
//		i.e. the Predicate is checked before std::wait(lock)
//		http://en.cppreference.com/w/cpp/thread/condition_variable/wait
//		The Predicate itself is implemented as lambda.
//
//	Status:	Completed
//------------------------------------------------------------------------------

#pragma hdrstop

#include "UnitMain.h"
//---------------------------------------------------------------------------
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

//------------------------------------------------------------------------------
std::mutex mu_cv;            	// mutex of the conditional variable
std::condition_variable cv;     // conditional variable to synchronize on

static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::default_random_engine random_engine(seed);
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::thread> vThreads;
	std::vector<bool> vGuards;

	for(int i = 0; i < THREADS_NUMBER; i++)
	{
		vGuards.push_back(false);
		vThreads.push_back(std::thread(doFunc, i, std::ref(vGuards)));
	}

	//  Delay of Receiver to stimulate Race Condition of notifications
	std::chrono::milliseconds sleep_dur(3000);
	std::cout << "Delay of Receiver for " << sleep_dur.count() << ", ms\n\n";
	std::this_thread::sleep_for(sleep_dur);

	for(int i = 0; i < vThreads.size(); i++)
	{
		int id = -1;

		{
			//  WaitOnForMultipleEvents
			std::unique_lock<std::mutex> lk(mu_cv);
			cv.wait(lk, [&id, &vGuards, &vThreads]()
						{	//  The Predicate, implemented as lambda
							//  It is checked before std::wait(lock)
							for(auto j = 0; j < vThreads.size(); j++)
							{
								if(vGuards[j] == true)
								{
									vGuards[j] = false;
									id = j;
									return true;
								}
							}
							id = -1;
							return false;
						});

			std::cout <<  id << std::endl;
		}
	}

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
void doFunc(int id, std::vector<bool>& guards)
{
	//  Random Delay to stimulate Race Condition of notifications
	std::uniform_int_distribution<int> distribution(0, 6000);
	std::this_thread::sleep_for(std::chrono::milliseconds(distribution(random_engine)));

	guards[id] = true;
	cv.notify_one();
}
//------------------------------------------------------------------------------

