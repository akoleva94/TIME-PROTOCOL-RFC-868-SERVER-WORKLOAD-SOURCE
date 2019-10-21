//---------------------------------------------------------------------------

#ifndef UnitUtilsH
#define UnitUtilsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Win.ScktComp.hpp>
//---------------------------------------------------------------------------
bool __fastcall IsTimeZero(TTime t);

String __fastcall GetTSLSVersion(void);

void __fastcall AddToLog(String str);
void __fastcall AddToLog(TCustomWinSocket* sock, String str);
//---------------------------------------------------------------------------
#endif
