// CodeGenDoc.cpp : implementation of the CodeGenDoc class


#include "pch.h"
#include "CodeGenDoc.h"
#include "AbbrDlg.h"
#include "CodeGen.h"
#include "CodeGenView.h"
#include "DatabaseBdy.h"
#include "DatabaseHdr.h"
#include "DbTblList.h"
#include "DbTblSelDlg.h"
#include "filename.h"
#include "IniFileEx.h"
#include "LinSrch.h"
#include "MainFrame.h"
#include "ModNames.h"
#include "RcdSetBdy.h"
#include "RcdSetHdr.h"
#include "Resource.h"
#include "ResourceExtra.h"
#include "TableHdr.h"
#include "TableBdy.h"


static TCchar* FileSection      = _T("DataBase File Names");
static TCchar* DBFileKey        = _T("DataBase File");
static TCchar* GenFilePathKey   = _T("GenFilePath");

static TCchar* HeaderPat        = _T("*.h");
static TCchar* CppPat           = _T("*.cpp");


// CodeGenDoc

IMPLEMENT_DYNCREATE(CodeGenDoc, CDoc)

BEGIN_MESSAGE_MAP(CodeGenDoc, CDoc)
  ON_COMMAND(      ID_File_Open, &OnFileOpen)
  ON_CBN_SELCHANGE(ID_CB,        &OnComboBoxChng)
  ON_COMMAND(      ID_CB,        &OnComboBoxChng)

  ON_COMMAND(      ID_RcdSet,    &onRcdSet)
  ON_COMMAND(      ID_DBtable,   &onDBtable)
  ON_COMMAND(      ID_Database,  &onDatabase)

  ON_COMMAND(      ID_File_Save, &OnFileSave)
END_MESSAGE_MAP()


// CodeGenDoc construction/destruction

CodeGenDoc::CodeGenDoc() noexcept : dataSource(NotePadSrc), dbOpened(false), tableSelected(false) {
  pathDlgDsc(_T("Ugly Example"), _T(""), _T("txt"), _T("*.txt"));
  }

CodeGenDoc::~CodeGenDoc() { }


void CodeGenDoc::OnFileOpen() {
PathDlgDsc dsc;
DbTblIter  iter(dbTblList);
TblItem*   item;
MyToolBar& toolBar = mainFrm()->getToolBar();

  notePad.clear();

  dsc(_T("Database"), 0, _T("accdb"), _T("*.accdb"));

  if (!setOpenPath(dsc)) return;

  iniFile.writeString(FileSection, DBFileKey, path);

  notePad << nSetTab(20);

  dbTblList.load(path);

  for (item = iter(); item; item = iter++) toolBar.addCbxItemSorted(ID_CB, item->name);

  toolBar.setCaption(ID_CB, _T("Database Tables"));

  toolBar.setWthPercent(ID_CB, 80);   toolBar.setWidth(ID_CB);   toolBar.setHeight(ID_CB);

  dbOpened = true;  display(NotePadSrc);
  }


void CodeGenDoc::OnComboBoxChng() {
MyToolBar& toolBar = mainFrm()->getToolBar();
String     table;
void*      x;
AbbrDlg    dlg;
TblItem*   tblItem;

  if (!dbOpened) return;

  tableSelected = false;

  if (!toolBar.getCurSel(ID_CB, table, x)) return;

  if (!fields.load(path, table)) return;

  dlg.table = table;

  if (dlg.DoModal() != IDOK) return;

  tblItem = dbTblList.find(table);   if (tblItem) tblItem->getPKey();

  if (!modNames.set(table)) {notePad << _T("modNames failure") << nCrlf; return;}

  modNames.noFields = fields.nData();

  notePad.clear();   fields.display();    tableSelected = true;

  display(NotePadSrc);
  }


void CodeGenDoc::onRcdSet() {
RcdSetHdr hdr;
RcdSetBdy bdy;

  if (!tableSelected) return;

  hdr.create();
  pathDlgDsc(_T("RcdSetHdr File"), modNames.setCls, _T(".h"), HeaderPat);    saveFile();

  bdy.create();
  pathDlgDsc(_T("RcdSetBdy File"), modNames.setCls, _T(".cpp"), CppPat);     saveFile();

  display(NotePadSrc);
  }


void CodeGenDoc::onDBtable() {
TableHdr hdr;
TableBdy bdy;

  if (!tableSelected) return;

  linSrch.getFields();

  hdr.create();
  pathDlgDsc(_T("Table hdr File"), modNames.tblCls, _T(".h"), HeaderPat);   saveFile();

  bdy.create();
  pathDlgDsc(_T("Table cpp File"), modNames.tblCls, _T(".cpp"), CppPat);    saveFile();

  display(NotePadSrc);
  }


void CodeGenDoc::onDatabase() {
DbTblSelDlg dlg(dbTblList);
DatabaseHdr hdr;
DatabaseBdy bdy;

  if (!dbOpened) return;

  if (dlg.DoModal() != IDOK) return;

  hdr.create();
  pathDlgDsc(_T("Table hdr File"), _T("Database"), _T(".h"),   HeaderPat);   saveFile();

  bdy.create();
  pathDlgDsc(_T("Table hdr File"), _T("Database"), _T(".cpp"), CppPat);      saveFile();
  }


void CodeGenDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void CodeGenDoc::OnFileSave() {if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);}


void CodeGenDoc::saveFile() {
String path;
String filePath;

  iniFile.readString(FileSection, GenFilePathKey, path);   path = ::getPath(path);

  path += pathDlgDsc.name;

  if (getSaveAsPathDlg(pathDlgDsc, filePath)) {

    String pth = ::getPath(filePath);

    iniFile.writeString(FileSection, GenFilePathKey, pth);

    dataSource = NotePadSrc;   OnSaveDocument(filePath);
    }
  }


// UglyDoc serialization

void CodeGenDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case NotePadSrc : ar << notePad; return;
      default         : return;
      }

  else return;
  }


// CodeGenDoc diagnostics

#ifdef _DEBUG
void CodeGenDoc::AssertValid() const          {CDocument::AssertValid();}
void CodeGenDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG



