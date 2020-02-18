// TableOp.cpp : implementation file
//

#include "stdafx.h"
#include "TableOp.h"
#include "TableDscrs.h"


// TableOp dialog

IMPLEMENT_DYNAMIC(TableOp, CDialog)

TableOp::TableOp(CWnd* pParent) : CDialog(TableOp::IDD, pParent), nameBox(0), comboBox(0), tableName(_T("")) {
  operation = NilOp; comboBox = 0;
  }

TableOp::~TableOp() {}



BOOL TableOp::OnInitDialog() {
TableDsc* p;

  CDialog::OnInitDialog();

  if (!comboBox) {

    comboBox = static_cast<CComboBox*>(GetDlgItem(IDC_TblNamesCB));
    nameBox  = static_cast<CEdit*>(GetDlgItem(IDC_TblNameEB));

    for (p = tableDscrs.startLoop(); p; p = tableDscrs.nextEntry()) comboBox->AddString(p->name);
    }

  return TRUE;
  }


void TableOp::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  DDX_CBString(pDX, IDC_TblNamesCB, tableName);
  DDX_CBString(pDX, IDC_TblNameEB,  name);
  }


BEGIN_MESSAGE_MAP(TableOp, CDialog)
  ON_BN_CLICKED(   IDC_MakeCode, &TableOp::OnMakeCode)
  ON_BN_CLICKED(   IDC_Cancel, &TableOp::OnCancelClicked)
  ON_CBN_SELCHANGE(IDC_TblNamesCB,  &TableOp::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// TableOp message handlers

void TableOp::OnMakeCode() {CDialog::OnOK();}



void TableOp::OnCbnSelchangeCombo1() {
CString t;

  comboBox->GetLBText(comboBox->GetCurSel(), t);   nameBox->SetWindowText(t);
  }
