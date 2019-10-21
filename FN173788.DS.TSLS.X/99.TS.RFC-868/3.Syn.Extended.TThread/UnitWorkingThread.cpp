//---------------------------------------------------------------------------

#include <System.hpp>
#include <System.DateUtils.hpp>
#pragma hdrstop

#include "UnitWorkingThread.h"
#include "UnitFormMain.h"
#include "UnitFormSockets.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall WorkingThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall WorkingThread::WorkingThread(Item c)
	: TThread(false)
{
	cwsMyClient = c;
	// атомарна операция
	InterlockedIncrement(&formSockets->longWorkingThreadsNumber);
}
//---------------------------------------------------------------------------
__fastcall WorkingThread::~WorkingThread(void)
{
	// атомарна операция
	InterlockedDecrement(&formSockets->longWorkingThreadsNumber);
}
//---------------------------------------------------------------------------
void __fastcall WorkingThread::Execute(void)
{
	//---- Place thread code here ----

/* TODO : Get Current System Time */
	SYSTEMTIME stNew;
	GetSystemTime(&stNew);

/* TODO : Calculate ulTime */
	unsigned long ulTime = SysTimeToUL(stNew);

/* TODO : Convert ulTime to TCP/IP Order */
	unsigned long ulTimeClient = htonl(ulTime);

	buf1.printf(L"%4d.%02d.%02d %02d:%02d:%02d",
		stNew.wYear, stNew.wMonth, stNew.wDay,
		stNew.wHour, stNew.wMinute, stNew.wSecond);

	buf2 = buf1;
	buf2.cat_printf(L" << [%0X]", ulTime);

	Synchronize(&UpdateCaption);

/* TODO : Reply to Current Client */
	cwsMyClient->SendBuf(&ulTimeClient, 4);

	delete this;
}
//---------------------------------------------------------------------------
void __fastcall WorkingThread::UpdateCaption(void)
{
	formMain->leditUTC->Text = buf1;
	buf2 += " #" + IntToStr(static_cast< int >(formSockets->longWorkingThreadsNumber)) + " running thread(s)";
	AddToLog(cwsMyClient, buf2);
}
//---------------------------------------------------------------------------
unsigned long __fastcall WorkingThread::SysTimeToUL(SYSTEMTIME& stTime)
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

