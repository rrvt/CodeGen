// MapDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapDataDlg.h"
#include "tblList.h"


// MapDataDlg dialog

IMPLEMENT_DYNAMIC(MapDataDlg, CDialogEx)

MapDataDlg::MapDataDlg(CWnd* pParent) : CDialogEx(IDD_Selection, pParent) { }




BOOL MapDataDlg::OnInitDialog() {
TLIter  iter(tblList);
TblDsc* dsc;
int     i;

  CDialogEx::OnInitDialog();

  SetWindowText(title);

  mapNames.SetExtendedStyle(mapNames.GetExtendedStyle() | LVS_EX_CHECKBOXES);

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) mapNames.InsertItem(i, dsc->accName);

  return TRUE;
  }


MapDataDlg::~MapDataDlg() { }


void MapDataDlg::DoDataExchange(CDataExchange* pDX) {

  CDialogEx::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_List, mapNames);
  }


BEGIN_MESSAGE_MAP(MapDataDlg, CDialogEx)
  ON_BN_CLICKED(IDOK, &MapDataDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// MapDataDlg message handlers


void MapDataDlg::OnBnClickedOk() {
TLIter  iter(tblList);
TblDsc* dsc;
int     i;

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) dsc->selected = mapNames.GetCheck(i);

  CDialogEx::OnOK();
  }
