//---------------------------------------------------------------------------

#include <System.DateUtils.hpp>
#include <mutex>
#pragma hdrstop

#include "UnitWorkingThread.h"
#include "UnitFormMain.h"
#include "UnitFormSockets.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
std::mutex mutex;
//---------------------------------------------------------------------------
void DoWork(Item c)
{
	//---- Place thread code here ----
	formSockets->intWorkingThreadsNumber++; // операция над атомарен обект

	Item cwsMyClient = c;  					// Идентификатор на заявката/клиента

/* TODO : Get Current System Time */
	SYSTEMTIME stNew;
	GetSystemTime(&stNew);

/* TODO : Calculate ulTime */
	unsigned long ulTime = SysTimeToUL(stNew);

/* TODO : Convert ulTime to TCP/IP Order */
	unsigned long ulTimeClient = htonl(ulTime);

	String buf1;
	buf1.printf(L"%4d.%02d.%02d %02d:%02d:%02d",
		stNew.wYear, stNew.wMonth, stNew.wDay,
		stNew.wHour, stNew.wMinute, stNew.wSecond);

	String buf2 = buf1;
	buf2.cat_printf(L" << [%0X]", ulTime);

	UpdateCaption(buf1, buf2, cwsMyClient);

/* TODO : Reply to Current Client */
	cwsMyClient->SendBuf(&ulTimeClient, 4);

	formSockets->intWorkingThreadsNumber--;     // операция над атомарен обект
}
//---------------------------------------------------------------------------
void __fastcall UpdateCaption(String& buf1, String& buf2, Item cwsMyClient)
{
	buf2 += " #" + IntToStr(formSockets->intWorkingThreadsNumber) + " running thread(s)";

	// формиране на критична секция до изхода на функцията
	// секцията сериализира достъпа на нишките до GUI
	std::lock_guard<std::mutex> guard(mutex);   // RAII
	//
	formMain->leditUTC->Text = buf1;
	AddToLog(cwsMyClient, buf2);
}
//---------------------------------------------------------------------------
unsigned long __fastcall SysTimeToUL(SYSTEMTIME& stTime)
{
	SYSTEMTIME    stBase;

	stBase.wYear         = 1900;
	stBase.wMonth        = 1;
	stBase.wDay          = 1;
	stBase.wHour         = 0;
	stBase.wMinute       = 0;
	stBase.wSecond       = 0;
	stBase.wMilliseconds = 0;

/* TODO : SYSTEMTIME to TDateTime */
	TDateTime dtBase = SystemTimeToDateTime(stBase);
	TDateTime dtTime = SystemTimeToDateTime(stTime);

/* TODO : Calculate Time Difference */
	return SecondsBetween(dtTime, dtBase);
}
//---------------------------------------------------------------------------

