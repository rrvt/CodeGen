// CodeGenDoc.cpp : implementation of the CodeGenDoc class
//

#include "stdafx.h"
#include "CodeGenDoc.h"
#include "AceDao.h"
#include "CodeGen.h"
#include "CodeGenView.h"
#include "filename.h"
#include "Crypt.h"
#include "GetPathDlg.h"
#include "LicenseDlg.h"
#include "MainFrm.h"
#include "MapCode.h"
#include "MapDataDlg.h"
#include "NotePad.h"
#include "TableOp.h"
#include "TestMap.h"


enum {col2 = 10, col3 = 35, col4 = 58, col5 = 81};



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CodeGenDoc

IMPLEMENT_DYNCREATE(CodeGenDoc, CDocument)

BEGIN_MESSAGE_MAP(CodeGenDoc, CDocument)

  ON_COMMAND(ID_TableOps,       &CodeGenDoc::createTableCode)
  ON_COMMAND(ID_TableExtension, &CodeGenDoc::onTableExtension)
  ON_COMMAND(ID_MapData,        &CodeGenDoc::OnMapData)
  ON_COMMAND(ID_CreateLicense,  &CodeGenDoc::createLicense)
  ON_COMMAND(ID_DisplayDB,      &CodeGenDoc::OnDisplayDB)

END_MESSAGE_MAP()


// CodeGenDoc construction/destruction

CodeGenDoc::CodeGenDoc() {
  notePad.open();

//  SetTitle(_T("Code Gen -- RR Van Tuyl"));
  }


CodeGenDoc::~CodeGenDoc() { }



#define myKey _T("Alley, Ali, Bobbi, Tache, Clovis")


void CodeGenDoc::createLicense() {
LicenseDlg license;
String     key;
int        pos;
Crypt      crypt;
Byte       encryption[128];
ByteBlock  enc(noElements(encryption), encryption);
String     decStg;
Date       today;
DWORD      i;
String     date;

  notePad.close();

  if (license.DoModal() == IDOK) {

    key = license.key;

    today.getToday();
    today += 365;
    key += _T('#');

    date = today; // , 12)

    pos = (int) date.find(_T('.'));

    key += date.substr(0, pos+1); key += _T("0#");

    if (crypt.enc(key, String(myKey), enc)) {

      notePad << _T("// license.cpp : Defines the exported functions for the DLL application.") << nCrlf;
      notePad << nCrlf;
      notePad << _T("#include \"stdafx.h\"") << nCrlf;
      notePad << _T("#include \"license.h\"") << nCrlf;
      notePad << _T("#include <stdexcept>") << nCrlf << nCrlf;

      notePad << _T("using namespace std;") << nCrlf << nCrlf;

      notePad << _T("namespace License {") << nCrlf << nCrlf << nCrlf;

      notePad << _T("static Byte data[] = {");
      for (i = 0; i < enc.noBytes; i++) {
        if (i != 0) {
          if (i % 8) notePad << _T(", ");
          else       notePad << _T(",") << nCrlf << _T("                      ");
          }
        notePad << enc.bytes[i];
        }
      notePad << _T("};") << nCrlf << nCrlf;

      notePad << _T("#define myKey \"Alley, Ali, Bobbi, Tache, Clovis\"") << nCrlf << nCrlf << nCrlf;

      notePad << _T("bool get(ByteBlock& license) {") << nCrlf;
      notePad << _T("Crypt     crypt;") << nCrlf;
      notePad << _T("ByteBlock enc(noElements(data), data);") << nCrlf << nCrlf;

      notePad << _T("  return crypt.dec(enc, String(myKey), license);") << nCrlf;
      notePad << _T("  }") << nCrlf;
      notePad << _T("}") << nCrlf;
      }
    }

  saveFile(_T("License File"), _T("License.cpp"), _T(".cpp"), _T("Save File|*.cpp|All Files|*.*||"));
  invalidateView();
  }


void CodeGenDoc::createTableCode() {
TableOp tableOp;
String  accTableName;
String  name;

  tableOp.tableName = "";

  if (tableOp.DoModal() == IDOK) {

    accTableName = tableOp.tableName; name = tableOp.name;

    createCode(accTableName, name);

    invalidateView();
    }
  }



void CodeGenDoc::createCode(String& accTableName, String& name) {
MapCode mapCode;
int     noDesc;

  noDesc = mapCode.load(accTableName);

  Table table(accTableName, name, mapCode.getKeyDesc());

  notePad.close();   mapCode.createHeader(table);  invalidateView();
  saveFile(_T("Header File"), table.fileName, _T("h"), HeaderExt);

  notePad.close();   mapCode.createCpp(table);     invalidateView();
  saveFile(_T("Body File"), table.fileName, _T("cpp"), CppExt);
  }


void CodeGenDoc::onTableExtension() {
MapDataDlg dlg;
MapCode    mapCode;

  dlg.title = _T("Create Table Extension Modules");

  if (dlg.DoModal() == IDOK) {

    mapCode.createTableExtensions();
    }
  }


