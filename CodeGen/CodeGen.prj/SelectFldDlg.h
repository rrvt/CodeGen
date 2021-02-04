// Dialog for collecting fields to use in searches of map tables.


#pragma once
#include "resource.h"
#include "TableCode.h"


// SelectFldDlg dialog

class SelectFldDlg : public CDialogEx {

  DECLARE_DYNAMIC(SelectFldDlg)

public:

CString     title;
Collection& col;
CListCtrl   fieldNames;

  SelectFldDlg(Collection& collection, CWnd* pParent = nullptr);   // standard constructor
  virtual ~SelectFldDlg();

  virtual BOOL OnInitDialog();

  afx_msg void OnBnClickedOk();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_SelectField };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
