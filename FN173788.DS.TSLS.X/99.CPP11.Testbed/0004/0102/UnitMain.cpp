//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.hpp>
#include <fstream>
#pragma hdrstop

#include <chrono>
#include <future>
//---------------------------------------------------------------------------
#include "UnitMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformMain *formMain;
//---------------------------------------------------------------------------
vector<int> vectorArray;	// Main Data Set
vector<int> vectorArray0;	// Partition 0
vector<int> vectorArray1;	// Partition 1
vector<int> vectorArray2;	// Partition 2
vector<int> vectorArray3;	// Partition 3
//---------------------------------------------------------------------------
__fastcall TformMain::TformMain(TComponent* Owner)
	: TForm(Owner)
{
	intTestCount = 0;
	intColumnToSort = 0;

	DWORD dwStyle = GetWindowLong(leditN->Handle, GWL_STYLE);
	SetWindowLong(leditN->Handle, GWL_STYLE, dwStyle | ES_NUMBER | ES_RIGHT);
	leditN->Text = MAX_N;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::FormShow(TObject *Sender)
{
//	vectorArray.reserve(MAX_N);
//	vectorArray0.reserve(MAX_N/2);
//	vectorArray1.reserve(MAX_N/2);
//	vectorArray1.reserve(MAX_N/2);
//	vectorArray1.reserve(MAX_N/2);

	hProcess = GetCurrentProcess();

	SYSTEM_INFO siSystemInfo;
	GetSystemInfo(&siSystemInfo);
	for(auto& i : vcboxCores)
	{
		int m = 1 << i->Tag;
		if(siSystemInfo.dwActiveProcessorMask & m)
		{
			if(m == 1)
			{
				i->Checked = true;
			}
			i->Enabled = true;
		}
		else
		{
			i->Checked = false;
			i->Enabled = false;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::buttonStartClick(TObject *Sender)
{
	buttonStart->Enabled = false;
	Screen->Cursor = crHourGlass;

	stbarStatus->SimpleText = "";

	std::chrono::milliseconds dur_in_milli;

	vectorArray.clear();
	vectorArray0.clear();
	vectorArray1.clear();
	vectorArray2.clear();
	vectorArray3.clear();

	memoLog->Clear();

	try
	{
		// Get N
		intN = leditN->Text.ToInt();
		if(intN > MAX_N)
		{
			leditN->Text = MAX_N;
			throw Exception("Max Limit of N Exceeded");
		}

		if(rgPartitions->ItemIndex == 0)
		{ // Sequential Mode
			// Data Set Initialization
			Randomize();
			for(int i = 0; i < intN; i++)
			{
				int item = RandomRange(-MaxInt, MaxInt);
				vectorArray.push_back(item);
			}

			memoLog->Lines->Add("Partition Size:");
			memoLog->Lines->Add("N = " + IntToStr((int)vectorArray.size()));

			auto beg = std::chrono::high_resolution_clock::now();

			// Serial Processing
			intMax = GetMax(vectorArray);

			auto end = std::chrono::high_resolution_clock::now();
			dur_in_milli = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);
		}
		else if(rgPartitions->ItemIndex == 1)
		{ // Parallel Mode - 2 Threads

			// Data Set Initialization
			Randomize();
			for(int i = 0; i < intN; i++)
			{
				int item = RandomRange(-MaxInt, MaxInt);
				// Partitioning
				if(i & 0x1)
				{
					vectorArray1.push_back(item);
				}
				else
				{
					vectorArray0.push_back(item);
				}
			}

			memoLog->Lines->Add("Partitions Size:");
			memoLog->Lines->Add("N0 = " + IntToStr((int)vectorArray0.size()));
			memoLog->Lines->Add("N1 = " + IntToStr((int)vectorArray1.size()));

			auto beg = std::chrono::high_resolution_clock::now();

			// Parallel Processing

			std::future<int> future_max0(std::async(std::launch::async, [](){return GetMax(vectorArray0);}));
			std::future<int> future_max1(std::async(std::launch::async, [](){return GetMax(vectorArray1);}));

			// VCL Thread waits on futures working threads to finish
			// Merging results
			intMax = Max(future_max0.get(), future_max1.get());

			auto end = std::chrono::high_resolution_clock::now();
			dur_in_milli = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);
		}
		else if(rgPartitions->ItemIndex == 2)
		{ // Parallel Mode - 4 Threads

			// Data Set Initialization
			Randomize();
			for(int i = 0; i < intN; i++)
			{
				int item = RandomRange(-MaxInt, MaxInt);
				// Partitioning
				if(i & 0b10)
				{
					if(i & 0b01)
					{
						vectorArray3.push_back(item);
					}
					else
					{
						vectorArray2.push_back(item);
					}
				}
				else if(i & 0b01)
				{
					vectorArray1.push_back(item);
				}
				else
				{
					vectorArray0.push_back(item);
				}
			}

			memoLog->Lines->Add("Partitions Size:");
			memoLog->Lines->Add("N0 = " + IntToStr((int)vectorArray0.size()));
			memoLog->Lines->Add("N1 = " + IntToStr((int)vectorArray1.size()));
			memoLog->Lines->Add("N2 = " + IntToStr((int)vectorArray2.size()));
			memoLog->Lines->Add("N3 = " + IntToStr((int)vectorArray3.size()));

			auto beg = std::chrono::high_resolution_clock::now();

			// Parallel Processing

			std::future<int> future_max0(std::async(std::launch::async, [](){return GetMax(vectorArray0);}));
			std::future<int> future_max1(std::async(std::launch::async, [](){return GetMax(vectorArray1);}));
			std::future<int> future_max2(std::async(std::launch::async, [](){return GetMax(vectorArray2);}));
			std::future<int> future_max3(std::async(std::launch::async, [](){return GetMax(vectorArray3);}));

			// VCL Thread waits on futures working threads to finish
			// Merging results
			int intMax01 = Max(future_max0.get(), future_max1.get());
			int intMax23 = Max(future_max2.get(), future_max3.get());
			intMax = Max(intMax01, intMax23);

			auto end = std::chrono::high_resolution_clock::now();
			dur_in_milli = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);
		}

		TListItem* liItem = lviewProtocol->Items->Add();
		liItem->Caption = ++intTestCount;
		liItem->ImageIndex = -1;

		liItem->SubItems->Add(rgPartitions->ItemIndex + 1);
		liItem->SubItems->Add(dwProcessAffinityMask);
		liItem->SubItems->Add(leditN->Text);
		liItem->SubItems->Add(dur_in_milli.count());

		intColumnToSort = 0;
		lviewProtocol->Columns->Items[intColumnToSort]->ImageIndex = 0;
	}
	catch(Exception& e)
	{
		// Log e.Message
		stbarStatus->SimpleText = e.Message;
	}

	Screen->Cursor = crDefault;
	buttonStart->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::cboxCore0Click(TObject *Sender)
{
	// Set Process Affinity
	DWORD __dwAffinityMask = 0;
	for(auto& i : vcboxCores)
	{
		if(i->Checked)
		{
			int mask = 1 << i->Tag;
			__dwAffinityMask |= mask;
		}
	}
	SetProcessAffinityMask(hProcess, __dwAffinityMask);

	// Check Process Affinity
	GetProcessAffinityMask(hProcess, &dwProcessAffinityMask, &dwSystemAffinityMask);
	if(__dwAffinityMask != dwProcessAffinityMask)
	{
		for(auto& i : vcboxCores)
		{
			int m = 1 << i->Tag;
			if(dwProcessAffinityMask & m)
			{
				i->Checked = true;
			}
        }
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::miClearClick(TObject *Sender)
{
	int ExitCode = Application->MessageBox(L"Сигурни ли сте", L"Протоколът ще бъде изтрит",
		MB_YESNO|MB_ICONWARNING);

	if(ExitCode == IDYES)
	{
		intTestCount = 0;
		lviewProtocol->Clear();
	}
}
//---------------------------------------------------------------------------
void __fastcall TformMain::miSaveClick(TObject *Sender)
{
	String ln;
	String stringFileName;

	stringFileName.printf(L"TEMP.csv");

	ofstream file(stringFileName.c_str());
	if(!file)
	{
		ln = "[" + (Date() + Time()).DateTimeString() + "] " + "ERROR: Cannot Open " + stringFileName;
		stbarStatus->SimpleText = ln;
		return;
	}

	Screen->Cursor = crSQLWait;

	for(int i = 0; i < lviewProtocol->Columns->Count; i++)
	{
		if(i == 0)
		  ln = lviewProtocol->Columns->Items[i]->Caption;
		else
		  ln += "; " + lviewProtocol->Columns->Items[i]->Caption;
	}
	file << ln.c_str() << endl;

	for(int j = 0; j < lviewProtocol->Items->Count; j++)
	{
		ln = lviewProtocol->Items->Item[j]->Caption;

		for(int i = 0; i < lviewProtocol->Columns->Count - 1; i++)
		{
		  ln += "; " + lviewProtocol->Items->Item[j]->SubItems->Strings[i];
		}
		file << ln.c_str() << endl;
	}

	ln = "[" + (Date() + Time()).DateTimeString() + "] Отчетът е записан във файла \"" + ExtractFileName(stringFileName) + "\"";
	stbarStatus->SimpleText = ln;

	Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TformMain::lviewProtocolColumnClick(TObject *Sender,
	  TListColumn *Column)
{
	if(intColumnToSort == Column->Index)
	{
		if(lviewProtocol->Columns->Items[intColumnToSort]->ImageIndex == 0)
		  lviewProtocol->Columns->Items[intColumnToSort]->ImageIndex = 1;
		else
		  lviewProtocol->Columns->Items[intColumnToSort]->ImageIndex = 0;
	}
	else
	{
		lviewProtocol->Columns->Items[intColumnToSort]->ImageIndex = -1;
		intColumnToSort = Column->Index;
		lviewProtocol->Columns->Items[intColumnToSort]->ImageIndex = 0;
	}

	((TCustomListView *)Sender)->AlphaSort();
}
//---------------------------------------------------------------------------
void __fastcall TformMain::lviewProtocolCompare(TObject *Sender,
	  TListItem *Item1, TListItem *Item2, int Data, int &Compare)
{
	if(intColumnToSort == 0)
	Compare = CompareText(Item1->Caption,Item2->Caption);
	else
	{
		int ix = intColumnToSort - 1;
		Compare = CompareText(Item1->SubItems->Strings[ix], Item2->SubItems->Strings[ix]);
	}

	if(lviewProtocol->Columns->Items[intColumnToSort]->ImageIndex == 1)
	if(Compare != 0)
		Compare = -Compare;
}
//---------------------------------------------------------------------------

