//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <chrono>
#include <memory>
#include <string>
//---------------------------------------------------------------------------
#include "UnitMain.h"
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
	stbarClock->Panels->Items[1]->Text = Time();
}
//---------------------------------------------------------------------------
void __fastcall TformMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(threadBackground.joinable())
	{
        // Block main thread until background finishes
        threadBackground.join();
    }
}
//---------------------------------------------------------------------------
void __fastcall TformMain::buttonStartClick(TObject *Sender)
{
  if(rgMode->ItemIndex == 0)
  { // Single Task Mode
	Store(STR_FILE_NAME, INT_FILE_VOLUME);
  }
  else
  { // Background Task Mode
	// Deferred start of background thread for single cycle execution
    // Pass two parameters to the thread
	threadBackground = std::thread(Store, STR_FILE_NAME, INT_FILE_VOLUME);
  }
}
//---------------------------------------------------------------------------
void __fastcall TformMain::timerClockTimer(TObject *Sender)
{
	stbarClock->Panels->Items[1]->Text = Time();
}
//---------------------------------------------------------------------------
void TformMain::Store(const String& file_name, const int file_volume)
{
	formMain->buttonStart->Enabled = false;
	rgMode->Enabled = false;
	Screen->Cursor = crHourGlass;

	stbarClock->Panels->Items[0]->Text = "Wait...";

	auto beg = std::chrono::high_resolution_clock::now();

	std::unique_ptr<TMemoryStream> msBuffer(new TMemoryStream);

	msBuffer->Clear();

	try
	{
	  for(int i = 0; i < file_volume; i++)
		msBuffer->Write("x", 1);

	  msBuffer->SaveToFile(file_name);
	}
	__finally
	{
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::milliseconds dur_in_milli = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);
		std::wstring strDur = std::to_wstring(dur_in_milli.count()) + L", ms";
		stbarClock->Panels->Items[0]->Text = strDur.c_str();

		buttonStart->Enabled = true;
		rgMode->Enabled = true;
		Screen->Cursor = crDefault;
	}
}
//---------------------------------------------------------------------------

