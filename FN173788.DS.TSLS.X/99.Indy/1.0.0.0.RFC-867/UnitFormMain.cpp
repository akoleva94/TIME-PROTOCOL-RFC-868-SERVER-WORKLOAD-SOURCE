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
void __fastcall TformMain::btnSyncClick(TObject *Sender)
{
	IdDayTime->ConnectAndGetAll();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::IdDayTimeWorkEnd(TObject *ASender, TWorkMode AWorkMode)

{
	String str;
	str = IdDayTime->DayTimeStr;
	formMain->memoLog->Lines->Add("workEnd:" + str);
}
//---------------------------------------------------------------------------

