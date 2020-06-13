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
int n = col.fields.end();
int i;

  CDialogEx::OnInitDialog();

  SetWindowText(title);

  fieldNames.SetExtendedStyle(fieldNames.GetExtendedStyle() | LVS_EX_CHECKBOXES);

  for (i = 0; i < n; i++) fieldNames.InsertItem(i, col.fields[i].name);

  return TRUE;
  }


void SelectFldDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX); DDX_Control(pDX, IDC_List, fieldNames);
  }


void SelectFldDlg::OnBnClickedOk() {
int n = col.fields.end();
int i;

  col.noStringsSel = 0;

  for (i = 0; i < n; i++) {
    FldDsc& fd = col.fields[i];   fd.selected = fieldNames.GetCheck(i);

    if (fd.selected && fd.typ == _T("String")) col.noStringsSel++;
    }

  CDialogEx::OnOK();
  }

