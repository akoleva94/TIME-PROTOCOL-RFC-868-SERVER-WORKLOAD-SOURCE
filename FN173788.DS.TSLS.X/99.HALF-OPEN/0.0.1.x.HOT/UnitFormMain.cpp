//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormMain.h"
#include "UnitDMChannels.h"
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
void __fastcall TformMain::FormShow(TObject *Sender)
{
	if(buttonSync->Enabled)
	{
		buttonSync->SetFocus();
    }
}
//---------------------------------------------------------------------------
void __fastcall TformMain::buttonSyncClick(TObject *Sender)
{
	dmChannels->Sync();
}
//---------------------------------------------------------------------------
void __fastcall TformMain::miSaveClick(TObject *Sender)
{
	String stringLogFileNamePath = ExtractFilePath(Application->ExeName);
	String strLogFileName = strLogFilePrefix + "." +
                            dmChannels->GetMode() + "." +
							FormatDateTime("yyyymmdd.hhmmss", Date() + Time()) +
							strLogFileExpension;
	try
	{
		memoLog->Lines->SaveToFile(stringLogFileNamePath + strLogFileName);
		MessageDlg(strLogFileName + " saved", mtInformation, TMsgDlgButtons() << mbOK, 0);
	}
	catch(Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);
	}
}
//---------------------------------------------------------------------------

