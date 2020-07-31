// TableOpDlg Dialog Box


#pragma once

#include "afxwin.h"
#include "Resource.h"


class TableOpDlg : public CDialogEx {

DECLARE_DYNAMIC(TableOpDlg)

public:

CComboBox  accTblNameCtrl;
CEdit      nameCtrl;
CEdit      abbrCtrl;

CString    name;
CString    abbr;


enum { IDD = IDD_TableOpsDLG };

           TableOpDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~TableOpDlg();
  virtual BOOL OnInitDialog();

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnMakeCode();
  afx_msg void OnCancelClicked() {CDialogEx::OnCancel();}
  afx_msg void OnBnClickedRadio4();
  afx_msg void onSelectTable();
};


//enum Operation {NilOp, FieldNameOp, RecordOp, DisplayOp, CodeOp};
//CEdit*     nameBox;
//CString    tableName;
//CButton    fieldNames;
//CButton    displayRcds;
//CButton    code;
//Operation  operation;

