//------------------------------------------------------------------------------
//	Chrono is a precision-neutral library for time and date
//
//	std::chrono::system_clock	- current time according to system clock, not steady
//	std::chrono::steady_clock	- goes at uniform rate
//	std::chrono::high_resolution_clock	- provides smallest possible clock period
//
//	std::chrono::duration<>		- represents time duration
//------------------------------------------------------------------------------
#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <windows.h>
#include <stdio.h>
//------------------------------------------------------------------------------
#include <iostream>
#include <chrono>
#include <thread>
//------------------------------------------------------------------------------
void DoWork(void);
const int VOLUME = 1000;
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::string strLine;
	for(int i = 0; i < 32; i++)
	{
		strLine += "x";
	}

	// Measuring Period ////////////////////////////////////////////////////////
	auto t1 = std::chrono::system_clock::now();

	for(int i = 0; i < VOLUME; i++)
	{
		std::cout << i << "::" << strLine.c_str() << std::endl;
	}

	auto t2 = std::chrono::system_clock::now();

	for(int i = 0; i < VOLUME; i++)
	{
		std::thread threadWorking(DoWork);	// създаване/стартиране на обслужваща нишка
		threadWorking.detach();				// развързване на дъщерната нишка от основната
	}

	auto t3 = std::chrono::system_clock::now();
	////////////////////////////////////////////////////////////////////////////

	// conversion of duration into microseconds
	std::chrono::microseconds dur1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
	std::cout << "Duration: " << dur1.count()/VOLUME << ", microseconds" << std::endl;

	std::chrono::microseconds dur2 = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2);
	std::cout << "Duration: " << dur2.count()/VOLUME << ", microseconds" << std::endl;

	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------
void DoWork(void)
{
	std::chrono::milliseconds sleep_dur(1000);
	std::this_thread::sleep_for(sleep_dur);
}
//------------------------------------------------------------------------------

