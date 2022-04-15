// SrchCmpntDlg dialog


#pragma once
#include "Resource.h"


class SrchCmpntDlg : public CDialogEx {

  DECLARE_DYNAMIC(SrchCmpntDlg)

public:

CString   title;
CListCtrl listCtrl;

           SrchCmpntDlg(CWnd* pParent = nullptr);
  virtual ~SrchCmpntDlg() { }

  virtual BOOL OnInitDialog();
  virtual void OnOK();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Selection };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);                    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
