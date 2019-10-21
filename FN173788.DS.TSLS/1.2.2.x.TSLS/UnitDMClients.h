//---------------------------------------------------------------------------

#ifndef UnitDMClientsH
#define UnitDMClientsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Win.ScktComp.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#include <atomic>
#include <vector>
//---------------------------------------------------------------------------
//  ПРОСТРАНСТВО НА ИМЕНАТА НА TSP (Time Server Protocol)
namespace tsp
{
	//  TSP КЛИЕНТ
	class Client
	{
	public:
		enum STATE {Closed = 0, Transient, Open} State;	// състояние
		TClientSocket* csOut;           // изходен канал на клиента
	};

	//  ПАКЕТ TSP КЛИЕНТИ
	class ClientsPack
	{
	public:
		std::vector<Client*> vClients;		// клиенти в пакета
		std::atomic<int> intPending;		// необслужени клиенти
		std::atomic<bool> boolSyncing;		// обобщено състояние на пакета клиенти
	};
}
//---------------------------------------------------------------------------
class TdmClients : public TDataModule
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
	String strIniFileName;

	// Параметри ////////////////////////////////////////////////////////////
	String strIPAddress;		// Time Server IP Address
	int intVolume;			    // Брой заявки в пакета
	int intDelayToFree;			// Задръжка до освобождаване на сървъра, ms
	bool boolConsecutive;       // Последователно формиране на заявките

	// Променливи на състоянието  ///////////////////////////////////////////
	tsp::ClientsPack clientsPack;	// пакет TS клиенти

	void __fastcall __read_ini_file(void);
	void __fastcall __write_ini_file(void);

public:		// User declarations
	__fastcall TdmClients(TComponent* Owner);
	__fastcall ~TdmClients(void);

	bool __fastcall IsSyncing(void) 	{ return clientsPack.boolSyncing; }
	int __fastcall GetPending(void) 	{ return clientsPack.intPending; }
	int __fastcall GetChannelId(TObject *Sender);

	void __fastcall SendBatchOfReq(void);   // формиране пакет от заявки
};
//---------------------------------------------------------------------------
extern PACKAGE TdmClients *dmClients;
//---------------------------------------------------------------------------
#endif
