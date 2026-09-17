// CodeGenDoc.h : interface of the CodeGenDoc class


#pragma once
#include "CDoc.h"
#include "NotePad.h"
#include "PathDlg.h"


enum DataSource {NilSrc, NotePadSrc};


class CodeGenDoc : public CDoc {

DataSource dataSource;

bool       dbOpened;
bool       tableSelected;

PathDlg    dlg;

protected: // create from serialization only

  CodeGenDoc() noexcept;

  DECLARE_DYNCREATE(CodeGenDoc)

public:
String productName;

  virtual     ~CodeGenDoc();

  void         setProductName(TCchar* pn) {productName = pn;}

  DataSource   dataSrc() {return dataSource;}
  void         display(DataSource ds = NotePadSrc);
  NotePad&     getData() {return notePad;}

  void         saveFile();
  void         getHeader(NotePad& np, int pageNo, int noPages);
  void         getFooter(NotePad& np, int pageNo, int noPages);

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

  friend class CodeGenOps;
  };

