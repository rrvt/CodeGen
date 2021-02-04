// CodeGenDoc.h : interface of the CodeGenDoc class


#pragma once
#include "AceDao.h"
#include "CDoc.h"


enum DataSource {NotePadSrc, DataBaseSrc};


class CodeGenDoc : public CDoc {

PathDesc    pathDsc;

DataSource  dataSource;

String      filePath;

String      dbPath;
String      mapPath;

protected: // create from serialization only

  CodeGenDoc() noexcept;
  DECLARE_DYNCREATE(CodeGenDoc)

public:

  virtual ~CodeGenDoc();

    DataSource dataSrc() {return dataSource;}
    void       display(DataSource ds);

          void listTables(AceDao& db);

          void createLicense();

          void createMapCode(String& tableName, String& abbr);
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
  afx_msg void OnOpenDB();
  afx_msg void OnCreateMapCode();
  afx_msg void OnCreateTableCode();
  afx_msg void OnMapData();
  afx_msg void OnDisplayDB();
  afx_msg void OnOptions();
  };
