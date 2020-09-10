// Table Extension Template


#include "stdafx.h"
#include "TableExtension.h"
#include "CodeGenII.h"
#include "CodeGenIIDoc.h"
#include "NotePad.h"
#include "SelectFldDlg.h"
#include "TableDscrs.h"
#include "VarDecl.h"



extern TCchar* HeaderPat;
extern TCchar* CppPat;


bool TableExtension::operator() (TableDsc& tblDsc) {
String       s = tblDsc.accName + _T("Tbl");
SelectFldDlg dlg(col);

  load(tblDsc.accName);   //col.initialize(descTbl);

  dlg.title = tbl.cls;

  if (dlg.DoModal() != IDOK) return false;

  notePad.clear();   createTblExtHdr(); invalidate();
  doc()->saveFile(_T("Header File"), s, _T(".h"), HeaderPat);

  notePad.clear();   createTblExtCpp(); invalidate();
  doc()->saveFile(_T("Body File"), s, _T(".cpp"), CppPat);

  return true;
  }



void TableExtension::createTblExtHdr() {
String s;

  notePad << _T("// ") << tbl.name << _T(" Table Extension Template") << nCrlf << nCrlf << nCrlf;

  notePad << _T("#pragma once") << nCrlf;

  notePad << _T("#include \"") << tbl.name << _T("Map.h\"") << nCrlf << nCrlf << nCrlf;

  notePad << _T("class ") << tbl.tblCls << _T(" : public ") << tbl.cls << _T(" {") << nCrlf << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.tblCls << _T("() : ") << tbl.cls << _T("() { }") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* get(") << col.getArgs() << _T(");") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* find(const long key) {");
  notePad << tbl.iter << _T(" iter(*this); return iter.find(key);}") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* find(") << col.getArgs() << _T(");") << nCrlf;

  notePad << _T("  };") << nCrlf;
  }


void TableExtension::createTblExtCpp() {
VarDeclarations decl;
ClnIter         iter(col);
FldDsc*         dsc;
int             j;
String          s;

  notePad << _T("// ") << tbl.name << _T(" Table Extension Template") << nCrlf << nCrlf << nCrlf;

  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"") << tbl.tblCls << _T(".h\"") << nCrlf;
  if (col.noStringsSel > 1) notePad << _T("#include \"Utilities.h\"") << nCrlf;
  notePad<< nCrlf << nCrlf;

  notePad << tbl.rcd << _T("* ") << tbl.tblCls << _T("::get(");
  notePad << col.getArgs() << _T(") {") << nCrlf;
  notePad << tbl.rcd << _T("* r = find(") << col.getCallArgs() << _T(");   if (r) return r;");
  notePad << nCrlf;
  notePad << tbl.rcd << _T("  rcd;") << nCrlf << nCrlf;

  if (col.noStringsSel) notePad << _T("  ");

  for (dsc = iter(), j = 0; dsc; dsc = iter++) {

    if (dsc->selected) {
      if (j) notePad << _T(" ");

      notePad << _T("rcd.") << dsc->name << _T(" = ") << dsc->object << _T(";");   j++;
      }
    }

  if (j > 2) notePad << nCrlf;

  notePad << _T("  rcd.mark();  ") << tbl.cls << _T("::add(rcd);") << nCrlf << nCrlf;

  notePad << _T("  toDatabase();   return find(") << col.getCallArgs() << _T(");") << nCrlf;

  notePad << _T("  }") << nCrlf << nCrlf << nCrlf;

  notePad << tbl.rcd <<  _T("* ") << tbl.tblCls << _T("::find(") << col.getArgs();
  notePad << _T(") {") << nCrlf;

  decl.clear();
  decl.add(tbl.iter, _T("iter(*this)"));
  s = tbl.rcd + _T('*');
  decl.add(s, _T("rcd"));
  decl.output();   notePad << nCrlf;

  testArgsEmpty();   notePad << nCrlf;

  notePad << _T("  for (rcd = iter(); rcd; rcd = iter++)") << nCrlf;

  notePad << _T("    if (");

  for (dsc = iter(), j = 0; dsc; dsc = iter++) {

    if (dsc->selected) {
      if (j) notePad << _T(" && ");

      notePad <<  _T("rcd->") << dsc->name << _T(" == ") << dsc->object;   j++;
      }
    }
  notePad << _T(") return rcd;") << nCrlf << nCrlf;


  notePad << _T("  return 0;") << nCrlf;
  notePad << _T("  }") << nCrlf << nCrlf;
  }


void TableExtension::testArgsEmpty() {
ClnIter iter(col);
FldDsc* dsc;
int     j;

  for (dsc = iter(), j = 0; dsc; dsc = iter++) {

    if (dsc->selected && dsc->typ == _T("String")) {
      if (col.noStringsSel > 1) {
        if (!j) notePad << _T("  if (isEmpty(");
        if (j)  notePad << _T(", ");

        notePad << _T('&') << dsc->object;
        }
      else notePad << _T("  if (") << dsc->object << _T(".isEmpty()");

      j++;
      }
    }

  if (j) {
    if (col.noStringsSel > 1) notePad << _T(", 0)");
    notePad << _T(") return 0;") << nCrlf;
    }
  }


void Collection::initialize(DescTable& descTbl) {
DTIter     iter(descTbl);
FieldDesc* fldDesc;

  fields.clear();

  for (fldDesc = iter(); fldDesc; fldDesc = iter++) {

    if (fldDesc->isIndex) continue;

    FldDsc& fd = fields.nextData();

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

