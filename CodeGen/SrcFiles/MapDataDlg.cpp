// MapDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapDataDlg.h"
#include "tableDscrs.h"


// MapDataDlg dialog

IMPLEMENT_DYNAMIC(MapDataDlg, CDialogEx)

MapDataDlg::MapDataDlg(CWnd* pParent) : CDialogEx(IDD_DIALOG1, pParent) { }




BOOL MapDataDlg::OnInitDialog() {
TableDsc* tbl;
int       i;

  CDialogEx::OnInitDialog();

  SetWindowText(title);

  mapNames.SetExtendedStyle(mapNames.GetExtendedStyle() | LVS_EX_CHECKBOXES);

  for (tbl = tableDscrs.startLoop(), i = 0; tbl; tbl = tableDscrs.nextEntry(), i++)
                                                                      mapNames.InsertItem(i, tbl->name);
  return TRUE;
  }


MapDataDlg::~MapDataDlg() { }


void MapDataDlg::DoDataExchange(CDataExchange* pDX) {

  CDialogEx::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_LIST3, mapNames);
  }


BEGIN_MESSAGE_MAP(MapDataDlg, CDialogEx)
  ON_BN_CLICKED(IDOK, &MapDataDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// MapDataDlg message handlers


void MapDataDlg::OnBnClickedOk() {
TableDsc*  tbl;
int       i;

  for (tbl = tableDscrs.startLoop(), i = 0; tbl; tbl = tableDscrs.nextEntry(), i++)
                                                                  tbl->selected = mapNames.GetCheck(i);
  CDialogEx::OnOK();
  }
