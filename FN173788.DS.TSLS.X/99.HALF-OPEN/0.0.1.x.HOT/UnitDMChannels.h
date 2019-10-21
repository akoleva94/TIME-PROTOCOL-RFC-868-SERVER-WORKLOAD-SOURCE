//---------------------------------------------------------------------------

#ifndef UnitDMChannelsH
#define UnitDMChannelsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Win.ScktComp.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
void __fastcall AddToLog(String str);
void __fastcall AddToLog(TCustomWinSocket* sock, String str);
//---------------------------------------------------------------------------
class TdmChannels : public TDataModule
{
__published:	// IDE-managed Components
	TClientSocket *csMasterToSlave1;
	TClientSocket *csMasterToSlave2;
	TClientSocket *csMasterToSlave3;
	TClientSocket *csMasterToSlave4;
	TServerSocket *ssInTarget;
	TServerSocket *ssInSlave;
	TClientSocket *csClient;
	void __fastcall csMasterToSlave1Connect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csMasterToSlave1Disconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csMasterToSlave1Error(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
		  int &ErrorCode);
	void __fastcall csMasterToSlave1Read(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssInSlaveClientConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssInSlaveClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssInSlaveClientError(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall ssInSlaveClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csClientConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall csClientError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
		  int &ErrorCode);
	void __fastcall csClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssInTargetClientConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssInTargetClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssInTargetClientError(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall ssInTargetClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall DataModuleDestroy(TObject *Sender);

private:	// User declarations
	TIniFile* iniFile;
    String strIniFileName;

	bool boolMasterSwitch;
	bool boolSlaveSwitch;
	bool boolTargetSwitch;
	String strMode;

	String strSlaveId;
	const int intVolume = 20;   	// обем на пакета заявки
	std::vector <TClientSocket*> vClients;

	void __fastcall __read_ini_file(void);
	void __fastcall __write_ini_file(void);
	int __fastcall GetClientId(TObject *Sender);

public:		// User declarations
	__fastcall TdmChannels(TComponent* Owner);
	void __fastcall Sync(void);
    String GetMode(void)    { return strMode; }
};
//---------------------------------------------------------------------------
extern PACKAGE TdmChannels *dmChannels;
//---------------------------------------------------------------------------
#endif
