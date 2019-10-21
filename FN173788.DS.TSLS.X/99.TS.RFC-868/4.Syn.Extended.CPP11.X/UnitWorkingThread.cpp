//---------------------------------------------------------------------------

#include <System.DateUtils.hpp>
#include <mutex>
#include <algorithm>
#pragma hdrstop

#include "UnitWorkingThread.h"
#include "UnitFormMain.h"
#include "UnitFormSockets.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
std::mutex mutex;
std::mutex mutex_max;
//---------------------------------------------------------------------------
void DoWork(Item c)
{
	//---- Place thread code here ----

	 formSockets->intWorkingThreadsNumber++; // �������� ��� �������� �����

	 {
		int x = formSockets->intWorkingThreadsNumber;
		std::lock_guard<std::mutex> guard(mutex_max);
		//
		formSockets->intWorkingThreadsNumberMax = std::max(formSockets->intWorkingThreadsNumberMax, x);
	 }

//	 if(formSockets->intWorkingThreadsNumberMax < x)
//	 {
//		formSockets->intWorkingThreadsNumberMax.exchange(x);
//	 }

	//formSockets->intWorkingThreadsNumberMax = std::max(formSockets->intWorkingThreadsNumberMax, intWorkingThreadsNumber);



	Item cwsMyClient = c;  					// ������������� �� ��������/�������

/* TODO :
Add Record to Log:
<Client>::<IP> CONNECTED */
	UpdateCaption("SERVER CNC", cwsMyClient);

/* TODO : Get Current System Time */
	SYSTEMTIME stNew;
	GetSystemTime(&stNew);

/* TODO : Calculate ulTime */
	unsigned long ulTime = SysTimeToUL(stNew);

/* TODO : Convert ulTime to TCP/IP Order */
	unsigned long ulTimeClient = htonl(ulTime);

	if(formMain->cbLog->Checked || formMain->cbUTC->Checked)
	{
		String buf1;
		buf1.printf(L"%4d.%02d.%02d %02d:%02d:%02d",
			stNew.wYear, stNew.wMonth, stNew.wDay,
			stNew.wHour, stNew.wMinute, stNew.wSecond);

		String buf2 = buf1;
		buf2.cat_printf(L" << [%0X]", ulTime);

		UpdateCaption(buf1, buf2, cwsMyClient);
	}

/* TODO : Reply to Current Client */
	cwsMyClient->SendBuf(&ulTimeClient, 4);

	formSockets->intWorkingThreadsNumber--;     // �������� ��� �������� �����
}
//---------------------------------------------------------------------------
void __fastcall UpdateCaption(const String& msg, Item cwsMyClient)
{
	// ��������� �� �������� ������ �� ������ �� ���������
	// �������� ����������� ������� �� ������� �� GUI
	std::lock_guard<std::mutex> guard(mutex);   // RAII
	//
	if(formMain->cbLog->Checked)
	{
		AddToLog(cwsMyClient, msg);
	}
}
//---------------------------------------------------------------------------
void __fastcall UpdateCaption(const String& msg1, String& msg2, Item cwsMyClient)
{
	msg2 += " #" + IntToStr(formSockets->intWorkingThreadsNumber) + " running thread(s)";

	// ��������� �� �������� ������ �� ������ �� ���������
	// �������� ����������� ������� �� ������� �� GUI
	std::lock_guard<std::mutex> guard(mutex);   // RAII
	//
	if(formMain->cbUTC->Checked)
	{
		formMain->leditUTC->Text = msg1;
	}

	if(formMain->cbLog->Checked)
	{
		AddToLog(cwsMyClient, msg2);
	}
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
