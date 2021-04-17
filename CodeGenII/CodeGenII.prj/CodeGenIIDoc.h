// CodeGenIIDoc.h : interface of the CodeGenIIDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"
#include "TBComboBox.h"
#include "TBEditBox.h"


enum DataSource {NotePadSrc, StoreSrc, FontSrc};


class CodeGenIIDoc : public CDoc {

PathDlgDsc  pathDlgDsc;

DataSource  dataSource;

protected: // create from serialization only

  CodeGenIIDoc() noexcept;
  DECLARE_DYNCREATE(CodeGenIIDoc)

public:

  virtual ~CodeGenIIDoc();

  DataSource   dataSrc() {return dataSource;}
  void         display(DataSource ds);

  void         saveFile();
  virtual void serialize(Archive& ar);

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnFileOpen();
  afx_msg void OnComboBoxChng();
  afx_msg void onDBtable();
  afx_msg void OnFileSave();
  afx_msg void OnOptions();
  };

