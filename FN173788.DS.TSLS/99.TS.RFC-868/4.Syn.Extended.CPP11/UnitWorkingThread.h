//---------------------------------------------------------------------------

#ifndef UnitWorkingThreadH
#define UnitWorkingThreadH
//---------------------------------------------------------------------------
#include <System.Win.ScktComp.hpp>
//---------------------------------------------------------------------------
typedef TCustomWinSocket* Item;
//---------------------------------------------------------------------------
void DoWork(Item c);    // �������� ������� �� ������������ �����
unsigned long __fastcall SysTimeToUL(SYSTEMTIME& stTime);
void __fastcall UpdateCaption(String& buf1, String& buf2, Item cwsMyClient);
//---------------------------------------------------------------------------
#endif
