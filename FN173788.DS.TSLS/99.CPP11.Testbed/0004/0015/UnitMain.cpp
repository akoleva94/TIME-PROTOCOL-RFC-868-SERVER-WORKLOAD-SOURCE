//------------------------------------------------------------------------------
//	Project Name
//		WaitOnForMultipleEvents_D
//	Description
//		The Project 0004.0014 WaitOnForMultipleEvents extended with
//		distingushing of dispatching desciplines:
//		- by guard place;
//		- non-deterministic (uniform random).
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
//Disptaching dispatching = Disptaching::by_place;
Disptaching dispatching = Disptaching::uniform;

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

	//  Receiver Delay to stimulate Race Condition of notifications
	std::chrono::milliseconds sleep_dur(DELAY_RECEIVER);
	std::cout << "Receiever Delay of " << sleep_dur.count() << ", ms\n\n";
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
							switch(dispatching)
							{
								case Disptaching::by_place:
									// Dispatching by guard place
									for(auto j = 0; j < vGuards.size(); j++)
									{
										if(vGuards[j] == true)
										{
											vGuards[j] = false;
											id = j;
											return true;
										}
									}
									break;

								case Disptaching::uniform:
                                    // Uniform (non-deterministic) dispatching
									std::vector<int> vGuardsInTrue;
									for(auto j = 0; j < vGuards.size(); j++)
									{
										if(vGuards[j] == true)
										{
											vGuardsInTrue.push_back(j);
										}
									}

									if(vGuardsInTrue.size() > 0)
									{
										int k = 0;  // index of selected true guard
										if(vGuardsInTrue.size() > 1)
										{   // more than 1 guards are true
                                        	// select one of them randomly
											std::uniform_int_distribution<int> distribution(0, vGuardsInTrue.size() - 1);
											k = distribution(random_engine);
										}

										vGuards[vGuardsInTrue[k]] = false;
										id = vGuardsInTrue[k];
										return true;
									}
									break;
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
	std::uniform_int_distribution<int> distribution(0, DELAY_NOTIFICATIONS);
	std::this_thread::sleep_for(std::chrono::milliseconds(distribution(random_engine)));

	guards[id] = true;
	cv.notify_one();
}
//------------------------------------------------------------------------------

