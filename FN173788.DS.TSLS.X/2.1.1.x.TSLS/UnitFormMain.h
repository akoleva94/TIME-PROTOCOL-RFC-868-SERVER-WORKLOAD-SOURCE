//---------------------------------------------------------------------------

#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
const String strShowHideLogCaptionShow 	= "+";
const String strShowHideLogCaptionHide 	= "-";
const String strShowHideLogHintShow 	= "Show Log";
const String strShowHideLogHintHide 	= "Hide Log";
//---------------------------------------------------------------------------
const String strLogFilePrefix           = "Log";
const String strLogFileExpension        = ".txt";
//---------------------------------------------------------------------------
class TformMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *panelShowHideProtocol;
	TLabel *labelShowHideLog;
	TGroupBox *gboxSync;
	TButton *buttonSync;
	TBevel *bevelShowHideProtokol;
	TGroupBox *gboxLog;
	TMemo *memoLog;
	TPopupMenu *pupLog;
	TMenuItem *miClearLog;
	TMenuItem *miSaveLog;
	TMenuItem *miSaveReport;
	TMenuItem *N1;
	void __fastcall labelShowHideLogClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall buttonSyncClick(TObject *Sender);
	void __fastcall miClearLogClick(TObject *Sender);
	void __fastcall miSaveLogClick(TObject *Sender);
	void __fastcall miSaveReportClick(TObject *Sender);

private:	// User declarations
	String strVersion;

public:		// User declarations
	__fastcall TformMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformMain *formMain;
//---------------------------------------------------------------------------
#endif
