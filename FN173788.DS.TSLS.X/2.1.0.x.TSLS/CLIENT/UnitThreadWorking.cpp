//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitThreadWorking.h"
#include "UnitFormMain.h"
#include "UnitDMClients.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
void DoWork(Item c, int id, int delay, TObject* o)
{
//	TdmClients* oo = (TdmClients*)o;
	TdmClients* oo = static_cast<TdmClients*>(o);

	unsigned long ulTime;

	c->ReceiveBuf(&ulTime, 4);
	ulTime = ntohl(ulTime);

	if(id >= 0)
	{
		oo->clientsPack->vClients[id]->pairRPL.first = Time();
		oo->clientsPack->vClients[id]->pairRPL.second = oo->clientsPack->intCNC;
		oo->clientsPack->vClients[id]->rpl = ulTime;
	}
	oo->log->Add(c, "RPL[" + IntToStr(id) + "]::[" + IntToHex((int)ulTime, 8) + "]", oo->Parameters.boolL1);

	std::chrono::milliseconds sleep_dur(delay);
	std::this_thread::sleep_for(sleep_dur);

	c->Close();
}
//---------------------------------------------------------------------------

