// TableOpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TableOpDlg.h"
#include "TableDscrs.h"
#include "Utilities.h"


// TableOpDlg dialog

IMPLEMENT_DYNAMIC(TableOpDlg, CDialogEx)


BEGIN_MESSAGE_MAP(TableOpDlg, CDialogEx)
  ON_CBN_SELCHANGE(IDC_AccTblName, &TableOpDlg::onSelectTable)
END_MESSAGE_MAP()


TableOpDlg::TableOpDlg(CWnd* pParent) : CDialogEx(TableOpDlg::IDD, pParent),
                                                                           abbr(_T("")), name(_T("")) { }

TableOpDlg::~TableOpDlg() { }


BOOL TableOpDlg::OnInitDialog() {
TDIter    iter(tableDscrs);
TableDsc* dsc;

  CDialogEx::OnInitDialog();

  for (dsc = iter(); dsc; dsc = iter++) accTblNameCtrl.AddString(dsc->accName);

  return TRUE;
  }


void TableOpDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control( pDX, IDC_AccTblName, accTblNameCtrl);
  DDX_CBString(pDX, IDC_AccTblName, name);
  DDX_Control( pDX, IDC_Name,       nameCtrl);
  DDX_Control( pDX, IDC_Abbr,       abbrCtrl);
  DDX_Text(    pDX, IDC_Abbr,       abbr);
}


// TableOpDlg message handlers

void TableOpDlg::onSelectTable() {
CString t;
String  s;

  accTblNameCtrl.GetLBText(accTblNameCtrl.GetCurSel(), t);   nameCtrl.SetWindowText(t);

  s = findAbbr(t);

  abbrCtrl.SetWindowText(s);
  }
