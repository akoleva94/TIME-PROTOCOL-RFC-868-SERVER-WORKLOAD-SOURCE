//---------------------------------------------------------------------------

#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
const String strLogFilePrefix           = "Log";
const String strLogFileExpension        = ".txt";
//---------------------------------------------------------------------------
class TformMain : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *gboxLog;
	TGroupBox *gboxSync;
	TButton *buttonSync;
	TMemo *memoLog;
	TPopupMenu *pupLog;
	TMenuItem *miSave;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall buttonSyncClick(TObject *Sender);
	void __fastcall miSaveClick(TObject *Sender);

private:	// User declarations

public:		// User declarations
	__fastcall TformMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformMain *formMain;
//---------------------------------------------------------------------------
#endif
