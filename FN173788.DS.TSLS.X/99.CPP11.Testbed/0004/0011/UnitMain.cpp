//------------------------------------------------------------------------------
//	InterThreadCommunication through Proto-Channel
//	P (Sender) === Proto-Channel ==> Q (Receiver)
//
//	The condition_variable is used to facilitate inter-thread communication.
//
//	The alternative variant of std::condition_variable::wait() is used
//	with Predicate as second parameter.
//
//	std::condition_variable::wait(std::unique_lock<std::mutex>& lock, Predicate)
//
//	is equivalent to
//
//	while (!Predicate())
//	{
//		std::condition_variable::wait(lock);
//	}
//
//	If Predicate() returns false the waiting will be continued.
//	Could be used to introduce second condition to be met before exiting of std::condition_variable::wait().
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
#include <string>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
//------------------------------------------------------------------------------
std::mutex mu_cv;            	// mutex of the conditional variable
std::condition_variable cv;     // conditional variable to synchronize on

// Proto-Channel
std::string data;               // data transferred between threads
bool boolCompletedPreprocessing = false;	// flag checked by Sender lambda predicate
bool boolCompletedProcessing = false;		// flag checked by the main thread lambda predicate

// Sender main function
void doP(void)
{
	data = "Example data";
	// Send to Proto-Channel ///////////////////////////////////////////////////
	//
	{
		std::cout << "Sender: data preprocessing\n";
		std::lock_guard<std::mutex> lk(mu_cv);      // RAII
		std::chrono::milliseconds sleep_dur(1000);
		std::this_thread::sleep_for(sleep_dur);
		boolCompletedPreprocessing = true;
		std::cout << "Sender signals to Receiver: data preprocessing completed\n\n";
		// Automatic unlocking of lk before notifying because of RAII
	}
	cv.notify_one();
	//
	// Wait for acknoledge from the receiver
	{
		std::unique_lock<std::mutex> lk(mu_cv);
		cv.wait(lk, [](){return boolCompletedProcessing;});
		// Automatic unlocking of lk on exit because of RAII
	}
	////////////////////////////////////////////////////////////////////////////
}

// Receiver main function
void doQ(void)
{
	// Receive from Proto-Channel
	{
		// Wait until Sender sends data
		std::unique_lock<std::mutex> lk(mu_cv); 	// RAII
		cv.wait(lk, [](){ return boolCompletedPreprocessing; });

		// After the wait, worker thread owns the lock
		std::cout << "Receiver: data processing\n";
		std::chrono::milliseconds sleep_dur(1000);
		std::this_thread::sleep_for(sleep_dur);
		data += " after processing";

		// Send data back to main thread
		boolCompletedProcessing = true;
		std::cout << "Receiver acknowlage to Sender: data processing completed\n\n";
		// Automatic unlocking of lk before notifying because of RAII
	}
	// Return back acknowledge to the sender
	cv.notify_one();

	std::cout << "Data received: " << data << "\n\n";
}
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::thread> vThreads;

	// {P || Q}
	// P = {Q ! data}
	// Q = {P ? data}
	vThreads.push_back(std::thread(doP));
	vThreads.push_back(std::thread(doQ));

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

