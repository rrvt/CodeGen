// Prime Key Selection Dialog

#include "stdafx.h"
#include "IniFile.h"
#include "MessageBox.h"
#include "PrimeKeyDlg.h"

static TCchar* AbbrKey = _T("Abbr");
static TCchar* PrimKey = _T("PrimKey");


IMPLEMENT_DYNAMIC(PrimeKeyDlg, CDialogEx)

BEGIN_MESSAGE_MAP(PrimeKeyDlg, CDialogEx)
  ON_NOTIFY(LVN_ITEMCHANGED, IDC_List, &PrimeKeyDlg::OnListCtrlChng)
END_MESSAGE_MAP()


PrimeKeyDlg::PrimeKeyDlg(FieldList& fieldList, CWnd* pParent) : fl(fieldList),
                                                   CDialogEx(IDD_PrimeSelect, pParent), abbr(_T("")) { }
PrimeKeyDlg::~PrimeKeyDlg() { }


BOOL PrimeKeyDlg::OnInitDialog() {
FldListIter iter(fl);
FieldDsc*   fldDsc;
int         i;
String      section = tblName + _T("Sect");
String      primKey;

  iniFile.readString(section, AbbrKey, abbr, tblName.substr(0, 3));

  CDialogEx::OnInitDialog();

  listCtrl.SetExtendedStyle(listCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES);

  iniFile.readString(section, PrimKey, primKey);

  for (fldDsc = iter(), i = 0; fldDsc; fldDsc = iter++, i++) {

    listCtrl.InsertItem(i, fldDsc->name);

    if (!primKey.isEmpty()) {if (fldDsc->name == primKey) {listCtrl.SetCheck(i, true);}}
    else                     if (fldDsc->isIndex)         {listCtrl.SetCheck(i, true);}
    }

  return TRUE;
  }


static const int SelMask = LVIS_SELECTED << 12;


void PrimeKeyDlg::OnListCtrlChng(NMHDR* pNMHDR, LRESULT* pResult) {
LPNMLISTVIEW lv = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
bool state      = (lv->uNewState & SelMask) != 0;       if (!state) return;
int  item       = lv->iItem;
int  n          = listCtrl.GetItemCount();
int  i;

  for (i = 0; i < n; i++) if (i != item) listCtrl.SetCheck(i, false);

  *pResult = 0;
  }


void PrimeKeyDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_List, listCtrl);
  DDX_Text(   pDX, IDC_Abbr, abbr);
}


void PrimeKeyDlg::OnOK() {
FldListIter iter(fl);
FieldDsc*   fldDsc;
int         i;
int         n;
String      section = tblName + _T("Sect");
String      primKey;

  for (i = 0, n = 0, fldDsc = iter(); fldDsc;  i++, fldDsc = iter++) {
    fldDsc->isIndex = listCtrl.GetCheck(i);

    if (fldDsc->isIndex) {primKey = fldDsc->name;   n++;}
    }

  if (n == 1) {
    CDialogEx::OnOK();
    iniFile.writeString(section, AbbrKey, abbr);
    iniFile.writeString(section, PrimKey, primKey);
    return;
    }

  messageBox(_T("One Primary Index must be selected."));
  }
