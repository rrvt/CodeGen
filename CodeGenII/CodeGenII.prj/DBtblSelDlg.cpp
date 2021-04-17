// DBtblSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBTblSelDlg.h"
//#include "tableDscrs.h"


// DBtblSelDlg dialog

IMPLEMENT_DYNAMIC(DBtblSelDlg, CDialogEx)

DBtblSelDlg::DBtblSelDlg(TableData& tableData, DBtbl& dbTable, CWnd* pParent) :
                                 tblData(tableData), dbTbl(dbTable), CDialogEx(IDD_DBselect, pParent) { }




BOOL DBtblSelDlg::OnInitDialog() {
DBtblIter iter(dbTbl);
Table*    tbl;
int       i;

  CDialogEx::OnInitDialog();

  SetWindowText(title);

  nameCtrl.SetExtendedStyle(nameCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES);

  for (i = 0, tbl = iter(); tbl; i++, tbl = iter++)
                              {nameCtrl.InsertItem(i, tbl->name);   nameCtrl.SetCheck(i, tbl->selected);}

  return TRUE;
  }


DBtblSelDlg::~DBtblSelDlg() { }


void DBtblSelDlg::DoDataExchange(CDataExchange* pDX) {

  CDialogEx::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_List, nameCtrl);
  }


BEGIN_MESSAGE_MAP(DBtblSelDlg, CDialogEx)
  ON_BN_CLICKED(IDOK, &DBtblSelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// DBtblSelDlg message handlers


void DBtblSelDlg::OnBnClickedOk() {
DBtblIter iter(dbTbl);
Table*    tbl;
int       i;

  for (i = 0, tbl = iter(); tbl; i++, tbl = iter++) tbl->selected = nameCtrl.GetCheck(i);

  CDialogEx::OnOK();
  }
