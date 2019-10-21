//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormMain.h"
#include "UnitFormSockets.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformMain *formMain;
//---------------------------------------------------------------------------
__fastcall TformMain::TformMain(TComponent* Owner)
	: TForm(Owner)
{
/* TODO : Load Log */
	try
	{
		memoLogs->Lines->LoadFromFile(STR_LOG_FILE);
	}
	catch(Exception& e)
	{

	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::FormClose(TObject *Sender, TCloseAction &Action)
{
/* TODO : Close Connections */
/* TODO : Save Log */
	try
	{
		memoLogs->Lines->SaveToFile(STR_LOG_FILE);
	}
	catch(Exception& e)
	{

	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::buttonSyncClick(TObject *Sender)
{
/* TODO : Set Socket IP Address */
/* TODO : Send Request */
	formSockets->csSocket->Address = cboxIPAddress->Text;
    formSockets->csSocket->Active = true;
}
//---------------------------------------------------------------------------

