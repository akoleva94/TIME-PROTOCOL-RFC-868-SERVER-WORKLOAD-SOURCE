//---------------------------------------------------------------------------

#ifndef UnitDMSocketsH
#define UnitDMSocketsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Win.ScktComp.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
class TdmSockets : public TDataModule
{
__published:	// IDE-managed Components
	TClientSocket *csOut;
	void __fastcall csOutConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csOutDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csOutError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
	void __fastcall csOutRead(TObject *Sender, TCustomWinSocket *Socket);

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

	// Сокети ///////////////////////////////////////////////////////////////
	std::vector<TClientSocket *> vcsOut;

	void __fastcall __read_ini_file(void);
	void __fastcall __write_ini_file(void);

public:		// User declarations
	__fastcall TdmSockets(TComponent* Owner);
	__fastcall ~TdmSockets(void);

	bool __fastcall AllActive(void);
	bool __fastcall AllInactive(void);
	int __fastcall GetChannelId(TObject *Sender);

	int __fastcall GetPendingReq(void) 	{ return intPendingReq; }

	void __fastcall SendBatchOfReq(void);   // формиране пакет от заявки
};
//---------------------------------------------------------------------------
extern PACKAGE TdmSockets *dmSockets;
//---------------------------------------------------------------------------
#endif
