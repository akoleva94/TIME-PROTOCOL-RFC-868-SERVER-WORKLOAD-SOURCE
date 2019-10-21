//---------------------------------------------------------------------------

#ifndef UnitDMSocketsH
#define UnitDMSocketsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Win.ScktComp.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
class TdmSockets : public TDataModule
{
__published:	// IDE-managed Components
	TClientSocket *csOut1;
	TClientSocket *csOut2;
	TClientSocket *csOut3;
	TClientSocket *csOut4;
	void __fastcall csOut1Connect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csOut1Disconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csOut1Error(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
	void __fastcall csOut1Read(TObject *Sender, TCustomWinSocket *Socket);

private:	// User declarations
	// Конфигурационен файл /////////////////////////////////////////////////
	TIniFile* iniFile;
	String stringIniFileName;

	// Параметри ////////////////////////////////////////////////////////////
	String stringIPAddress;		// Time Server IP Address
	int intVolume;			    // Брой заявки в пакета
	int intDelayToFree;			// Задръжка до освобождаване на сървъра, ms

	// Променливи на състоянието
	int intPendingReq;			// брой заявки от пакета в очакване на отговор

	void __fastcall __read_ini_file(void);
	void __fastcall __write_ini_file(void);

public:		// User declarations
	__fastcall TdmSockets(TComponent* Owner);
	__fastcall ~TdmSockets(void);

	int __fastcall GetPendingReq(void) 	{ return intPendingReq; }

	void __fastcall SendBatchOfReq(void);   // формиране пакет от заявки
};
//---------------------------------------------------------------------------
extern PACKAGE TdmSockets *dmSockets;
//---------------------------------------------------------------------------
#endif
