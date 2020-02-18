// Table Extension Template


#include "stdafx.h"
#include "MapCode.h"
#include "codeGen.h"
#include "NotePad.h"
#include "Utilities.h"


class Name {
public:
String field;
String object;

  Name() { }
  void set(String& name) {field = name; object = objName(name);}
  };


class Collection {
String              s;
public:

String              name;
String              tblName;
String              tableName;
String              recordName;         // DB Field Name
String              rcdName;            // object Name
Expandable<Name, 4> names;

  Collection(DescTable& descTbl);
  String& getAll(bool args);            // Get as Arguments when args is true, otherwise as call
  };




void MapCode::createTableExtensions() {
TableDsc* tbl;

  for (tbl = tableDscrs.startLoop(); tbl; tbl = tableDscrs.nextEntry())
    if (tbl->selected) {

      String s = tbl->name + _T("Tbl");

      load(tbl->name);
      Collection collection(descTbl);

      notePad.close();   createTblExtHdr(collection); invalidateView();
      doc()->saveFile(_T("Header File"), s, _T(".h"), HeaderExt);

      notePad.close();   createTblExtCpp(collection); invalidateView();
      doc()->saveFile(_T("Body File"), s, _T(".cpp"), CppExt);
      }
  }


Collection::Collection(DescTable& descTbl) {
FieldDesc* fldDesc;
int        i;
int        n;

  name       = descTbl.getName();
  tblName    = name + _T("Tbl");
  tableName  = name + _T("Table");
  recordName = name + _T("Record");
  rcdName    = objName(recordName);

  for (fldDesc = descTbl.startLoop(), n = i = 0; fldDesc; fldDesc = descTbl.nextDesc(), i++) {
    if (!i) continue;

    if (fldDesc->x == dbText || fldDesc->x == dbMemo) {

      names[names.end()].set(fldDesc->name);

      n++;    if (n >= 3) break;
      }
    }
  }



void MapCode::createTblExtHdr(Collection& c) {
String s;

  notePad << _T("// ") << c.name << _T(" Table Extension Template") << nCrlf << nCrlf << nCrlf;

  notePad << _T("#pragma once") << nCrlf;

  notePad << _T("#include \"") << c.name << _T("Map.h\"") << nCrlf << nCrlf << nCrlf;

  notePad << _T("class ") << c.tblName << _T(" : public ") << c.tableName << _T(" {") << nCrlf << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("  ") << c.tblName << _T("() : ") << c.tableName << _T("() { }") << nCrlf << nCrlf;

  notePad << _T("  ") << c.recordName << _T("* get(") << c.getAll(true) << _T(");") << nCrlf << nCrlf;

  notePad << _T("  ") << c.recordName << _T("* find(const long key) {return ");
  notePad << c.tableName << _T("::find(key);}") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  ") << c.recordName << _T("* find(") << c.getAll(true) << _T(");") << nCrlf;

  notePad << _T("  };") << nCrlf;
  }


void MapCode::createTblExtCpp(Collection& c) {
int    i;
int    lng;
String s;

  notePad << _T("// ") << c.name << _T(" Table Extension Template") << nCrlf << nCrlf << nCrlf;

  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"") << c.tblName << _T(".h\"") << nCrlf;
  notePad << _T("#include \"Utilities.h\"") << nCrlf << nCrlf << nCrlf;

  notePad << c.recordName << _T("* ") << c.tblName << _T("::get(") << c.getAll(true) << _T(") {") << nCrlf;
  notePad << c.recordName << _T("* r = find(") << c.getAll(false) << _T(");   if (r) return r;") << nCrlf;
  notePad << c.recordName << _T("  rcd;") << nCrlf << nCrlf;

  for (i = 0; i < c.names.end(); i++) {
    Name& name = c.names[i];

    if (i) notePad << _T("  ");

    notePad << _T("  rcd.") << name.field << _T(" = ") << name.object << _T(";");
    }

  notePad << _T("    rcd.mark();  ") << c.tableName << _T("::add(rcd);") << nCrlf << nCrlf;

  // toDatabase();   return find(addr1, addr2);

  notePad << _T("  toDatabase();   return find(") << c.getAll(false) << _T(");") << nCrlf;

  notePad << _T("  }") << nCrlf << nCrlf << nCrlf;

  notePad << c.recordName <<  _T("* ") << c.tblName << _T("::find(") << c.getAll(true);
  notePad << _T(") {") << nCrlf;
  notePad << c.recordName << _T("* rcd;") << nCrlf << nCrlf;

  notePad << _T("  if (isEmpty(");
  for (i = 0; i < c.names.end(); i++) {
    Name& name = c.names[i];
    if (i) notePad << _T(" ");
    notePad << _T("&") << name.object << _T(",");
    }
  notePad << _T(" 0)) return 0;") << nCrlf << nCrlf;

  s = _T("  for (rcd = startLoop(); rcd; rcd = nextRecord())");   notePad << s;
  lng = s.length();

  s = _T("if (");
  for (i = 0; i < c.names.end(); i++) {
    Name name = c.names[i];

    if (i) s += _T(" && ");

    s += _T("rcd->") + name.field + _T(" == ") + name.object;
    }
  s += _T(") return rcd;");

  lng += s.length();

  if (lng < 104)                                notePad << _T(" ") << s << nCrlf;
  else {notePad << nSetTab(105 - s.length());   notePad << nCrlf << nTab << s << nCrlf;}

  notePad << _T("  return 0;") << nCrlf;
  notePad << _T("  }") << nCrlf << nCrlf;
  }



// Get as Arguments when args is true, otherwise as call

String& Collection::getAll(bool args) {
int i;

  s.clear();

  for (i = 0; i < names.end(); i++) {
    if (i) s += _T(", ");

    if (args) s += _T("String& ");

    s += names[i].object;
    }

  return s;
  }

