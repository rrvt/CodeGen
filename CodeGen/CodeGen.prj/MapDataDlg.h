// Dialog for collecting the list of Maps

#pragma once
#include "resource.h"


// MapDataDlg dialog

class MapDataDlg : public CDialogEx {

  DECLARE_DYNAMIC(MapDataDlg)

public:


#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Selection };
#endif

CString   title;
CListCtrl mapNames;


  MapDataDlg(CWnd* pParent = nullptr);                // standard constructor
  virtual ~MapDataDlg();

  virtual BOOL OnInitDialog();

  afx_msg void OnBnClickedOk();

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
};
