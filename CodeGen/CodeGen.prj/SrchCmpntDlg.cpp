// SrchCmpntDlg.cpp : implementation file


#include "stdafx.h"
#include "SrchCmpntDlg.h"
#include "Fields.h"


IMPLEMENT_DYNAMIC(SrchCmpntDlg, CDialogEx)

BEGIN_MESSAGE_MAP(SrchCmpntDlg, CDialogEx)
END_MESSAGE_MAP()


SrchCmpntDlg::SrchCmpntDlg(CWnd* pParent) : CDialogEx(IDD_Selection, pParent) { }


BOOL SrchCmpntDlg::OnInitDialog() {
FldsIter iter(fields);
Field*   fldDsc;
int      i;

  CDialogEx::OnInitDialog();

  SetWindowText(title);

  listCtrl.SetExtendedStyle(listCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES);

  for (fldDsc = iter(), i = 0; fldDsc; fldDsc = iter++, i++) listCtrl.InsertItem(i, fldDsc->name);

  return TRUE;
  }


void SrchCmpntDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_List,    listCtrl);
  }


void SrchCmpntDlg::OnOK() {
FldsIter iter(fields);
Field*   fldDsc;
int      i;

  for (i = 0, fldDsc = iter(); fldDsc;  i++, fldDsc = iter++) fldDsc->isSelected = listCtrl.GetCheck(i);

  CDialogEx::OnOK();
  }
