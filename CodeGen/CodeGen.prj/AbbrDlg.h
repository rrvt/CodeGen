// AbbrDlg dialog


#pragma once
#include "Resource.h"


class AbbrDlg : public CDialogEx {
  DECLARE_DYNAMIC(AbbrDlg)

public:
String  table;
CString abbr;

  AbbrDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~AbbrDlg();

  virtual BOOL OnInitDialog();
  virtual void OnOK();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Abbr };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
