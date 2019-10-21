//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormMain.h"
#include "System.SysUtils.hpp"
#include "System.Classes.hpp"
#include "System.SysUtils.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformMain *formMain;
//---------------------------------------------------------------------------
__fastcall TformMain::TformMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TformMain::buttonSyncClick(TObject *Sender)
{
	IdDayTime->ConnectAndGetAll();
	String str = IdDayTime->DayTimeStr;
	formMain->memoLog->Lines->Add(str);
}
//---------------------------------------------------------------------------

