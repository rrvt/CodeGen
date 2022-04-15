// DbTblSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBTblSelDlg.h"


// DbTblSelDlg dialog

IMPLEMENT_DYNAMIC(DbTblSelDlg, CDialogEx)

DbTblSelDlg::DbTblSelDlg(DbTblList& tblList, CWnd* pParent) :
                                                    CDialogEx(IDD_DBselect, pParent), tables(tblList) { }


BOOL DbTblSelDlg::OnInitDialog() {
DbTblIter iter(tables);
TblItem*  dsc;
int       i;

  CDialogEx::OnInitDialog();

  SetWindowText(title);

  nameCtrl.SetExtendedStyle(nameCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES);

  for (i = 0, dsc = iter(); dsc; i++, dsc = iter++)
                              {nameCtrl.InsertItem(i, dsc->name);   nameCtrl.SetCheck(i, dsc->selected);}
  return TRUE;
  }


DbTblSelDlg::~DbTblSelDlg() { }


void DbTblSelDlg::DoDataExchange(CDataExchange* pDX) {

  CDialogEx::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_List, nameCtrl);
  }


BEGIN_MESSAGE_MAP(DbTblSelDlg, CDialogEx)
  ON_BN_CLICKED(IDOK, &DbTblSelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// DbTblSelDlg message handlers


void DbTblSelDlg::OnBnClickedOk() {
DbTblIter iter(tables);
TblItem*  dsc;
int       i;

  for (i = 0, dsc = iter(); dsc; i++, dsc = iter++) dsc->selected = nameCtrl.GetCheck(i);

  CDialogEx::OnOK();
  }
