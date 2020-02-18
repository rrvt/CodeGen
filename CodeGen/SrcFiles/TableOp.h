// TableOp Dialog Box


#pragma once

#include "afxwin.h"
#include "Resource.h"


class TableOp : public CDialog {
DECLARE_DYNAMIC(TableOp)

public:
enum { IDD = IDD_TableOpsDLG };

enum Operation {NilOp, FieldNameOp, RecordOp, DisplayOp, CodeOp};

           TableOp(CWnd* pParent = NULL);   // standard constructor
  virtual ~TableOp();
  virtual BOOL OnInitDialog();

// Dialog Data

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

CComboBox* comboBox;
CEdit*     nameBox;
CString    tableName;
CString    name;
CButton    fieldNames;
CButton    displayRcds;
CButton    code;

Operation  operation;

  afx_msg void OnMakeCode();
  afx_msg void OnCancelClicked() {CDialog::OnCancel();}
  afx_msg void OnBnClickedRadio4();
  afx_msg void OnCbnSelchangeCombo1();
  };
