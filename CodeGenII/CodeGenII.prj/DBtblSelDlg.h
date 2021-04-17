// Dialog for collecting the list of Maps

#pragma once
#include "resource.h"
#include "DBtbl.h"


// DBtblSelDlg dialog

class DBtblSelDlg : public CDialogEx {

  DECLARE_DYNAMIC(DBtblSelDlg)

TableData& tblData;
DBtbl&     dbTbl;

public:


#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DBselect };
#endif

CString   title;
CListCtrl nameCtrl;


  DBtblSelDlg(TableData& tableData, DBtbl& dbTable, CWnd* pParent = nullptr);                // standard constructor
  virtual ~DBtblSelDlg();

  virtual BOOL OnInitDialog();

  afx_msg void OnBnClickedOk();

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
};
