// MapCodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapCodeDlg.h"
#include "TblList.h"
#include "Utilities.h"


// MapCodeDlg dialog

IMPLEMENT_DYNAMIC(MapCodeDlg, CDialogEx)


BEGIN_MESSAGE_MAP(MapCodeDlg, CDialogEx)
  ON_CBN_SELCHANGE(IDC_AccTblName, &MapCodeDlg::onSelectTable)
END_MESSAGE_MAP()


MapCodeDlg::MapCodeDlg(CWnd* pParent) : CDialogEx(MapCodeDlg::IDD, pParent),
                                                                           abbr(_T("")), name(_T("")) { }

MapCodeDlg::~MapCodeDlg() { }


BOOL MapCodeDlg::OnInitDialog() {
TLIter  iter(tblList);
TblDsc* dsc;

  CDialogEx::OnInitDialog();

  for (dsc = iter(); dsc; dsc = iter++) accTblNameCtrl.AddString(dsc->accName);

  return TRUE;
  }


void MapCodeDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control( pDX, IDC_AccTblName, accTblNameCtrl);
  DDX_CBString(pDX, IDC_AccTblName, name);
  DDX_Control( pDX, IDC_Name,       nameCtrl);
  DDX_Control( pDX, IDC_Abbr,       abbrCtrl);
  DDX_Text(    pDX, IDC_Abbr,       abbr);
}


// MapCodeDlg message handlers

void MapCodeDlg::onSelectTable() {
CString t;
String  s;

  accTblNameCtrl.GetLBText(accTblNameCtrl.GetCurSel(), t);   nameCtrl.SetWindowText(t);

  s = findAbbr(t);

  abbrCtrl.SetWindowText(s);
  }
