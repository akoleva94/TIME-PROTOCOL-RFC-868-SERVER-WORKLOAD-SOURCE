//---------------------------------------------------------------------------

#include <vcl.h>
#include <system.dateutils.hpp>
#pragma hdrstop

#include "UnitFormSockets.h"
#include "UnitFormMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformSockets *formSockets;
//---------------------------------------------------------------------------
__fastcall TformSockets::TformSockets(TComponent* Owner)
	: TForm(Owner)
{
	longWorkingThreadsNumber = 0;
}
//---------------------------------------------------------------------------
// КЛИЕНТСКА ЧАСТ ///////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
void __fastcall TformSockets::csSocketConnect(TObject *Sender, TCustomWinSocket *Socket)

{
/* TODO :
Add Record to Log:
<Server>::<IP> CONNECTED */
	AddToLog(Socket, "CLIENT CNC");
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::csSocketDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
/* TODO :
Add Record to Log:
<Server>::<IP> DISCONNECTED */
	AddToLog(Socket, "CLIENT DSC");
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::csSocketError(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode)
{
/* TODO :
Add Record to Log:
<Socket Error#> <Error Code> */
	AddToLog("Socket Error# " + IntToStr(ErrorCode));

/* TODO : Tolerate Error */
	ErrorCode = 0;
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::csSocketRead(TObject *Sender, TCustomWinSocket *Socket)
{
	unsigned long ulTime;

/* TODO : Get Reply */
	int intBytesReceived = Socket->ReceiveBuf(&ulTime, 4);
	if(intBytesReceived != 4)
	{   // Грешен отговор
		String msg = "Error: " + IntToStr(intBytesReceived) + " bytes received";
		ShowMessage(msg);
		return;
	}

/* TODO : Convert to Host Order */
	ulTime = ntohl(ulTime);

/* TODO : Convert to SYSTEMTIME */
	ULToSysTime(ulTime);

/* TODO : Set System Clock */
	if(formMain->cbSetTime->Checked)
	{
		if(!SetSystemTime(&stNew))
		{
			ShowMessage("Error: Cannot set system time");
		}
	}

	String as;
	as.printf(L"%4d.%02d.%02d %02d:%02d:%02d",
	stNew.wYear, stNew.wMonth, stNew.wDay,
	stNew.wHour, stNew.wMinute, stNew.wSecond);

	formMain->leditUTC->Text = as;
	as.cat_printf(L" >> [%0X]", ulTime);

	AddToLog(Socket, as);
    Sleep(3000);    // задръжка за визуализация на вмъкването в опашката
	Socket->Close();
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::ULToSysTime(unsigned long ulTime)
{
	stNew.wYear         = 1900;
	stNew.wMonth        = 1;
	stNew.wDay          = 1;
	stNew.wHour         = 0;
	stNew.wMinute       = 0;
	stNew.wSecond       = 0;
	stNew.wMilliseconds = 0;

/* TODO : SYSTEMTIME to TDateTime */
	TDateTime dtNew = SystemTimeToDateTime(stNew);

/* TODO : Increment TDateTime with ulTime */
	dtNew = IncSecond(dtNew, ulTime);

/* TODO : TDateTime to SYSTEMTIME */
	DateTimeToSystemTime(dtNew, stNew);
}
//---------------------------------------------------------------------------
// СЪРВЪРНА ЧАСТ ////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
void __fastcall TformSockets::ssSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket)
{
/* TODO :
Add Record to Log:
<Client>::<IP> CONNECTED */
	AddToLog(Socket, "SERVER CNC");

/* TODO : OnConnect */
    new WorkingThread(Socket);      // създаване/стартиране на обслужваща нишка
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::ssSocketClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)

{
/* TODO :
Add Record to Log:
<Client>::<IP> DISCONNECTED */
	AddToLog(Socket, "SERVER DSC");

/* TODO : OnDisconnect */
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::ssSocketClientError(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode)
{
/* TODO :
Add Record to Log:
<Socket Error#> <Error Code> */
	AddToLog("Socket Error# " + IntToStr(ErrorCode));

/* TODO : OnError */
	ErrorCode = 0;
}
//---------------------------------------------------------------------------
void __fastcall AddToLog(Item sock, String msg)
{
  String buf = Time().TimeString() + " [" +
			   sock->RemoteHost + "::" + sock->RemoteAddress + "] " +
			   msg;
  formMain->memoLogs->Lines->Add(buf);
}
//---------------------------------------------------------------------------
void __fastcall AddToLog(String msg)
{
  String buf = Time().TimeString() + " " + msg;
  formMain->memoLogs->Lines->Add(buf);
}
//---------------------------------------------------------------------------

