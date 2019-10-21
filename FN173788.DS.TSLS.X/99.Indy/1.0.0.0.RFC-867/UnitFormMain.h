//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdDayTimeServer.hpp>
#include <IdContext.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <System.Win.ScktComp.hpp>
#include <IdDayTime.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//---------------------------------------------------------------------------
class TformMain : public TForm
{
__published:	// IDE-managed Components
	TIdDayTimeServer *IdDayTimeServer;
	TGroupBox *gbSync;
	TButton *btnSync;
	TMemo *memoLog;
	TIdDayTime *IdDayTime;
	void __fastcall btnSyncClick(TObject *Sender);
	void __fastcall IdDayTimeWorkEnd(TObject *ASender, TWorkMode AWorkMode);


private:	// User declarations
public:		// User declarations
	__fastcall TformMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformMain *formMain;
//---------------------------------------------------------------------------
#endif

