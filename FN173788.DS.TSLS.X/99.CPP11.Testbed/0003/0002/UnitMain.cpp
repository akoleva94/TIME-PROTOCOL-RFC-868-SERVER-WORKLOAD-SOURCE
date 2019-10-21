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
int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Clock Period, sec" << std::endl;
//	std::cout << std::chrono::system_clock::period::num << "/" << std::chrono::system_clock::period::den << std::endl << std::endl;
//	std::cout << std::chrono::steady_clock::period::num << "/" << std::chrono::system_clock::period::den << std::endl << std::endl;
	std::cout << std::chrono::high_resolution_clock::period::num << "/" << std::chrono::system_clock::period::den << std::endl << std::endl;

	// Measuring Period ////////////////////////////////////////////////////////
//	auto beg = std::chrono::system_clock::now();
//	auto beg = std::chrono::steady_clock::now();
	auto beg = std::chrono::high_resolution_clock::now();
	//
	std::chrono::milliseconds sleep_dur(1000);
	std::this_thread::sleep_for(sleep_dur);
	//
//	auto end = std::chrono::system_clock::now();
//	auto end = std::chrono::steady_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	////////////////////////////////////////////////////////////////////////////

	// conversion of duration into microseconds
	std::chrono::microseconds dur_in_micro = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
	std::cout << "Duration: " << dur_in_micro.count() << ", microseconds" << std::endl;
	
	// "Press any key to continue..."
	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}
//------------------------------------------------------------------------------

