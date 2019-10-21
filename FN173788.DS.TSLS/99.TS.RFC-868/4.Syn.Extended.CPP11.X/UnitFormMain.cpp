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
	if(formSockets->intWorkingThreadsNumber != 0)
	{
	//  ������ ����� ��������� �� ������������ ��� �������� �����
	//  �� �� �� ������ �� ���� ����� ������� ������ �� �� ��-������������� (~ sec).
	//  � ����� ������ ������� ���������� ����� ��-�����, ������ �����
    //  �� �� ����� �� ���� �����.
		Action = caNone;
		ShowMessage("There are active threads. Cannot close.");
		return;
    }

/* TODO : Close Connections */
    formSockets->ssSocket->Active = false;

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
void __fastcall TformMain::cbUTCClick(TObject *Sender)
{
	if(!cbUTC->Checked)
	{
		leditUTC->Text = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::cbLogClick(TObject *Sender)
{
	if(!cbLog->Checked)
	{
		memoLogs->Clear();

		formSockets->intWorkingThreadsNumberMax = 0;
		stbarThreadsDblClick(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::stbarThreadsDblClick(TObject *Sender)
{
	stbarThreads->Panels->Items[1]->Text = IntToStr(formSockets->intWorkingThreadsNumberMax);
	AddToLog(stbarThreads->Panels->Items[1]->Text);
}
//---------------------------------------------------------------------------
