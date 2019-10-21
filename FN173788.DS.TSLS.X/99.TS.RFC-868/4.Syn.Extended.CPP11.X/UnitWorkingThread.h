//---------------------------------------------------------------------------

#ifndef UnitWorkingThreadH
#define UnitWorkingThreadH
//---------------------------------------------------------------------------
#include <System.Win.ScktComp.hpp>
//---------------------------------------------------------------------------
typedef TCustomWinSocket* Item;
//---------------------------------------------------------------------------
void DoWork(Item c);    // главната функция на обслужващата нишка
unsigned long __fastcall SysTimeToUL(SYSTEMTIME& stTime);
void __fastcall UpdateCaption(const String& msg, Item cwsMyClient);
void __fastcall UpdateCaption(const String& msg1, String& msg2, Item cwsMyClient);
//---------------------------------------------------------------------------
#endif
