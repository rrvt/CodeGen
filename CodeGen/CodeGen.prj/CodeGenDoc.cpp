// CodeGenDoc.cpp : implementation of the CodeGenDoc class


#include "stdafx.h"
#include "CodeGenDoc.h"
#include "AceDao.h"
#include "CodeGen.h"
#include "CodeGenView.h"
#include "DataStore.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MessageBox.h"
#include "MapCode.h"
#include "MapData.h"
#include "MapDataDlg.h"
#include "MapsCode.h"
#include "NotePad.h"
#include "Options.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "TableCode.h"
#include "MapCodeDlg.h"


enum {col2 = 10, col3 = 35, col4 = 58, col5 = 81};


TCchar* HeaderPat = _T("*.h");
TCchar* CppPat    = _T("*.cpp");

static TCchar* dbPattern = _T("*.accdb;*.mdb");


// CodeGenDoc

IMPLEMENT_DYNCREATE(CodeGenDoc, CDoc)

BEGIN_MESSAGE_MAP(CodeGenDoc, CDoc)
  ON_COMMAND(ID_DoOpenDB,        &OnOpenDB)
  ON_COMMAND(ID_CreateMapCode,   &OnCreateMapCode)
  ON_COMMAND(ID_CreateTableCode, &OnCreateTableCode)
  ON_COMMAND(ID_MapData,         &OnMapData)
  ON_COMMAND(ID_DisplayDB,       &OnDisplayDB)
  ON_COMMAND(ID_Options,         &OnOptions)
END_MESSAGE_MAP()


// CodeGenDoc construction/destruction

CodeGenDoc::CodeGenDoc() noexcept : dataSource(NotePadSrc)
                                        {pathDsc = {_T("Code Gen"), _T(""), _T("accdb"), dbPattern};}


CodeGenDoc::~CodeGenDoc() { }


void CodeGenDoc::OnOpenDB() {
TLIter  iter(tblList);
TblDsc* dsc;

  notePad.clear(); dataSource = DataBaseSrc;

  iniFile.readString(FileSection, DBFileKey, path);   pathDsc.name = path;   pathDsc.pattern  = dbPattern;

  if (!setPath(pathDsc) || !maps.openDB(path)) return;

  iniFile.writeString(FileSection, DBFileKey, path);

  OnOpenArb(&maps);

  notePad << DBFileKey << _T(":") << nTab << path << nCrlf;
  notePad << _T("Tables") << nCrlf << nSetTab(3) << nCrlf;

  for (dsc = iter(); dsc; dsc = iter++) notePad << nTab << dsc->accName << nCrlf;

  dataSource = NotePadSrc; invalidate();
  }


void CodeGenDoc::OnCreateMapCode() {
MapCodeDlg dlg;
String     tblName;
String     abbr;

  dataSource = NotePadSrc;

  if (dlg.DoModal() == IDOK) {

    tblName = dlg.name;   abbr = dlg.abbr;

    createMapCode(tblName, abbr);

    invalidate();
    }
  }


void CodeGenDoc::createMapCode(String& tblName, String& abbr) {
MapCode mapCode(tblName, abbr);

  notePad.clear();   mapCode.createHeader();  invalidate();
  saveFile(_T("Header File"), mapCode.tbl.mapName, _T("h"), HeaderPat);

  notePad.clear();   mapCode.createCpp();     invalidate();
  saveFile(_T("Body File"), mapCode.tbl.mapName, _T("cpp"), CppPat);
  }



void CodeGenDoc::OnCreateTableCode() {
MapDataDlg dlg;
TLIter  iter(tblList);
TblDsc* dsc;

  dlg.title = _T("Create Table Modules");

  if (dlg.DoModal() == IDOK) {

    for (dsc = iter(); dsc; dsc = iter++)
      if (dsc->selected) {TableCode tableCode(dsc->accName); if (!tableCode(*dsc)) break;}
    }
  }


void CodeGenDoc::OnMapData() {
MapDataDlg dlg;
MapsCode   mapsCode;

  dlg.title = _T("Create Map Data File with Checked Tables");

  if (dlg.DoModal() == IDOK) {

    notePad.clear();   mapsCode.createMapDataHdr(); invalidate();
    saveFile(_T("Header File"), _T("MapData"), _T(".h"), HeaderPat);

    notePad.clear();   mapsCode.createMapDataCpp(); invalidate();
    saveFile(_T("Body File"), _T("MapData"), _T(".cpp"), CppPat);

    notePad.clear();   mapsCode.createMapsHdr();  invalidate();
    saveFile(_T("Header File"), _T("Maps"), _T(".h"), HeaderPat);

    notePad.clear();   mapsCode.createMapsCpp();  invalidate();
    saveFile(_T("Body File"), _T("Maps"), _T(".cpp"), CppPat);
    }
  }


void CodeGenDoc::saveFile(TCchar* title, TCchar* iniFileName, TCchar* defExt, TCchar* filter) {
String path;

  iniFile.readString(FileSection, GenFilePathKey, path);   path = getPath(path);

  path += iniFileName;

  if (getSaveAsPathDlg(title, path, defExt, filter, filePath)) {

    iniFile.writeString(FileSection, GenFilePathKey, getPath(filePath));

    OnSaveDocument(filePath.c_str());
    }
  }


void CodeGenDoc::OnDisplayDB() {
MapDataDlg dlg;

  notePad.clear();

  dlg.title = _T("Display Record Fields");

  if (dlg.DoModal() == IDOK) display(DataBaseSrc);
  }


void CodeGenDoc::OnOptions() {options(view());  view()->setOrientation(options.orient);}


void CodeGenDoc::display(DataSource ds) {dataSource = ds; invalidate();}


// CodeGenDoc serialization

void CodeGenDoc::serialize(Archive& ar) {

  if (ar.isStoring()) switch(dataSource) {
                        case NotePadSrc : notePad.archive(ar); return;
                        default         : return;
                        }

  switch(dataSource) {
    case NotePadSrc     : return;
    case DataBaseSrc : {Maps* m = (Maps*) ar.getObj();  if (m) m->loadMaps(); return;}
    }
  }


// CodeGenDoc diagnostics

#ifdef _DEBUG
void CodeGenDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CodeGenDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

