// AbbrDlg.cpp : implementation file


#include "pch.h"
#include "AbbrDlg.h"
#include "Capitalize.h"
#include "DbTblList.h"


// AbbrDlg dialog

IMPLEMENT_DYNAMIC(AbbrDlg, CDialogEx)

AbbrDlg::AbbrDlg(CWnd* pParent) : CDialogEx(IDD_Abbr, pParent), abbr(_T("")) { }

AbbrDlg::~AbbrDlg() { }


BOOL AbbrDlg::OnInitDialog() {

TblItem* tblItem = dbTblList.find(table);   if (tblItem) abbr = tblItem->abbr;

  CDialogEx::OnInitDialog();   return TRUE;
  }



void AbbrDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_Abbr, abbr);
  }


BEGIN_MESSAGE_MAP(AbbrDlg, CDialogEx)
END_MESSAGE_MAP()


// AbbrDlg message handlers


void AbbrDlg::OnOK() {

TblItem* tblItem = dbTblList.find(table);

  CDialogEx::OnOK();

  if (tblItem) tblItem->setAbbr(capitalize(abbr));
  }


