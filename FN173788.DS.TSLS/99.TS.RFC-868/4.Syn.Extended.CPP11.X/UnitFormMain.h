//---------------------------------------------------------------------------

#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
const String STR_LOG_FILE = "Log.txt";
//---------------------------------------------------------------------------
class TformMain : public TForm
{
__published:	// IDE-managed Components
	TMemo *memoLogs;
	TGroupBox *gbControl;
	TGroupBox *gbSync;
	TLabel *labelIPAddress;
	TComboBox *cboxIPAddress;
	TButton *buttonSync;
	TGroupBox *gbUTC;
	TLabeledEdit *leditUTC;
	TCheckBox *cbSetTime;
	TCheckBox *cbUTC;
	TCheckBox *cbLog;
	TStatusBar *stbarThreads;
	TCheckBox *cbMNT;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall buttonSyncClick(TObject *Sender);
	void __fastcall cbUTCClick(TObject *Sender);
	void __fastcall cbLogClick(TObject *Sender);
	void __fastcall stbarThreadsDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TformMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformMain *formMain;
//---------------------------------------------------------------------------
#endif
