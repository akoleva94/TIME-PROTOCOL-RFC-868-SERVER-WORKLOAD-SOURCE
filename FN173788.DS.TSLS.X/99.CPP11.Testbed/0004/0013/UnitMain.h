//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>

#include <chrono>
#include <random>
#include <thread>
//------------------------------------------------------------------------------
//#define __RANDOMIZE_DEFAULT

const int SAMPLE_SIZE = 10;
//---------------------------------------------------------------------------
void doFunc(std::vector<int>& v, int id);        	// Thread main function
//---------------------------------------------------------------------------
#endif
