// Table Extension Template


#include "stdafx.h"
#include "TableExtension.h"
#include "codeGen.h"
#include "NotePad.h"
#include "SelectFldDlg.h"
#include "TableDscrs.h"


bool TableExtension::operator() (TableDsc& tbl) {
String       s = tbl.name + _T("Tbl");
SelectFldDlg dlg(col);

  load(tbl.name);   col.initialize(descTbl);

  dlg.title = col.tableName;

  if (dlg.DoModal() != IDOK) return false;

  notePad.clear();   createTblExtHdr(); invalidate();
  doc()->saveFile(_T("Header File"), s, _T(".h"), HeaderExt);

  notePad.clear();   createTblExtCpp(); invalidate();
  doc()->saveFile(_T("Body File"), s, _T(".cpp"), CppExt);

  return true;
  }



void TableExtension::createTblExtHdr() {
String s;

  notePad << _T("// ") << col.name << _T(" Table Extension Template") << nCrlf << nCrlf << nCrlf;

  notePad << _T("#pragma once") << nCrlf;

  notePad << _T("#include \"") << col.name << _T("Map.h\"") << nCrlf << nCrlf << nCrlf;

  notePad << _T("class ") << col.tblName << _T(" : public ") << col.tableName << _T(" {") << nCrlf << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("  ") << col.tblName << _T("() : ") << col.tableName << _T("() { }") << nCrlf << nCrlf;

  notePad << _T("  ") << col.recordName << _T("* get(") << col.getArgs() << _T(");") << nCrlf << nCrlf;

  notePad << _T("  ") << col.recordName << _T("* find(const long key) {return ");
  notePad << col.tableName << _T("::find(key);}") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  ") << col.recordName << _T("* find(") << col.getArgs() << _T(");") << nCrlf;

  notePad << _T("  };") << nCrlf;
  }


void TableExtension::createTblExtCpp() {
int    i;
int    j;
String s;

  notePad << _T("// ") << col.name << _T(" Table Extension Template") << nCrlf << nCrlf << nCrlf;

  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"") << col.tblName << _T(".h\"") << nCrlf;
  if (col.noStringsSel > 1) notePad << _T("#include \"Utilities.h\"") << nCrlf;
  notePad<< nCrlf << nCrlf;

  notePad << col.recordName << _T("* ") << col.tblName << _T("::get(");
  notePad << col.getArgs() << _T(") {") << nCrlf;
  notePad << col.recordName << _T("* r = find(") << col.getCallArgs() << _T(");   if (r) return r;");
  notePad << nCrlf;
  notePad << col.recordName << _T("  rcd;") << nCrlf << nCrlf;

  if (col.noStringsSel) notePad << _T("  ");

  for (i = 0, j = 0; i < col.fields.end(); i++) {
    FldDsc& fd = col.fields[i];

    if (fd.selected) {
      if (j) notePad << _T(" ");

      notePad << _T("rcd.") << fd.name << _T(" = ") << fd.object << _T(";");   j++;
      }
    }

  if (j > 2) notePad << nCrlf;

  notePad << _T("  rcd.mark();  ") << col.tableName << _T("::add(rcd);") << nCrlf << nCrlf;

  notePad << _T("  toDatabase();   return find(") << col.getCallArgs() << _T(");") << nCrlf;

  notePad << _T("  }") << nCrlf << nCrlf << nCrlf;

  notePad << col.recordName <<  _T("* ") << col.tblName << _T("::find(") << col.getArgs();
  notePad << _T(") {") << nCrlf;
  notePad << col.recordName << _T("* rcd;") << nCrlf << nCrlf;

  testArgsEmpty();   notePad << nCrlf;

  notePad << _T("  for (rcd = startLoop(); rcd; rcd = nextRecord())") << nCrlf;

  notePad << _T("    if (");

  for (i = 0, j = 0; i < col.fields.end(); i++) {
    FldDsc fd = col.fields[i];

    if (fd.selected) {
      if (j) notePad << _T(" && ");

      notePad <<  _T("rcd->") << fd.name << _T(" == ") << fd.object;   j++;
      }
    }
  notePad << _T(") return rcd;") << nCrlf << nCrlf;


  notePad << _T("  return 0;") << nCrlf;
  notePad << _T("  }") << nCrlf << nCrlf;
  }


void TableExtension::testArgsEmpty() {
int  n = col.fields.end();
int  i;
int  j;

  for (i = 0, j = 0; i < n; i++) {
    FldDsc& fd = col.fields[i];
    if (fd.selected && fd.typ == _T("String")) {
      if (col.noStringsSel > 1) {
        if (!j) notePad << _T("  if (isEmpty(");
        if (j)  notePad << _T(", ");

        notePad << _T('&') << fd.object;
        }
      else notePad << _T("  if (") << fd.object << _T(".isEmpty()");

      j++;
      }
    }

  if (j) {
    if (col.noStringsSel > 1) notePad << _T(", 0)");
    notePad << _T(") return 0;") << nCrlf;
    }
  }


void Collection::initialize(DescTable& descTbl) {
FieldDesc* fldDesc;

  name       = descTbl.getName();
  tblName    = name + _T("Tbl");
  tableName  = name + _T("Table");
  recordName = name + _T("Record");
  rcdName    = objName(recordName);

  for (fldDesc = descTbl.startLoop(); fldDesc; fldDesc = descTbl.nextDesc()) {

    if (fldDesc->isIndex) continue;

    FldDsc& fd = fields[fields.end()];

    fd.typ = getDbCppType(fldDesc->x);

    fd.set(fldDesc->name);
    }
  }

// Get as Arguments when args is true, otherwise as call

String& Collection::getArgs() {
int    n = fields.end();
int    i;
int    j;
String t;

  s.clear();

  for (i = 0, j = 0; i < n; i++) {
    FldDsc& fd = fields[i];

    if (fd.selected) {
      if (j) s += _T(", ");

      t = fd.typ == _T("String") ? _T("String&") : fd.typ;

      s += t + _T(' ') + fd.object;   j++;
      }
    }

  return s;
  }


String& Collection::getCallArgs() {
int n = fields.end();
int i;
int j;

  s.clear();

  for (i = 0, j = 0; i < n; i++) {
    FldDsc& fd = fields[i];

    if (fd.selected) {if (j) s += _T(", ");   s += fd.object;   j++;}
    }

  return s;
  }

