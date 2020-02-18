#pragma once
#include "Resource.h"


// License dialog

class LicenseDlg : public CDialog {
DECLARE_DYNAMIC(LicenseDlg)

public:
CString key;

  LicenseDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~LicenseDlg();

// Dialog Data
  enum { IDD = IDD_LicenseDLG };

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
