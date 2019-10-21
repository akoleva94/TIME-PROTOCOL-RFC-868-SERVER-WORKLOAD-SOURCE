//------------------------------------------------------------------------------
//	Project Name
//		SharedRNG
//	Description
//		Thread-safe Random Number Generator.
//
//	Randomization of the random_engine
//		- with random_device()
//			std::random_device random_device;
//			std::default_random_engine random_engine(random_device());
//		Not apropriate because of random_device.entropy() is 0.
//		- with std::chrono::system_clock
//			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//			static std::default_random_engine random_engine(seed);
//		Gives good result.
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
#if defined __RANDOMIZE_DEFAULT
static std::random_device random_device;
static std::default_random_engine random_engine(random_device());
#else
static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::default_random_engine random_engine(seed);
#endif
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<int> vRandom1, vRandom2, vRandom3;
	std::vector<std::thread> vThreads;

    //	{P1 || P2 || P3}
	vThreads.push_back(std::thread(doFunc, std::ref(vRandom1), 1));
	vThreads.push_back(std::thread(doFunc, std::ref(vRandom2), 2));
	vThreads.push_back(std::thread(doFunc, std::ref(vRandom3), 3));

	for(auto& t : vThreads)
	{
		if(t.joinable())
		{
			t.join();
		}
	}

#if defined __RANDOMIZE_DEFAULT
	std::cout << "Random Device Entropy:" << random_device.entropy() << std::endl;
#endif

	std::cout << "Series #1: ";
	for(auto& r : vRandom1)
	{
		std::cout << r;
	}
	std::cout << std::endl;

	std::cout << "Series #2: ";
	for(auto& r : vRandom2)
	{
		std::cout << r;
	}
	std::cout << std::endl;

	std::cout << "Series #3: ";
	for(auto& r : vRandom3)
	{
		std::cout << r;
	}
	std::cout << std::endl;

	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------
void doFunc(std::vector<int>& v, int id)
{
	std::uniform_int_distribution<int> distribution(0, 1);
	for(int i = 0; i < SAMPLE_SIZE; i++)
	{
		v.push_back(distribution(random_engine));
	}
}
//------------------------------------------------------------------------------

