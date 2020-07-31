// CodeGenIIDoc.h : interface of the CodeGenIIDoc class


#pragma once
#include "AceDao.h"
#include "CDoc.h"


class CodeGenIIDoc : public CDoc {

String saveAsTitle;                                            // Save As Parameters, examples:
String defFileName;                                            // _T("mumble.txt")
String defExt;                                                 // _T("txt")
String defFilePat;                                             // _T("*.txt")

String filePath;

protected: // create from serialization only

  CodeGenIIDoc() noexcept;
  DECLARE_DYNCREATE(CodeGenIIDoc)

public:

  virtual ~CodeGenIIDoc();

  virtual BOOL OnNewDocument();

          void listTables(AceDao& db);

          void createTableCode();
          void onTableExtension();
          void createLicense();

          void createCode(String& tableName, String& abbr);
          void saveFile(TCchar* title, TCchar* iniFileName, TCchar* defExt, TCchar* filter);

  virtual void serialize(Archive& ar);

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void testTestMap();
  void dspRecords(String& name);

// Generated message map functions

protected:
  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnDisplayDB();
  afx_msg void OnMapData();
  afx_msg void OnTest();
  afx_msg void OnFileOpen();
  afx_msg void OnFileSave();
  afx_msg void OnOptions();
  };
