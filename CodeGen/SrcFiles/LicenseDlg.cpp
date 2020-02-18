// License.cpp : implementation file
//

#include "stdafx.h"
#include "CodeGen.h"
#include "LicenseDlg.h"


// License dialog

IMPLEMENT_DYNAMIC(LicenseDlg, CDialog)

LicenseDlg::LicenseDlg(CWnd* pParent /*=NULL*/) : CDialog(LicenseDlg::IDD, pParent) {}

LicenseDlg::~LicenseDlg() {}


void LicenseDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

  DDX_CBString(pDX, IDC_LicenseEB,  key);
  }


BEGIN_MESSAGE_MAP(LicenseDlg, CDialog)
END_MESSAGE_MAP()


// License message handlers