void CodeGenDoc::OnMapData() {
MapDataDlg dlg;
MapCode    mapCode;

  dlg.title = _T("Create Map Data File with Checked Tables");

  if (dlg.DoModal() == IDOK) {

    notePad.close();   mapCode.createMapDataHdr(); invalidateView();
    saveFile(_T("Header File"), _T("MapData"), _T(".h"), HeaderExt);

    notePad.close();   mapCode.createMapDataCpp(); invalidateView();
    saveFile(_T("Body File"), _T("MapData"), _T(".cpp"), CppExt);

    notePad.close();   mapCode.createMapsHdr();  invalidateView();
    saveFile(_T("Header File"), _T("Maps"), _T(".h"), HeaderExt);

    notePad.close();   mapCode.createMapsCpp();  invalidateView();
    saveFile(_T("Body File"), _T("Maps"), _T(".cpp"), CppExt);
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


// CodeGenDoc serialization

void CodeGenDoc::serialize(Archive& ar) {if (ar.isStoring()) notePad.archive(ar);}



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


// CodeGenDoc commands

static TCchar* dbExtensions =  _T("*.accdb;*.mdb");


void CodeGenDoc::OnDisplayDB() {
MapDataDlg dlg;
int        i;
TableDsc*  p;

  notePad.close();

  dlg.title = _T("Display Record Fields");

  if (dlg.DoModal() == IDOK)
    for (p = tableDscrs.startLoop(), i = 0; p; p = tableDscrs.nextEntry(), i++) {
      if (i) notePad << nCrlf;
      if (p->selected) dspRecords(p->name);
      }
  }


void CodeGenDoc::dspRecords(String& name) {
DescTable  descTbl;
FieldDesc* dsc;
int        maxLng = 0;

  descTbl.load(maps, name);

  for (dsc = descTbl.startLoop(); dsc; dsc = descTbl.nextDesc())
                                                              if (dsc->lng > maxLng) maxLng = dsc->lng;

  notePad << name << _T(" Table") << nCrlf;

  notePad << nSetRTab(3) << nSetTab(5) << nSetTab(8+maxLng) << nSetRTab(maxLng+26);

  notePad << nTab << _T("No") << nTab << _T("Name")  << nTab << _T("Type");
  notePad << nTab << _T("Is Index") << nCrlf;

  for (dsc = descTbl.startLoop(); dsc; dsc = descTbl.nextDesc()) {

    notePad << nTab << dsc->fieldIndex;
    notePad << nTab << dsc->name;
    notePad << nTab << getDbCppType(dsc->x);
    notePad << nTab << dsc->isIndex;
    notePad << nCrlf;
    }

  invalidateView();
  }

#if 0
void CodeGenDoc::dspRecords(MapTable* tbl) {
MapRecord* rcd;
int        max = 0;
int        lng;

  if (!tbl) return;

  notePad.close();

  notePad << tbl->name << _T(" Table Size = ") << tbl->curSize() << nCrlf << nCrlf;

  for (rcd = tbl->startLoop(); rcd; rcd = tbl->nextRecord()) {

    String s = rcd->getFldVal(1);   lng = s.length();   if (lng > max) max = lng;
    }

  notePad << nSetTab(5) << nSetTab(max + 8);

  for (rcd = tbl->startLoop(); rcd; rcd = tbl->nextRecord()) {

    notePad << rcd->getFldVal(0) << nTab << rcd->getFldVal(1) << nTab << rcd->getFldVal(2) << nCrlf;
    }

  invalidateView();
  }
#endif




void CodeGenDoc::listTables(AceDao& dao) {
AceTables  tables(dao);
TableDesc* dsc;
int i;

  notePad << _T("Tables - number of tables: ") << tables.count() << nCrlf << nCrlf;

  notePad << nClrTabs << nSetTab(11) << nSetTab(30) << nSetTab(45);
  notePad << nTab << _T("Name") << nTab << _T("No of Fields") << nTab << _T("No of Records");
  notePad << nCrlf;

  notePad << nClrTabs << nSetTab(11) << nSetRTab(36) << nSetRTab(52);

  for (i = 1, dsc = tables.startLoop(); dsc; dsc = tables.nextTable(), i++) {

    notePad << _T("Table ") << i << _T(":") << nTab << nTableName << dsc->name;

    notePad << nTab << dsc->nFlds << nTab << dsc->nRcds << nCrlf;
    }
  }



void CodeGenDoc::testTestMap() {
MyTable myTable;
String  t1 = _T("first string!");
String  t2 = _T("Second String");
Record  rcd;
Record* r;
int     sz;
long    x;
String  f1;
String  f2;
long    key;

  rcd.key = 12; rcd.fld1 = t1;          rcd.fld2 = t2;          myTable.add(rcd); sz = myTable.curSize();
  rcd.key = 27; rcd.fld1 = _T("Alpha"); rcd.fld2 = _T("Beta");  myTable.add(rcd); sz = myTable.curSize();
  rcd.key = 17; rcd.fld1 = _T("Gamma"); rcd.fld2 = _T("Delta"); myTable.add(rcd); sz = myTable.curSize();

  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {
    x   = r->key;
    f1  = r->fld1;
    f2  = r->fld2;
    key = myTable.curKey();
    int y = 1;
    }

  key = myTable.curKey();

  r = myTable.find(17);
  x   = r->key;
  f1  = r->fld1;
  f2  = r->fld2;
  key = myTable.curKey();

  rcd.key = 19; rcd.fld1 = _T("Smoke");  rcd.fld2 = _T("Mirrors"); myTable.add(rcd);
  r = myTable.find(19);
  x   = r->key;
  f1  = r->fld1;
  f2  = r->fld2;
  key = myTable.curKey();    sz = myTable.curSize();

  x = myTable.erase(17);    sz = myTable.curSize();

  for (r = myTable.startRLoop(); r; r = myTable.prevRecord()) {
    x   = r->key;
    f1  = r->fld1;
    f2  = r->fld2;
    key = myTable.curKey();
    int y = 1;
    }
  }

