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
  cwsMyClient = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::csSocketConnect(TObject *Sender, TCustomWinSocket *Socket)

{
/* TODO :
Add Record to Log:
<Server>::<IP> CONNECTED */
	AddToLog(Socket, "CNC");
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::csSocketDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
/* TODO :
Add Record to Log:
<Server>::<IP> DISCONNECTED */
	AddToLog(Socket, "DSC");
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
	{   // ֳנורום מעדמגמנ
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
	as.cat_printf(L" [%0X]", ulTime);

	AddToLog(as);
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

#if defined(USE_DATETIME)
/* TODO : SYSTEMTIME to TDateTime */
	TDateTime dtNew = SystemTimeToDateTime(stNew);

/* TODO : Increment TDateTime with ulTime */
	dtNew = IncSecond(dtNew, ulTime);

/* TODO : TDateTime to SYSTEMTIME */
	DateTimeToSystemTime(dtNew, stNew);

#else
  FILETIME      ftNew;  // FILETIME and LARGE_INTEGER used
  LARGE_INTEGER li;     // for time calculations

		// SYSTEMTIME to FILETIME
/* TODO : SYSTEMTIME to FILETIME */

		// STEP 1: FILETIME to LARGE_INTEGER
/* TODO : FILETIME to LARGE_INTEGER */

		// STEP 2: Add ulTime as offset from 0:00:00 of 01.01.1900
		//      Note1: (LONGLONG)10000000 is scale factor for 100ns intervals
		//      Note2: LONGLONG QuadPart is 64 bit representation
		//             of LARGE_INTEGER data type
/* TODO : Calculate Current Time in LONGLONG */

		// STEP 3: LARGE_INTEGER to FILETIME
/* TODO : LARGE_INTEGER to FILETIME */

		// FILETIME to SYSTEMTIME
/* TODO : FILETIME to SYSTEMTIME */
#endif
}
//---------------------------------------------------------------------------
unsigned long __fastcall TformSockets::SysTimeToUL(SYSTEMTIME& stTime)
{
  SYSTEMTIME    stBase;

  stBase.wYear         = 1900;
  stBase.wMonth        = 1;
  stBase.wDay          = 1;
  stBase.wHour         = 0;
  stBase.wMinute       = 0;
  stBase.wSecond       = 0;
  stBase.wMilliseconds = 0;

#if defined(USE_DATETIME)
/* TODO : SYSTEMTIME to TDateTime */

/* TODO : Calculate Time Difference */

#else
  FILETIME      ftBase, ftTime;  // FILETIME and LARGE_INTEGER used
  LARGE_INTEGER liBase, liTime;     // for time calculations
/* TODO : SYSTEMTIME to FILETIME */
/* TODO : FILETIME to LARGE_INTEGER */

/* TODO : SYSTEMTIME to FILETIME */
/* TODO : FILETIME to LARGE_INTEGER */

/* TODO : Calculate Time Difference */

#endif
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::ssSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket)
{
/* TODO :
Add Record to Log:
<Client>::<IP> CONNECTED */

/* TODO : OnConnect */
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::ssSocketClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)

{
/* TODO :
Add Record to Log:
<Client>::<IP> DISCONNECTED */

/* TODO : OnDisconnect */
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::ssSocketClientError(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode)
{
/* TODO :
Add Record to Log:
<Socket Error#> <Error Code> */

/* TODO : OnError */
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::RequestProcessing(void)
{
  unsigned long ulTime, ulTimeClient;

/* TODO : Get Current System Time */

/* TODO : Calculate ulTime */

/* TODO : Convert ulTime to TCP/IP Order */

  String as;
  as.printf(L"%4d.%02d.%02d %02d:%02d:%02d",
	stNew.wYear, stNew.wMonth, stNew.wDay,
	stNew.wHour, stNew.wMinute, stNew.wSecond);

  formMain->leditUTC->Text = as;
  as.cat_printf(L" [%0X]", ulTime);

  formMain->memoLogs->Lines->Add(as);

/* TODO : Reply to Current Client */
}
//---------------------------------------------------------------------------
void __fastcall TformSockets::QueueInsert(Item cwsItem)
{
/* TODO : Queue Request */
}
//---------------------------------------------------------------------------
Item __fastcall TformSockets::QueueRemove(void)
{
/* TODO : Retrieve Request form Queue */
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

