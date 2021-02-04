// Table Extension Template


#include "stdafx.h"
#include "TableCode.h"
#include "CodeGen.h"
#include "CodeGenDoc.h"
#include "NotePad.h"
#include "SelectFldDlg.h"
#include "TblList.h"
#include "VarDecl.h"



extern TCchar* HeaderPat;
extern TCchar* CppPat;


bool TableCode::operator() (TblDsc& tblDsc) {
String       s = tblDsc.accName + _T("Table");
SelectFldDlg dlg(col);

  load(tblDsc.accName);   //col.initialize(descTbl);

  dlg.title = tbl.mapName;

  if (dlg.DoModal() != IDOK) return false;

  notePad.clear();   createHeader(); invalidate();
  doc()->saveFile(_T("Header File"), s, _T(".h"), HeaderPat);

  notePad.clear();   createBody(); invalidate();
  doc()->saveFile(_T("Body File"), s, _T(".cpp"), CppPat);

  return true;
  }


void TableCode::createHeader() {
String s;

  notePad << _T("// ") << tbl.name << _T(" Table Extension Template") << nCrlf << nCrlf << nCrlf;

  notePad << _T("#pragma once") << nCrlf;

  notePad << _T("#include \"") << tbl.name << _T("Map.h\"") << nCrlf << nCrlf << nCrlf;

  createIterClass();  notePad << nCrlf << nCrlf;

  notePad << _T("class ") << tbl.tblName << _T(" : public ") << tbl.mapName << _T(" {") << nCrlf << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.tblName << _T("() : ") << tbl.mapName << _T("() { }") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* get(") << col.getArgs() << _T(");") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* find(const long key) {");
  notePad << tbl.iter << _T(" iter(*this); return iter.find(key);}") << nCrlf << nCrlf;

  if (col.allFieldsUsed())
    notePad << _T("  ") << tbl.keyType << _T(" add(") << col.getArgs(true) << _T(");") << nCrlf;

//  bool add(CityStateRecord& rcd) {return CityStateMap::add(rcd);}

  notePad << _T("  bool add(") << tbl.rcd << _T("& rcd) {return ");
  notePad << tbl.mapName << _T("::add(rcd);}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.keyType << _T(" findID(String& key);") << nCrlf;
  if (col.noChecked() > 1)
          {notePad << _T("  ") << tbl.keyType << _T(" findID(") << col.getArgs() << _T(");") << nCrlf;}

  notePad << nCrlf;

  notePad << _T("  bool toDatabase() {return ") << tbl.mapName << _T("::toDatabase();}") << nCrlf;

  notePad << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* find(") << col.getArgs() << _T(");") << nCrlf;

  notePad << _T("  };") << nCrlf;
  }



