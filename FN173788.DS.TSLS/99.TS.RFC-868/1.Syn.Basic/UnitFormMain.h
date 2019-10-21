//---------------------------------------------------------------------------

#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
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
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall buttonSyncClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TformMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformMain *formMain;
//---------------------------------------------------------------------------
#endif
