// CodeGenIIDoc.cpp : implementation of the CodeGenIIDoc class


#include "stdafx.h"
#include "CodeGenIIDoc.h"
#include "AceDao.h"
#include "CodeGenII.h"
#include "CodeGenIIView.h"
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
#include "TableExtension.h"
#include "TableOpDlg.h"


enum {col2 = 10, col3 = 35, col4 = 58, col5 = 81};


TCchar* HeaderPat = _T("*.h");
TCchar* CppPat    = _T("*.cpp");

static TCchar* dbPattern = _T("*.accdb;*.mdb");


// CodeGenIIDoc

IMPLEMENT_DYNCREATE(CodeGenIIDoc, CDoc)

BEGIN_MESSAGE_MAP(CodeGenIIDoc, CDoc)
  ON_COMMAND(ID_DoOpenDB,       &OnOpenDB)
  ON_COMMAND(ID_TableOps,       &OnCreateTableCode)
  ON_COMMAND(ID_TableExtension, &OnTableExtension)
  ON_COMMAND(ID_MapData,        &OnMapData)
  ON_COMMAND(ID_DisplayDB,      &OnDisplayDB)
  ON_COMMAND(ID_Options,        &OnOptions)
END_MESSAGE_MAP()


// CodeGenIIDoc construction/destruction

CodeGenIIDoc::CodeGenIIDoc() noexcept : dataSource(NoteSource)
                                        {pathDsc = {_T("Code Gen II"), _T(""), _T("accdb"), dbPattern};}


CodeGenIIDoc::~CodeGenIIDoc() { }


void CodeGenIIDoc::OnOpenDB() {
String title;
String ext;

  notePad.clear(); dataSource = DataBaseSource;

  if (!openOneDB(DBFileKey, dbPattern)) return;

  dataSource = NoteSource; invalidate();
  }


bool CodeGenIIDoc::openOneDB(TCchar* title, TCchar* pattern) {

  iniFile.readString(FileSection, DBFileKey, path);   pathDsc.name = path;   pathDsc.pattern  = pattern;

  if (!setPath(pathDsc) || !maps.openDB(path)) return false;

  iniFile.writeString(FileSection, DBFileKey, path);

  OnOpenArb(&maps);   notePad << title << _T(":") << nTab << path << nCrlf;   return true;
  }


void CodeGenIIDoc::OnCreateTableCode() {
TableOpDlg dlg;
String     tblName;
String     abbr;

  dataSource = NoteSource;

  if (dlg.DoModal() == IDOK) {

    tblName = dlg.name;   abbr = dlg.abbr;

    createCode(tblName, abbr);

    invalidate();
    }
  }


void CodeGenIIDoc::createCode(String& tblName, String& abbr) {
MapCode mapCode(tblName, abbr);

  notePad.clear();   mapCode.createHeader();  invalidate();
  saveFile(_T("Header File"), mapCode.tbl.fileName, _T("h"), HeaderPat);

  notePad.clear();   mapCode.createCpp();     invalidate();
  saveFile(_T("Body File"), mapCode.tbl.fileName, _T("cpp"), CppPat);
  }



void CodeGenIIDoc::OnTableExtension() {
MapDataDlg dlg;
TDIter     iter(tableDscrs);
TableDsc*  dsc;

  dlg.title = _T("Create Table Extension Modules");

  if (dlg.DoModal() == IDOK) {

    for (dsc = iter(); dsc; dsc = iter++)
      if (dsc->selected) {TableExtension ext(dsc->accName); if (!ext(*dsc)) break;}
    }
  }


void CodeGenIIDoc::OnMapData() {
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


void CodeGenIIDoc::saveFile(TCchar* title, TCchar* iniFileName, TCchar* defExt, TCchar* filter) {
String path;

  iniFile.readString(FileSection, GenFilePathKey, path);   path = getPath(path);

  path += iniFileName;

  if (getSaveAsPathDlg(title, path, defExt, filter, filePath)) {

    iniFile.writeString(FileSection, GenFilePathKey, getPath(filePath));

    OnSaveDocument(filePath.c_str());
    }
  }


void CodeGenIIDoc::OnDisplayDB() {
MapDataDlg dlg;

  notePad.clear();

  dlg.title = _T("Display Record Fields");

  if (dlg.DoModal() == IDOK) display(DataBaseSource);
  }

#if 0
void CodeGenIIDoc::dspTables() {
int       i;
TDIter    iter(tableDscrs);
TableDsc* dsc;

  notePad.clear();

  for (dsc = iter(), i = 0; dsc; dsc = iter++)
                              if (dsc->selected) {if (i++) notePad << nCrlf;   dspRecords(dsc->accName);}
  }


void CodeGenIIDoc::dspRecords(String& name) {
DescTable  descTbl;
DTIter     iter(descTbl);
FieldDesc* dsc;
int        maxLng = 0;

  descTbl.load(maps, name);

  for (dsc = iter(); dsc; dsc = iter++) if (dsc->lng > maxLng) maxLng = dsc->lng;

  notePad << name << _T(" Table") << nCrlf;

  notePad << nSetRTab(3) << nSetTab(5) << nSetTab(8+maxLng) << nSetRTab(maxLng+26);

  notePad << nTab << _T("No") << nTab << _T("Name")  << nTab << _T("Type");
  notePad << nTab << _T("Is Index") << nCrlf;

  for (dsc = iter(); dsc; dsc = iter++) {

    notePad << nTab << dsc->fieldIndex;
    notePad << nTab << dsc->name;
    notePad << nTab << getDbCppType(dsc->x);
    notePad << nTab << dsc->isIndex;
    notePad << nCrlf;
    }
  }
#endif


void CodeGenIIDoc::OnOptions() {options();  view()->setOrientation(options.orient);}


void CodeGenIIDoc::display(DataSource ds) {dataSource = ds; invalidate();}


// CodeGenIIDoc serialization

void CodeGenIIDoc::serialize(Archive& ar) {

  if (ar.isStoring()) switch(dataSource) {
                        case NoteSource : notePad.archive(ar); return;
                        default         : return;
                        }

  switch(dataSource) {
    case NoteSource     : return;
    case DataBaseSource : {Maps* m = (Maps*) ar.getObj();  if (m) m->loadMaps(); return;}
    }
  }


// CodeGenIIDoc diagnostics

#ifdef _DEBUG
void CodeGenIIDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CodeGenIIDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

