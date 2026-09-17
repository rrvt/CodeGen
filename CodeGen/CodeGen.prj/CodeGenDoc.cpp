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
#include "Invalidate.h"
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
  ON_COMMAND(      ID_Open,      &OnFileOpen)
  ON_CBN_SELCHANGE(ID_CB,        &OnComboBoxChng)
  ON_COMMAND(      ID_CB,        &OnComboBoxChng)

  ON_COMMAND(      ID_RcdSet,    &onRcdSet)
  ON_COMMAND(      ID_DBtable,   &onDBtable)
  ON_COMMAND(      ID_Database,  &onDatabase)

  ON_COMMAND(      ID_Save,      &OnFileSave)
END_MESSAGE_MAP()


// CodeGenDoc construction/destruction

CodeGenDoc::CodeGenDoc() noexcept : dataSource(NotePadSrc), dbOpened(false), tableSelected(false) {
  }

CodeGenDoc::~CodeGenDoc() { }


void CodeGenDoc::OnFileOpen() {
PathDlg    dlg(_T("Database"), 0, _T("accdb"), _T("Database"), _T("*.accdb"));
DbTblIter  iter(dbTblList);
TblItem*   item;
MyToolBar& toolBar = mainFrm()->getToolBar();

  notePad.clear();

  iniFile.read(FileSection, DBFileKey, dlg.iPath);

  if (!dlg.openFile(path)) return;

  iniFile.writeString(FileSection, DBFileKey, path);

  notePad << nSetTab(20);

  dbTblList.load(path);

  for (item = iter(); item; item = iter++) toolBar.addCboItemSrtd(ID_CB, item->name);

  toolBar.setCboCaption(ID_CB, _T("Database Tables"));

  toolBar.setCboWthPrct(ID_CB, 80);   toolBar.setCboHeight(ID_CB);

  dbOpened = true;  display(NotePadSrc);
  }


void CodeGenDoc::OnComboBoxChng() {
MyToolBar& toolBar = mainFrm()->getToolBar();
String     table;
ulongP     x;
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
  dlg(_T("RcdSetHdr File"), modNames.setCls, _T("h"), _T("Header File"), HeaderPat);    saveFile();

  bdy.create();
  dlg(_T("RcdSetBdy File"), modNames.setCls, _T("cpp"), _T("Body File"), CppPat);     saveFile();

  display(NotePadSrc);
  }


void CodeGenDoc::onDBtable() {
TableHdr hdr;
TableBdy bdy;
String   s;

  if (!tableSelected) return;

  linSrch.getFields();

  hdr.create();
  dlg(_T("Table hdr File"), modNames.tblCls, _T("h"), _T("Header File"), HeaderPat);   saveFile();

  bdy.create();
  dlg(_T("Table cpp File"), modNames.tblCls, _T("cpp"), _T("Body File"), CppPat);      saveFile();

  bdy.createDsp();   s = modNames.tblCls + _T("Dsp");
  dlg(_T("Table Display cpp File"), s, _T("cpp"), _T("Display cpp"), CppPat);          saveFile();


  display(NotePadSrc);
  }


void CodeGenDoc::onDatabase() {
DbTblSelDlg tblDlg(dbTblList);
DatabaseHdr hdr;
DatabaseBdy bdy;

  if (!dbOpened) return;

  if (tblDlg.DoModal() != IDOK) return;

  hdr.create();
  dlg(_T("Table hdr File"), _T("Database"), _T("h"), _T("Header File"), HeaderPat);   saveFile();

  bdy.create();
  dlg(_T("Table hdr File"), _T("Database"), _T("cpp"), _T("Body File"), CppPat);      saveFile();
  }


void CodeGenDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void CodeGenDoc::OnFileSave() {if (dlg.saveFileAs(path)) OnSaveDocument(path);}


void CodeGenDoc::getHeader(NotePad& np, int pageNo, int noPages)
  {np << _T("Header") << nRight << theApp.name;}


void CodeGenDoc::getFooter(NotePad& np, int pageNo, int noPages)
  {np << nCenter << _T("Page ") << pageNo << _T(" of ") << noPages;}


void CodeGenDoc::saveFile() {
String path;
String filePath;

  iniFile.readString(FileSection, GenFilePathKey, path);   path = ::getPath(path);

  path += dlg.iPath;

  if (dlg.saveFileAs(filePath)) {

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



