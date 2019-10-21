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
const int THREADS_NUMBER    = 10;
//------------------------------------------------------------------------------
void doFunc(int id, std::vector<bool>& guards);        	// Thread main function
//---------------------------------------------------------------------------
#endif
