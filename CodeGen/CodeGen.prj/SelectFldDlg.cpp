// SelectFldDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SelectFldDlg.h"



// SelectFldDlg dialog

IMPLEMENT_DYNAMIC(SelectFldDlg, CDialogEx)


BEGIN_MESSAGE_MAP(SelectFldDlg, CDialogEx)
  ON_BN_CLICKED(IDOK, &SelectFldDlg::OnBnClickedOk)
END_MESSAGE_MAP()


SelectFldDlg::SelectFldDlg(Collection& collection, CWnd* pParent) : col(collection), CDialogEx(IDD_SelectField, pParent) { }

SelectFldDlg::~SelectFldDlg() { }




BOOL SelectFldDlg::OnInitDialog() {
ClnIter iter(col);
FldDsc* dsc;
int     i;

  CDialogEx::OnInitDialog();

  SetWindowText(title);

  fieldNames.SetExtendedStyle(fieldNames.GetExtendedStyle() | LVS_EX_CHECKBOXES);

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) fieldNames.InsertItem(i, dsc->name);

  return TRUE;
  }


void SelectFldDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX); DDX_Control(pDX, IDC_List, fieldNames);
  }


void SelectFldDlg::OnBnClickedOk() {
ClnIter iter(col);
FldDsc* dsc;
int     i;

  col.noStringsSel = 0;

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    dsc->selected = fieldNames.GetCheck(i);

    if (dsc->selected && dsc->typ == _T("String")) col.noStringsSel++;
    }

  CDialogEx::OnOK();
  }

