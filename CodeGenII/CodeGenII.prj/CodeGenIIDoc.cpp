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


// CodeGenIIDoc

IMPLEMENT_DYNCREATE(CodeGenIIDoc, CDoc)

BEGIN_MESSAGE_MAP(CodeGenIIDoc, CDoc)
  ON_COMMAND(ID_TableOps,       &CodeGenIIDoc::createTableCode)
  ON_COMMAND(ID_TableExtension, &CodeGenIIDoc::onTableExtension)
  ON_COMMAND(ID_MapData,        &CodeGenIIDoc::OnMapData)
  ON_COMMAND(ID_DisplayDB,      &CodeGenIIDoc::OnDisplayDB)
  ON_COMMAND(ID_FILE_OPEN,      &CodeGenIIDoc::OnFileOpen)
  ON_COMMAND(ID_FILE_SAVE,      &CodeGenIIDoc::OnFileSave)
  ON_COMMAND(ID_Test,           &CodeGenIIDoc::OnTest)
  ON_COMMAND(ID_Options,        &CodeGenIIDoc::OnOptions)
END_MESSAGE_MAP()


// CodeGenIIDoc construction/destruction

CodeGenIIDoc::CodeGenIIDoc() noexcept {
  saveAsTitle = _T("Code Gen II");   defExt = _T("txt");   defFilePat = _T("*.txt");
  }

CodeGenIIDoc::~CodeGenIIDoc() { }


BOOL CodeGenIIDoc::OnNewDocument() {return CDocument::OnNewDocument();}




void CodeGenIIDoc::OnDisplayDB() {
MapDataDlg dlg;
int        i;
TDIter    iter(tableDscrs);
TableDsc* dsc;

  notePad.clear();

  dlg.title = _T("Display Record Fields");

  if (dlg.DoModal() == IDOK)
    for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
      if (i) notePad << nCrlf;
      if (dsc->selected) dspRecords(dsc->accName);
      }
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

  invalidate();
  }



void CodeGenIIDoc::createTableCode() {
TableOpDlg dlg;
String     tblName;
String     abbr;

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




void CodeGenIIDoc::onTableExtension() {
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


// CodeGenIIDoc commands


void CodeGenIIDoc::OnTest() {

  theApp.setTitle(_T("My Test"));

  notePad.clear();  notePad << _T("Hello World") << nCrlf;

  invalidate();
  }


void CodeGenIIDoc::OnOptions() {
OptionsDlg dlg;

  dlg.topMargin   = options.topMargin;
  dlg.leftMargin  = options.leftMargin;
  dlg.rightMargin = options.rightMargin;
  dlg.botMargin   = options.botMargin;

  if (dlg.DoModal() == IDOK) {
    options.topMargin    = dlg.topMargin;
    options.leftMargin   = dlg.leftMargin;
    options.rightMargin  = dlg.rightMargin;
    options.botMargin    = dlg.botMargin;

    options.store();
    }
  }



void CodeGenIIDoc::OnFileOpen() {
String path;

  saveAsTitle = _T("Code Gen II");   defExt = _T("txt");   defFilePat = _T("*.txt");

  if (!getPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);   view()->rightFooter= defFileName;  view()->date.getToday();

  notePad.clear();

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

  dataStore.setName(defFileName);  invalidate();
  }


void CodeGenIIDoc::OnFileSave() {
String path;

  if (!getSaveAsPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  OnSaveDocument(path);
  }


// CodeGenIIDoc serialization

void CodeGenIIDoc::serialize(Archive& ar) {

  if (ar.isStoring()) {notePad.archive(ar); return;}

  dataStore.load(ar);
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

