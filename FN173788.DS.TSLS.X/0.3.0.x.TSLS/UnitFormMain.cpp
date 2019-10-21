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
	if(dmSockets->csOut1->Active || dmSockets->csOut2->Active || dmSockets->csOut3->Active || dmSockets->csOut4->Active)
	{
	//  Защита срещу затваряне на приложението при наличие на необслужени заявки.
	//  За да се стигне до тази точка, обработката трябва да бъде по-продължителна (~ sec).
		Action = caNone;
		String str = "There are pending requests #" +
					 IntToStr(dmSockets->GetPendingReq()) + ". " +
					 "Cannot close.";
		ShowMessage(str);
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

