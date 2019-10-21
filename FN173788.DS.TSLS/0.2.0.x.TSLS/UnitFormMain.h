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
const String stringShowHideLogCaptionShow 	= "+";
const String stringShowHideLogCaptionHide 	= "-";
const String stringShowHideLogHintShow 		= "Show Log";
const String stringShowHideLogHintHide 		= "Hide Log";
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
	void __fastcall labelShowHideLogClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall buttonSyncClick(TObject *Sender);

private:	// User declarations
	String stringVersion;

public:		// User declarations
	__fastcall TformMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformMain *formMain;
//---------------------------------------------------------------------------
#endif
