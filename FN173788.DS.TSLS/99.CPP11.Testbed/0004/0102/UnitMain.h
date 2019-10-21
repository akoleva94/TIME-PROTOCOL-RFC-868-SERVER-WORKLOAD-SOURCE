//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include <System.ImageList.hpp>
//---------------------------------------------------------------------------
const int MAX_N = 10000000;	// Max Problem Size 10 000 000
//---------------------------------------------------------------------------
#include <vector>
#include <list>
#include <set>
#include <string>
#include <iterator>
using namespace std;
//---------------------------------------------------------------------------
template <class T>
T __fastcall GetMax(vector<T>& src)
{
  T max = src[0];
  for(auto& item : src)
  {
	if(max < item)
	  max = item;
  }

  return max;
}
//---------------------------------------------------------------------------
class TformMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *panelControl;
	TGroupBox *gboxProtocol;
	TRadioGroup *rgPartitions;
	TLabeledEdit *leditN;
	TButton *buttonStart;
	TListView *lviewProtocol;
	TStatusBar *stbarStatus;
	TGroupBox *gboxProcessAffinity;
	TCheckBox *cboxCore0;
	TPopupMenu *pupmProtocol;
	TMenuItem *miClear;
	TMenuItem *miSave;
	TImageList *imageList;
	TCheckBox *cboxCore1;
	TCheckBox *cboxCore2;
	TCheckBox *cboxCore3;
	TCheckBox *cboxCore4;
	TCheckBox *cboxCore5;
	TCheckBox *cboxCore6;
	TCheckBox *cboxCore7;
	TLabel *labelCore0;
	TLabel *labelCore7;
	TMemo *memoLog;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall buttonStartClick(TObject *Sender);
	void __fastcall cboxCore0Click(TObject *Sender);
	void __fastcall miClearClick(TObject *Sender);
	void __fastcall miSaveClick(TObject *Sender);
	void __fastcall lviewProtocolCompare(TObject *Sender, TListItem *Item1,
          TListItem *Item2, int Data, int &Compare);
	void __fastcall lviewProtocolColumnClick(TObject *Sender,
		  TListColumn *Column);
private:	// User declarations
	HANDLE hProcess;			// VCL Thread Pseudo Handle
	DWORD dwProcessAffinityMask, dwSystemAffinityMask;
	vector<TCheckBox*> vcboxCores {cboxCore0, cboxCore1, cboxCore2, cboxCore3, cboxCore4, cboxCore5, cboxCore6, cboxCore7};
	int intColumnToSort;		// lviewProtocol Column to sort
public:		// User declarations
	__fastcall TformMain(TComponent* Owner);

	int intN;					// Problem Size
	int intMax;					// Final Decision
	int intTestCount;			// Current Test Number
};
//---------------------------------------------------------------------------
extern PACKAGE TformMain *formMain;
//---------------------------------------------------------------------------
#endif
