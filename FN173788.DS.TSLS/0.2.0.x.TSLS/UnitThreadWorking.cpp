//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitThreadWorking.h"
#include "UnitFormMain.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
void DoWork(Item c, int id)
{
	std::chrono::milliseconds sleep_dur(3000);
	std::this_thread::sleep_for(sleep_dur);

	c->Close();
}
//---------------------------------------------------------------------------

