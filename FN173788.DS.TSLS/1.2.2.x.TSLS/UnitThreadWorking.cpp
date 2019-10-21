//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitThreadWorking.h"
#include "UnitFormMain.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
void DoWork(Item c, int id, int delay)
{
	std::chrono::milliseconds sleep_dur(delay);
	std::this_thread::sleep_for(sleep_dur);

	c->Close();
}
//---------------------------------------------------------------------------

