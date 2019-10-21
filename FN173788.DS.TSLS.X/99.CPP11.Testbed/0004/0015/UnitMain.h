//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <random>
#include <string>
#include <thread>
//------------------------------------------------------------------------------
#define SCENARIO 2
// 1 - Receiver Started without delay; Notifications delayed randomly
// 2 - Receiver Started after all notifications; Notifications delayed randomly
// 3 - Receiver Started between notifications; Notifications delayed randomly
//------------------------------------------------------------------------------
#if (SCENARIO == 1)
const int DELAY_RECEIVER	    = 0;		// ms
const int DELAY_NOTIFICATIONS	= 6000;		// ms
#elif (SCENARIO == 2)
const int DELAY_RECEIVER	    = 10000;	// ms
const int DELAY_NOTIFICATIONS	= 6000;		// ms
#elif (SCENARIO == 3)
const int DELAY_RECEIVER	    = 3000;		// ms
const int DELAY_NOTIFICATIONS	= 6000;		// ms
#else
	#error ILLEGAL SCENARIO
#endif
//------------------------------------------------------------------------------
const int THREADS_NUMBER    = 10;


enum class Disptaching {by_place, uniform};
//------------------------------------------------------------------------------
void doFunc(int id, std::vector<bool>& guards);        	// Thread main function
//---------------------------------------------------------------------------
#endif
