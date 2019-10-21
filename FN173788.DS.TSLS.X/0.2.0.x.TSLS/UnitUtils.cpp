//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitUtils.h"
#include "UnitFormMain.h"
//---------------------------------------------------------------------------
String __fastcall GetTSLSVersion(void)
{
	String stringVersion = "0.0.0.0000";
	String stringKeyFileInfo = "";

	String FileName = Application->ExeName;

	DWORD dwDummy;
	DWORD dwSize = GetFileVersionInfoSize(FileName.w_str(),
										&dwDummy);
	if(dwSize > 0)
	{
		TCHAR* lpFileVersionInfo = new TCHAR[dwSize];
		GetFileVersionInfo(FileName.w_str(),
						   0,
						   dwSize,
						   lpFileVersionInfo);

		// Extract Language and Character Set
		struct
		{
			unsigned short language;
			unsigned short character_set;
		} *translation;

		UINT wVVBuferLength;
		VerQueryValue(lpFileVersionInfo,
					  TEXT("\\VarFileInfo\\Translation"),
					  (void **)&translation,
					  &wVVBuferLength) ;

		stringKeyFileInfo = "\\StringFileInfo\\"
							+ String::IntToHex(translation[0].language, 4)
							+ String::IntToHex(translation[0].character_set, 4);

		// Extract File Version
		TCHAR* lpFileVersion;
		if(VerQueryValue(lpFileVersionInfo,
						 (stringKeyFileInfo + "\\FileVersion").w_str(),
						 (void**)&lpFileVersion,
						 &wVVBuferLength))
		{
			stringVersion = lpFileVersion;
		}

		delete [] lpFileVersionInfo;
	}

	return stringVersion;
}
//---------------------------------------------------------------------------
void __fastcall AddToLog(String str)
{
	String ws = Time().TimeString() + " " + str;
	formMain->memoLog->Lines->Add(ws);
}
//---------------------------------------------------------------------------
void __fastcall AddToLog(TCustomWinSocket* sock, String str)
{
	String ws = Time().TimeString() +
				" [" + sock->RemoteHost + "::" + sock->RemoteAddress + "] " +
				str;
	formMain->memoLog->Lines->Add(ws);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
