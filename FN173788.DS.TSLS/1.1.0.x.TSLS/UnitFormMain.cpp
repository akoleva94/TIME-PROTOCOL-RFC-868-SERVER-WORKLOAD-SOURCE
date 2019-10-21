//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormMain.h"
#include "UnitUtils.h"
#include "UnitDMSockets.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformMain *formMain;
//---------------------------------------------------------------------------
__fastcall TformMain::TformMain(TComponent* Owner)
	: TForm(Owner)
{
	// Get Application Version
	stringVersion = GetTSLSVersion();
	Caption = Caption + " [ver." + stringVersion + "]";
}
//---------------------------------------------------------------------------
void __fastcall TformMain::FormShow(TObject *Sender)
{
	labelShowHideLogClick(Sender);

	buttonSync->SetFocus();
    buttonSync->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(!dmSockets->AllInactive())
	{
	//  ������ ����� ��������� �� ������������ ��� ������� �� ����������� ������.
	//  �� �� �� ������ �� ���� �����, ����������� ������ �� ���� ��-������������� (~ sec).
		Action = caNone;
		String str = "There are pending requests #" +
					 IntToStr(dmSockets->GetPendingReq()) + ". " +
					 "Cannot close.";
		MessageDlg(str, mtError, TMsgDlgButtons() << mbOK, 0);
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::buttonSyncClick(TObject *Sender)
{
	// Send Batch of Requests
	dmSockets->SendBatchOfReq();
}
//---------------------------------------------------------------------------
void __fastcall TformMain::labelShowHideLogClick(TObject *Sender)
{
	if(memoLog->Visible)
	{	// Hide Log
		labelShowHideLog->Caption = stringShowHideLogCaptionShow;
		labelShowHideLog->Hint = stringShowHideLogHintShow;

		memoLog->Hide();
		ClientHeight = ClientHeight - memoLog->Height;
	}
	else
	{	// Show Log
		labelShowHideLog->Caption = stringShowHideLogCaptionHide;
		labelShowHideLog->Hint = stringShowHideLogHintHide;

		ClientHeight = ClientHeight + memoLog->Height;
		memoLog->Show();
	}

	Top = Screen->WorkAreaHeight - Height;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::miClearClick(TObject *Sender)
{
	int ExitCode = Application->MessageBox(L"Do you want to continue?", L"The System Log will be Cleared",
		MB_YESNO|MB_ICONWARNING);
	if(ExitCode == IDNO)
		return;

    memoLog->Clear();
	buttonSync->SetFocus();
}
//---------------------------------------------------------------------------

