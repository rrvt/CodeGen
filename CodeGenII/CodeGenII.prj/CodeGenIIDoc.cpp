// CodeGenIIDoc.cpp : implementation of the CodeGenIIDoc class


#include "stdafx.h"
#include "CodeGenIIDoc.h"
#include "DBtbl.h"
#include "DBtables.h"
#include "ExtraResource.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MessageBox.h"
#include "MdlBody.h"
#include "MdlHeader.h"
#include "Module.h"
#include "NotePad.h"
#include "Options.h"
#include "Resource.h"
#include "CodeGenII.h"
#include "CodeGenIIView.h"
#include "ToolBar.h"


TCchar* FileSection      = _T("DataBase File Names");
TCchar* DBFileKey        = _T("DataBase File");
TCchar* GenFilePathKey   = _T("GenFilePath");

static TCchar* HeaderPat = _T("*.h");
static TCchar* CppPat    = _T("*.cpp");


// CodeGenIIDoc

IMPLEMENT_DYNCREATE(CodeGenIIDoc, CDoc)

BEGIN_MESSAGE_MAP(CodeGenIIDoc, CDoc)
  ON_COMMAND(ID_File_Open,     &OnFileOpen)
  ON_CBN_SELCHANGE(ID_CB,      &OnComboBoxChng)
  ON_COMMAND(      ID_CB,      &OnComboBoxChng)
  ON_COMMAND(ID_DBtable,       &onDBtable)
  ON_COMMAND(ID_File_Save,     &OnFileSave)
  ON_COMMAND(ID_Options,       &OnOptions)
END_MESSAGE_MAP()


// CodeGenIIDoc construction/destruction

CodeGenIIDoc::CodeGenIIDoc() noexcept : dataSource(NotePadSrc) {
  pathDlgDsc = PathDlgDsc(_T("Ugly Example"), _T(""), _T("txt"), _T("*.txt"));
  }

CodeGenIIDoc::~CodeGenIIDoc() { }


void CodeGenIIDoc::OnFileOpen() {
TBComboBox* cb = TBComboBox::get(ID_CB);      if (!cb) return;
String      path;
DAOiter     iter(daoTables);
DAOtable*   doaTbl;

  notePad.clear();

  if (getPathDlg(_T("Database"), 0, _T("accdb"), _T("*.accdb"), path))
                                                       iniFile.writeString(FileSection, DBFileKey, path);
  if (!dbTables.load(path)) return;

  dbTbl.loadTableNames();

  for (doaTbl = iter(); doaTbl; doaTbl = iter++) cb->AddSortedItem(doaTbl->name);

  cb->SelectItem(-1);   dbTables.display();   display(NotePadSrc);
  }



void CodeGenIIDoc::OnComboBoxChng() {
TBComboBox* cb   = TBComboBox::get(ID_CB);    if (!cb)   return;
int         i    = cb->GetCurSel();           if (i < 0) return;
String      name = cb->GetItem(i);
Module      module(name);
MdlHeader   hdr(module);
MdlBody     body(module);
String      tblName = name + _T("Tbl");

  if (!module.getSearchFields()) return;

  hdr.create();

  pathDlgDsc = PathDlgDsc(_T("Header File"), tblName, _T(".h"), HeaderPat);   saveFile();

  body.create();

  pathDlgDsc = PathDlgDsc(_T("Body File"), tblName, _T(".cpp"), CppPat);   saveFile();

  Table* tbl = dbTbl.find(name);   if (tbl) tbl->selected = true;

  display(NotePadSrc);
  }


void CodeGenIIDoc::onDBtable() {

  dbTbl.hdrCreate();

  pathDlgDsc = PathDlgDsc(_T("Header File"), _T("DBtables"), _T(".h"), HeaderPat);   saveFile();

  dbTbl.bodyCreate();

  pathDlgDsc = PathDlgDsc(_T("Body File"), _T("DBtables"), _T(".cpp"), CppPat);   saveFile();

  display(NotePadSrc);
  }


void CodeGenIIDoc::OnOptions() {options(view());  view()->setOrientation(options.orient);}


void CodeGenIIDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void CodeGenIIDoc::OnFileSave() {if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);}


void CodeGenIIDoc::saveFile() {
String path;
String filePath;

  iniFile.readString(FileSection, GenFilePathKey, path);   path = ::getPath(path);

  path += pathDlgDsc.name;

  if (getSaveAsPathDlg(pathDlgDsc, filePath)) {

    iniFile.writeString(FileSection, GenFilePathKey, ::getPath(filePath));

    dataSource = NotePadSrc;   OnSaveDocument(filePath);
    }
  }


// UglyDoc serialization

void CodeGenIIDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case NotePadSrc : notePad.archive(ar); return;
      default         : return;
      }

  else
    switch(dataSource) {
      case FontSrc  :
      default       : return;
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


