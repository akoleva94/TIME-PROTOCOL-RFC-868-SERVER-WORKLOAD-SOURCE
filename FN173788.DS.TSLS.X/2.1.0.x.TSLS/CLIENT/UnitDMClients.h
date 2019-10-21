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
#define __DYNAMIC__
#define __LAMBDA_THREAD__
#include "UnitThreadWorking.h"
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

	 	int intLocalPort;
		std::pair<TTime, int> pairREQ;
		std::pair<TTime, int> pairCNC;
		std::pair<TTime, int> pairDSC;
		std::pair<TTime, int> pairRPL;
		std::pair<TTime, int> pairERR;
		unsigned long rpl;

        __fastcall Client(void);
		void __fastcall Init(void);
	};

	//  ��������������� ��������� �� ������ TSP �������
	class Parameters
	{
	public:
		// ������ Form
		int intLeft;                    // ���������� �� ����� ���� �������� �����
		int intTop;                     // ���������� �� ������ ���� �� �������� �����
		// ������ Log
		bool boolLogAuto;				// ����������� ������������ �� ���������
		bool boolLogVisible;            // ������������ ��� �������� �� ������������
		int intLogHeight;               // �������� �� ������ � ���������
		// ������ TimeServer
		String strIPAddress;            // IP ����� �� TP �������
		// ������ Package
		int intVolume;                  // ���� �� ������ � ����������� ������
		bool boolConsecutive;           // �������������� ����� �� �������� �� ��������
		int intDelayToFree;             // ������ �� ��������� �� �������� � �������
		// ������ Report
		String strReportFileNamePrefix;
		String strReportFileVersion;
		const String strReportFileExt = ".csv";
		// ������ Debug
		bool boolL1;					// �������� ���� 1
		bool boolL2;					// �������� ���� 2
		bool boolL3;					// �������� ���� 3

		Parameters& operator=(Parameters& src)
		{
			intLeft         = src.intLeft;
			intTop          = src.intTop;

			boolLogAuto		= src.boolLogAuto;
			boolLogVisible	= src.boolLogVisible;
			intLogHeight	= src.intLogHeight;

			strIPAddress 	= src.strIPAddress;

			intVolume 		= src.intVolume;
			boolConsecutive = src.boolConsecutive;
			intDelayToFree 	= src.intDelayToFree;

			strReportFileNamePrefix 	= src.strReportFileNamePrefix;
			strReportFileVersion 		= src.strReportFileVersion;

			boolL1			= src.boolL1;
			boolL2			= src.boolL2;
			boolL3			= src.boolL3;

			return *this;
		}
	};

	//  ����� TSP �������
	class ClientsPack
	{
	public:
		std::vector<Client*> vClients;		// ������� � ������
		std::atomic<int> intPending;		// ��� ���� ����������� �������
		std::atomic<int> intCNC;			// ������� �� ������
		std::atomic<int> intERR;			// ������� � ���������� ������
		std::atomic<bool> boolSyncing;		// �������� ��������� �� ������ �������

		TClientSocket* csOutBase;
		TDateTime dtTsyn;					// Tsyn
		TDateTime dtT0;						// T0
		TDateTime dtTend;					// Tend

		// ��������������� ���������
		tsp::Parameters Parameters;

		void __fastcall Init(TClientSocket* csOut, tsp::Parameters& p);
		String __fastcall ToMilliSeconds(TTime t, bool boolFormat = false);
		void __fastcall Save(void);
	};


	//  ������� LOG � �������
	class Log
	{
	private:
		std::vector<String> Lines;

	public:
		__fastcall Log(void) {}
		void __fastcall Clear(void)     { Lines.clear(); }
		void __fastcall Add(String str, bool boolStopper);
		void __fastcall Add(TCustomWinSocket* sock, String str, bool boolStopper);
		void __fastcall Show(TMemo* dst, bool boolStopper);
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
	// ���������� �� �����������  ///////////////////////////////////////////
	int intSession;                 // ����� �� ������� �����

	tsp::ClientsPack clientsPackStat;	// �������� ����� TS �������
	tsp::Log logStat;                   // �������� �������� �������� � �������

	tsp::ClientsPack* clientsPack;		// ��������� ����� TS �������
	tsp::Log* log;					// ��������� �������� �������� � �������

	// ��������������� ���� /////////////////////////////////////////////////
	TIniFile* iniFile;
	String strIniFileName;

	// ��������������� ���������
	tsp::Parameters Parameters;

	void __fastcall __read_ini_file(tsp::Parameters& dst);
	void __fastcall __write_ini_file(void);
	int __fastcall GetChannelId(TObject *Sender);

public:		// User declarations
	__fastcall TdmClients(TComponent* Owner);
	__fastcall ~TdmClients(void);

	bool __fastcall IsSyncing(void) 		{ return clientsPack->boolSyncing; }
	int __fastcall GetPending(void) 		{ return clientsPack->intPending; }
	TDateTime& __fastcall GetTSyn(void)		{ return clientsPack->dtTsyn; }


	void __fastcall SendBatchOfReq(void);   // ��������� ����� �� ������
	void __fastcall Save(void)				{ clientsPack->Save(); }

	const tsp::Parameters& GetParameters(void)    { return Parameters; }

	friend void DoWork(Item c, int id, int delay, TObject* o);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmClients *dmClients;
//---------------------------------------------------------------------------
#endif
