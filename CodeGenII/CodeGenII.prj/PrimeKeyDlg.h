// Prime Key Selection Dialog


#pragma once
#include "FieldList.h"
#include "Resource.h"


// PrimeKeyDlg dialog

class PrimeKeyDlg : public CDialogEx {
FieldList& fl;

  DECLARE_DYNAMIC(PrimeKeyDlg)

public:
CString   title;
String    tblName;
CListCtrl listCtrl;
  CString abbr;

           PrimeKeyDlg(FieldList& fieldList, CWnd* pParent = nullptr);
  virtual ~PrimeKeyDlg();

  virtual BOOL OnInitDialog();
  virtual void OnOK();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_PrimeSelect };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnListCtrlChng(NMHDR* pNMHDR, LRESULT* pResult);
};
