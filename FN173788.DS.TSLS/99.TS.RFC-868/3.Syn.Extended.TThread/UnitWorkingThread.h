//---------------------------------------------------------------------------

#ifndef UnitWorkingThreadH
#define UnitWorkingThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Win.ScktComp.hpp>
//---------------------------------------------------------------------------
typedef TCustomWinSocket* Item;
//---------------------------------------------------------------------------
class WorkingThread : public TThread
{
private:
protected:
	void __fastcall Execute(void);
	unsigned long __fastcall SysTimeToUL(SYSTEMTIME& stTime);
	void __fastcall UpdateCaption(void);

	Item cwsMyClient;  				// Идентификатор на заявката/клиента
	String buf1, buf2;

public:
	__fastcall WorkingThread(Item c);
	__fastcall ~WorkingThread(void);
};
//---------------------------------------------------------------------------
#endif
