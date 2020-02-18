// CodeGenDoc.h : interface of the CodeGenDoc class

#pragma once
#include "AceDao.h"
#include "CDoc.h"

class Note;
class MapTable;


class CodeGenDoc : public CDoc {
String filePath;

protected: // create from serialization only

  CodeGenDoc();
  DECLARE_DYNCREATE(CodeGenDoc)

public:
          void saveFile(TCchar* title, TCchar* iniFileName, TCchar* defExt, TCchar* filter);

  virtual void serialize(Archive& ar);

// Implementation

public:

  virtual ~CodeGenDoc();

  void listTables(AceDao& db);

  void createTableCode();
  void onTableExtension();
  void createLicense();

  void createCode(String& tableName, String& name);

//  void restoreTables();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void testTestMap();
  void dspRecords(MapTable* tbl);

// Generated message map functions

protected:

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnDisplayDB();
  afx_msg void OnMapData();
  };


