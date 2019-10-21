//---------------------------------------------------------------------------

#ifndef UnitFormSocketsH
#define UnitFormSocketsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Win.ScktComp.hpp>
//---------------------------------------------------------------------------
//#include <list>
#include <queue>
using namespace std;
				// Елемент на опашка без приоритет
typedef TCustomWinSocket* Item;
//---------------------------------------------------------------------------
#define USE_DATETIME

void __fastcall AddToLog(Item sock, String msg);
void __fastcall AddToLog(String msg);
//---------------------------------------------------------------------------
class TformSockets : public TForm
{
__published:	// IDE-managed Components
	TServerSocket *ssSocket;
	TClientSocket *csSocket;
	void __fastcall ssSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssSocketClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssSocketClientError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
		  int &ErrorCode);
	void __fastcall csSocketConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csSocketDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csSocketError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
		  int &ErrorCode);
	void __fastcall csSocketRead(TObject *Sender, TCustomWinSocket *Socket);


private:	// User declarations
	// Опашка без приоритет за заявките
	//queue < Item, list< Item > > Queue; 	// underlying container is list
	queue < Item > Queue;			// default underlying container - dequeue
	Item cwsMyClient;  				// Текущ клиент

	void __fastcall QueueInsert(Item cwsItem);
	Item __fastcall QueueRemove(void);

	void __fastcall RequestProcessing(void);

public:		// User declarations
	__fastcall TformSockets(TComponent* Owner);

	void __fastcall ULToSysTime(unsigned long ulTime);
	unsigned long __fastcall SysTimeToUL(SYSTEMTIME& stTime);
	SYSTEMTIME    stNew;
};
//---------------------------------------------------------------------------
extern PACKAGE TformSockets *formSockets;
//---------------------------------------------------------------------------
#endif
