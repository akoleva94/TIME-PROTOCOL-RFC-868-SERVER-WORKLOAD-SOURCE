//---------------------------------------------------------------------------

#include <Vcl.Dialogs.hpp>
#pragma hdrstop

#include "UnitDMChannels.h"
#include "UnitFormMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
TdmChannels *dmChannels;
//---------------------------------------------------------------------------
__fastcall TdmChannels::TdmChannels(TComponent* Owner)
	: TDataModule(Owner)
{
	boolMasterSwitch	= false;
	boolSlaveSwitch		= false;
	boolTargetSwitch	= false;

    strSlaveId = "?";

    formMain->buttonSync->Enabled = false;

	__read_ini_file();	// четене на параметрите от конфигурационния файл
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::DataModuleDestroy(TObject *Sender)
{
    __write_ini_file();
	delete iniFile;
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::__read_ini_file(void)
{
	strIniFileName = Application->ExeName;
	strIniFileName = strIniFileName.SubString(1, strIniFileName.Length() - 3) + "ini";

	iniFile = new TIniFile(strIniFileName);
	if(!FileExists(strIniFileName))
	{
		MessageDlg("Missing configuration file!", mtError, TMsgDlgButtons() << mbOK, 0);
		return;
	}

	boolMasterSwitch 	= iniFile->ReadBool(L"Master", L"Switch", 0);
	boolSlaveSwitch 	= iniFile->ReadBool(L"Slave", L"Switch", 0);
	boolTargetSwitch 	= iniFile->ReadBool(L"Target", L"Switch", 0);

	if(boolMasterSwitch)
	{	// Master Mode
		csMasterToSlave1->Port  = iniFile->ReadInteger(L"Master", L"1SlavePort", 0);
		csMasterToSlave1->Address  = iniFile->ReadString(L"Master", L"1SlaveAddr", L"");

		csMasterToSlave2->Port  = iniFile->ReadInteger(L"Master", L"2SlavePort", 0);
		csMasterToSlave2->Address  = iniFile->ReadString(L"Master", L"2SlaveAddr", L"");

		csMasterToSlave3->Port  = iniFile->ReadInteger(L"Master", L"3SlavePort", 0);
		csMasterToSlave3->Address  = iniFile->ReadString(L"Master", L"3SlaveAddr", L"");

		csMasterToSlave4->Port  = iniFile->ReadInteger(L"Master", L"4SlavePort", 0);
		csMasterToSlave4->Address  = iniFile->ReadString(L"Master", L"4SlaveAddr", L"");

		formMain->buttonSync->Enabled = true;
		strMode = "Master";
		formMain->Caption += " [" + strMode + "]";
	}
	else if(boolSlaveSwitch)
	{   // Slave Mode
		strSlaveId = iniFile->ReadString(L"Slave", L"Id", L"?");
		ssInSlave->Port 	= iniFile->ReadInteger(L"Slave", L"SlavePort", 0);

		int intTargetPort 	= iniFile->ReadInteger(L"Slave", L"TargetPort", 0);
		String strTargetAddr = iniFile->ReadString(L"Slave", L"TargetAddr", L"");

		for(int i = 0; i < intVolume; i++)
		{
			TClientSocket* cs = new TClientSocket(Owner);

			cs->Port 	= intTargetPort;
			cs->Address = strTargetAddr;

			cs->OnConnect = csClient->OnConnect;
			cs->OnDisconnect = csClient->OnDisconnect;
			cs->OnError = csClient->OnError;
			cs->OnRead = csClient->OnRead;

			vClients.push_back(cs);
		}

		ssInSlave->Open();

		formMain->buttonSync->Enabled = false;
		strMode = "Slave" + strSlaveId;
		formMain->Caption += " [" + strMode + "]";
	}
	else if(boolTargetSwitch)
	{   // Target Mode
		ssInTarget->Port 	= iniFile->ReadInteger(L"Target", L"TargetPort", 0);

		ssInTarget->Open();

		formMain->buttonSync->Enabled = false;
		strMode = "Target";
		formMain->Caption += " [" + strMode + "]";
	}

	formMain->Top   = iniFile->ReadInteger(L"FormPos", L"Top", 0);
	formMain->Left  = iniFile->ReadInteger(L"FormPos", L"Left", 0);
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::__write_ini_file(void)
{
	try
	{
		iniFile->WriteInteger("FormPos", "Top", formMain->Top);
		iniFile->WriteInteger("FormPos", "Left", formMain->Left);
	}
	catch(Exception& e)
	{
		MessageDlg(e.Message, mtError, TMsgDlgButtons() << mbOK, 0);
	}
}
//---------------------------------------------------------------------------
int __fastcall TdmChannels::GetClientId(TObject *Sender)
{
	int intId = -1;

	for(int i = 0; i < vClients.size(); i++)
	{
		if(vClients[i] == Sender)
		{
			intId = i;
			break;
		}
	}

	return intId;
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::Sync(void)
{
	csMasterToSlave1->Open();
	csMasterToSlave2->Open();
	csMasterToSlave3->Open();
	csMasterToSlave4->Open();
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::csMasterToSlave1Connect(TObject *Sender, TCustomWinSocket *Socket)
{
	int intReqId = 0;
	if(Sender == csMasterToSlave1)
	{
		intReqId = 1;
	}
	else if(Sender == csMasterToSlave2)
	{
		intReqId = 2;
	}
	else if(Sender == csMasterToSlave3)
	{
		intReqId = 3;
	}
	else if(Sender == csMasterToSlave4)
	{
		intReqId = 4;
	}
	AddToLog(Socket, "CNC[" + IntToStr(intReqId) + "]");
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::csMasterToSlave1Disconnect(TObject *Sender, TCustomWinSocket *Socket)
{
	int intReqId = 0;
	if(Sender == csMasterToSlave1)
	{
		intReqId = 1;
	}
	else if(Sender == csMasterToSlave2)
	{
		intReqId = 2;
	}
	else if(Sender == csMasterToSlave3)
	{
		intReqId = 3;
	}
	else if(Sender == csMasterToSlave4)
	{
		intReqId = 4;
	}
	AddToLog(Socket, "DSC[" + IntToStr(intReqId) + "]");
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::csMasterToSlave1Error(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode)
{
	int intReqId = 0;
	if(Sender == csMasterToSlave1)
	{
		intReqId = 1;
	}
	else if(Sender == csMasterToSlave2)
	{
		intReqId = 2;
	}
	else if(Sender == csMasterToSlave3)
	{
		intReqId = 3;
	}
	else if(Sender == csMasterToSlave4)
	{
		intReqId = 4;
	}
	AddToLog(Socket, "ERR[" + IntToStr(intReqId) + "]#" + IntToStr(ErrorCode));
	ErrorCode = 0;
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::csMasterToSlave1Read(TObject *Sender, TCustomWinSocket *Socket)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::ssInSlaveClientConnect(TObject *Sender, TCustomWinSocket *Socket)
{
	AddToLog(Socket, "CNC");

	for(int i = 0; i < vClients.size(); i++)
	{
		vClients[i]->Open();
	}
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::ssInSlaveClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
	AddToLog(Socket, "DSC");

	for(int i = 0; i < vClients.size(); i++)
	{
		vClients[i]->Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::ssInSlaveClientError(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode)
{
	AddToLog(Socket, "ERR]#" + IntToStr(ErrorCode));

	for(int i = 0; i < vClients.size(); i++)
	{
		vClients[i]->Close();
	}

    ErrorCode = 0;
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::ssInSlaveClientRead(TObject *Sender, TCustomWinSocket *Socket)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::csClientConnect(TObject *Sender, TCustomWinSocket *Socket)
{
	int intReqId = GetClientId(Sender);
	AddToLog(Socket, "CNC[" + IntToStr(intReqId) + "]");
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::csClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
	int intReqId = GetClientId(Sender);
	AddToLog(Socket, "DSC[" + IntToStr(intReqId) + "]");
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::csClientError(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode)
{
	int intReqId = GetClientId(Sender);
	AddToLog(Socket, "ERR[" + IntToStr(intReqId) + "]#" + IntToStr(ErrorCode));
	ErrorCode = 0;
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::csClientRead(TObject *Sender, TCustomWinSocket *Socket)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::ssInTargetClientConnect(TObject *Sender, TCustomWinSocket *Socket)
{
	AddToLog(Socket, "CNC");
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::ssInTargetClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
	AddToLog(Socket, "DSC");
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::ssInTargetClientError(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode)
{
	AddToLog(Socket, "ERR#" + IntToStr(ErrorCode));
	ErrorCode = 0;
}
//---------------------------------------------------------------------------
void __fastcall TdmChannels::ssInTargetClientRead(TObject *Sender, TCustomWinSocket *Socket)
{
//
}
//---------------------------------------------------------------------------
void __fastcall AddToLog(String str)
{
	String ws = FormatDateTime("hh:mm:ss.zzz",Time()) + " " + str;
	formMain->memoLog->Lines->Add(ws);
}
//---------------------------------------------------------------------------
void __fastcall AddToLog(TCustomWinSocket* sock, String str)
{
	String ws = FormatDateTime("hh:mm:ss.zzz",Time()) +
				" [" + sock->RemoteHost + "::" + sock->RemoteAddress + "] " +
				str;
	formMain->memoLog->Lines->Add(ws);
}
//---------------------------------------------------------------------------

