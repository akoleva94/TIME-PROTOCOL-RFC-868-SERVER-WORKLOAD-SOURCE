//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <thread>
//---------------------------------------------------------------------------
const int INT_FILE_VOLUME = 256*1024*1024;	// 256 MB
const String STR_FILE_PATH = "F:\\TMP\\";
const String STR_FILE_NAME = STR_FILE_PATH + "FileStream.txt";
//---------------------------------------------------------------------------
class TformMain : public TForm
{
__published:	// IDE-managed Components
	TRadioGroup *rgMode;
	TButton *buttonStart;
	TTimer *timerClock;
	TStatusBar *stbarClock;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall timerClockTimer(TObject *Sender);
	void __fastcall buttonStartClick(TObject *Sender);

private:	// User declarations
	std::thread threadBackground;
	void Store(const String& file_name, const int file_volume);

public:		// User declarations
	__fastcall TformMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformMain *formMain;
//---------------------------------------------------------------------------
#endif
