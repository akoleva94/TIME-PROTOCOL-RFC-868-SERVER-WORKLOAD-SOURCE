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
//  ������������ �� ������� �� TSP (Time Server Protocol)
namespace tsp
{
	//  TSP ������
	class Client
	{
	public:
		enum STATE {Closed = 0, Transient, Open} State;	// ���������
		TClientSocket* csOut;           // ������� ����� �� �������
	};

	//  ����� TSP �������
	class ClientsPack
	{
	public:
		std::vector<Client*> vClients;		// ������� � ������
		std::atomic<int> intPending;		// ����������� �������
		std::atomic<bool> boolSyncing;		// �������� ��������� �� ������ �������
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
	// ��������������� ���� /////////////////////////////////////////////////
	TIniFile* iniFile;
	String strIniFileName;

	// ��������� ////////////////////////////////////////////////////////////
	String strIPAddress;		// Time Server IP Address
	int intVolume;			    // ���� ������ � ������
	int intDelayToFree;			// �������� �� ������������� �� �������, ms
	bool boolConsecutive;       // �������������� ��������� �� ��������

	// ���������� �� �����������  ///////////////////////////////////////////
	tsp::ClientsPack clientsPack;	// ����� TS �������

	void __fastcall __read_ini_file(void);
	void __fastcall __write_ini_file(void);

public:		// User declarations
	__fastcall TdmClients(TComponent* Owner);
	__fastcall ~TdmClients(void);

	bool __fastcall IsSyncing(void) 	{ return clientsPack.boolSyncing; }
	int __fastcall GetPending(void) 	{ return clientsPack.intPending; }
	int __fastcall GetChannelId(TObject *Sender);

	void __fastcall SendBatchOfReq(void);   // ��������� ����� �� ������
};
//---------------------------------------------------------------------------
extern PACKAGE TdmClients *dmClients;
//---------------------------------------------------------------------------
#endif