void TableCode::createIterClass() {
VarDeclarations decl;
String prefix;

  notePad << _T("class ") << tbl.iter << _T(" {") << nCrlf << nCrlf;

  prefix = _T("typedef ") + tbl.mapName + _T("::MyMap");  decl.add(prefix, _T("MyMap"));
  decl.add(_T("typedef MyMap::iterator"), _T("MyIter"));
  decl.output();   notePad << nCrlf;

  decl.clear();
  decl.add(_T("MyMap&"), _T("myMap"));
  decl.add(_T("MyIter"), _T("iter"));
  decl.output();   notePad << nCrlf;

  notePad << _T("typedef pair<MyIter, bool> Pair;") << nCrlf << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("enum Dir {Fwd, Rev};") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.iter << _T("(") << tbl.mapName;
  notePad << _T("& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* operator() (Dir rev = Fwd) {") << nCrlf;
  notePad << _T("    if (rev) {iter = myMap.end();   return decr();}") << nCrlf;
  notePad << _T("    else     {iter = myMap.begin(); ");
  notePad << _T("return iter == myMap.end() ? 0 : &iter->second;}") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* operator++ (int)") << nCrlf;
  notePad << _T("                            {return iter == myMap.end() ? 0 : ");
  notePad << _T("++iter == myMap.end() ? 0 : &iter->second;}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* operator-- (int) {return decr();}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* current() {return iter == myMap.end() ? 0 : &iter->second;}");
  notePad << nCrlf << nCrlf;

  notePad << _T("  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}") << nCrlf;
  notePad << _T("  bool isFirst() {return iter == myMap.begin();}") << nCrlf << nCrlf;

  notePad << _T("  void remove() {iter = myMap.erase(iter);}") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* find(const long key)") << nCrlf;
  notePad << _T("                               {iter = myMap.find(key);  ");
  notePad << _T("return iter == myMap.end() ? 0 : &iter->second;}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.rcd << _T("* decr() {return iter == myMap.begin() ? 0 : ");
  notePad << _T("&(--iter)->second;}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl.iter << _T("() : myMap(*(MyMap*) 0) { }                   ");
  notePad << _T("// Prevents uninitizlized iterator") << nCrlf << nCrlf;

  notePad << _T("  friend class ") << tbl.mapName << _T(";") << nCrlf;
  notePad << _T("  friend class ") << tbl.tblName << _T(";") << nCrlf;

  notePad << _T("  };") << nCrlf;
  }



void TableCode::createBody() {

  notePad << _T("// ") << tbl.name << _T(" Table Extension Template") << nCrlf << nCrlf << nCrlf;

  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"") << tbl.tblName << _T(".h\"") << nCrlf;
  if (col.noStringsSel > 1) notePad << _T("#include \"Utilities.h\"") << nCrlf;
  notePad << nCrlf << nCrlf;

  createGet();

  createAdd();

  createFindID();

  createFind();
  }


void TableCode::createGet() {
ClnIter iter(col);
FldDsc* dsc;
int     j;

  notePad << tbl.rcd << _T("* ") << tbl.tblName << _T("::get(");
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

  notePad << _T("  rcd.mark();  ") << tbl.mapName << _T("::add(rcd);") << nCrlf << nCrlf;

  notePad << _T("  toDatabase();   return find(") << col.getCallArgs() << _T(");") << nCrlf;

  notePad << _T("  }") << nCrlf << nCrlf;
  }


void TableCode::createAdd() {
VarDeclarations decl;
DescTable       dscTbl(tbl.name);
DTIter          iter(dscTbl);
FieldDesc*      fldDsc = iter();       fldDsc = iter++;   if (!fldDsc) return;
String          key    = fldDsc->name; fldDsc = iter++;   if (!fldDsc) return;
String          dsc    = fldDsc->name;
int             n;

  if (!col.allFieldsUsed()) return;

  notePad << nCrlf;
  notePad << tbl.keyType << _T(" ") << tbl.tblName << _T("::add(") << col.getArgs(true) << _T(") {");
  notePad << nCrlf;

  decl.clear();
  n = col.getArgDecls(decl);
  decl.add(tbl.keyType, _T("id"));
  decl.output(); notePad << nCrlf;

  notePad << _T("  if (") << col.argsEmpty() << _T(") return 0;") << nCrlf << nCrlf;

  notePad << _T("  id = findID(") << col.getArgs(n) << _T(");   if (id) return id;") << nCrlf << nCrlf;
  notePad << _T("  ") << tbl.rcd << _T(" r;  ");
  notePad << col.argsToRcd();
  notePad << nCrlf;
  notePad << _T("  r.mark();   ") << tbl.mapName << _T("::add(r);") << nCrlf << nCrlf;
  notePad << _T("  toDatabase();   return findID(") << col.getArgs(n) << _T(");") << nCrlf;
  notePad << _T("  }") << nCrlf << nCrlf;
  }


bool Collection::allFieldsUsed() {
ClnIter iter(*this);
FldDsc* fd;

  for (fd = iter(); fd; fd = iter++) if (!fd->selected) return false;

  return true;
  }


String& Collection::argsEmpty() {
ClnIter iter(*this);
FldDsc* fd;
int     i;
String  argN;

  s.clear();

  for (i = 0, fd = iter(); fd; fd = iter++) if (fd->selected) {
    if (i) s += _T(" && ");

    argN = i;

    s += _T("arg") + argN; s += _T(".isEmpty()");  i++;
    }

  return s;
  }


int Collection::getArgDecls(VarDeclarations& decl) {
ClnIter iter(*this);
FldDsc* fd;
int     n;
String  s;

  for (n = 0, fd = iter(); fd; fd = iter++) if (fd->selected) {
    s = _T("arg"); s += n; s += _T(" = ") + fd->object;       decl.add(_T("String"), s);  n++;
    }

  return n;
  }


String& Collection::getArgs(int n) {
int i;

  s.clear();

  for (i = 0; i < n; i++) {
    if (i) s += _T(", ");
    s += _T("arg"); s += i;
    }

  return s;
  }


String& Collection::argsToRcd() {
ClnIter iter(*this);
FldDsc* fd;
int     i;

  s.clear();

  for (i = 0, fd = iter(); fd; fd = iter++) if (fd->selected) {
    if (i) s += _T("  ");

    s += _T("r.") + fd->name + _T(" = arg") + i + _T(";");   i++;
    }

  return s;
  }


void TableCode::createFindID() {
VarDeclarations decl;
String          s;
DescTable       dscTbl(tbl.name);
DTIter          iter(dscTbl);
FieldDesc*      fldDsc = iter();                          if (!fldDsc) return;
String          id     = fldDsc->name; fldDsc = iter++;   if (!fldDsc) return;
String          key    = fldDsc->name; fldDsc = iter++;   if (!fldDsc) return;
String          dsc    = fldDsc->name;

  notePad << nCrlf;

  notePad << tbl.keyType << _T(" ") << tbl.tblName << _T("::findID(String& key) {") << nCrlf;

  decl.clear();
  decl.add(tbl.iter, _T("iter(*this)"));
  s = tbl.rcd + _T("*");  decl.add(s, _T("rcd"));
  decl.output();   notePad << nCrlf;

  notePad << _T("  if (key.isEmpty()) return 0;") << nCrlf << nCrlf;

  notePad << _T("  for (rcd = iter(); rcd; rcd = iter++) if (rcd->") << key;
  notePad << _T(" == key) return rcd->") << id << _T(";") << nCrlf << nCrlf;

  notePad << _T("  return 0;") << nCrlf;
  notePad << _T("  }") << nCrlf << nCrlf;

  if (col.noChecked() > 1) createFindIDargs(id);
  }


void TableCode::createFindIDargs(String& idFld) {

  notePad << tbl.keyType << _T(" ") << tbl.tblName;
  notePad << _T("::findID(") << col.getArgs() << _T(") {") << nCrlf;
  notePad << tbl.rcd << _T("* rcd = find(") << col.getCallArgs() << _T(");") << nCrlf;
  notePad << _T("  return rcd ? rcd->") << idFld << _T(" : 0;") << nCrlf;
  notePad << _T("  }") << nCrlf << nCrlf;
  }


void TableCode::createFind() {
VarDeclarations decl;
String          s;
ClnIter         iter(col);
FldDsc*         dsc;
int             i;

  notePad << nCrlf;
  notePad << tbl.rcd <<  _T("* ") << tbl.tblName << _T("::find(") << col.getArgs();
  notePad << _T(") {") << nCrlf;

  decl.clear();
  decl.add(tbl.iter, _T("iter(*this)"));
  s = tbl.rcd + _T('*');
  decl.add(s, _T("rcd"));
  decl.output();   notePad << nCrlf;

  testArgsEmpty();   notePad << nCrlf;

  notePad << _T("  for (rcd = iter(); rcd; rcd = iter++)") << nCrlf;

  notePad << _T("    if (");

  for (dsc = iter(), i = 0; dsc; dsc = iter++) {

    if (dsc->selected) {
      if (i) notePad << _T(" && ");

      notePad <<  _T("rcd->") << dsc->name << _T(" == ") << dsc->object;   i++;
      }
    }
  notePad << _T(") return rcd;") << nCrlf << nCrlf;

  notePad << _T("  return 0;") << nCrlf;
  notePad << _T("  }") << nCrlf << nCrlf;
  }


void TableCode::testArgsEmpty() {
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

String& Collection::getArgs(bool doChar) {
int    n = fields.end();
int    i;
int    j;
String t;

  s.clear();

  for (i = 0, j = 0; i < n; i++) {
    FldDsc& fd = fields[i];

    if (fd.selected) {
      if (j) s += _T(", ");

      t = fd.typ != _T("String") ? fd.typ : doChar ? _T("TCchar*") : _T("String&");

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


int Collection::noChecked() {
ClnIter iter(*this);
FldDsc* dsc;
int     cnt;

  for (cnt = 0, dsc = iter(); dsc; dsc = iter++) if (dsc->selected) cnt++;

  return cnt;
  }


