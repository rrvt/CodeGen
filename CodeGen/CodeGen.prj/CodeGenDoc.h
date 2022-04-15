// CodeGenDoc.h : interface of the CodeGenDoc class


#pragma once
#include "CDoc.h"


enum DataSource {NotePadSrc, StoreSrc, FontSrc};


class CodeGenDoc : public CDoc {

DataSource  dataSource;

bool        dbOpened;
bool        tableSelected;

PathDlgDsc  pathDlgDsc;

protected: // create from serialization only

  CodeGenDoc() noexcept;
  DECLARE_DYNCREATE(CodeGenDoc)

public:

  virtual ~CodeGenDoc();

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
  afx_msg void onRcdSet();
  afx_msg void onDBtable();
  afx_msg void onDatabase();
  afx_msg void OnFileSave();
  afx_msg void OnOptions();

  friend class CodeGenOps;
  };



//#include "Fields.h"
//#include "ModNames.h"

