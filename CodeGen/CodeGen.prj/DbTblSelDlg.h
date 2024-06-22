// Dialog for collecting the list of Maps

#pragma once
#include "DbTblList.h"
#include "resource.h"


// DbTblSelDlg dialog

class DbTblSelDlg : public CDialogEx {

  DECLARE_DYNAMIC(DbTblSelDlg)

DbTblList& tables;

public:
CString   title;
CListCtrl nameCtrl;

  DbTblSelDlg(DbTblList& tblList, CWnd* pParent = nullptr);           // standard constructor
  virtual ~DbTblSelDlg();

  virtual BOOL OnInitDialog();

  afx_msg void OnBnClickedOk();

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DBselect };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);

  DECLARE_MESSAGE_MAP()
  };


