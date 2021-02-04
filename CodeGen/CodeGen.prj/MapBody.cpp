// Create Map Body code (i.e. .cpp file)


#include "stdafx.h"
#include "MapBody.h"
#include "CodeGen.h"
#include "MapCode.h"
#include "MapHeader.h"
#include "NotePad.h"
#include "TableNames.h"
#include "Utilities.h"
#include "VarDecl.h"


static String fldToString(FieldDesc* fldDesc);


void MapBody::createFile(TableNames& table) {
String fldName;
String converter;

  tbl = &table;

  createCopyright(tbl->name, theApp.version);

  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"") << tbl->name << _T("Map.h\"") << nCrlf;
  notePad << _T("#include \"MapData.h\"") << nCrlf;
  notePad << _T("#include \"NotePad.h\"") << nCrlf << nCrlf << nCrlf;

  notePad << tbl->mapName << _T("::MyMap ") << tbl->mapName << _T("::myMap;") << nCrlf;

  createAdd();
  createToTable();
  createToDatabase();
  createErase();
  createDBwrt();
  createGetFldVal();
  createCopy();
  }


void MapBody::createAdd() {
String s;
bool   longKey = tbl->keyType == _T("long");

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->mapName << _T("::add(") << tbl->rcd << _T("& rcd) {") << nCrlf;
  notePad << tbl->iter << _T("::Pair pair;") << nCrlf << nCrlf;

  s = _T("rcd.") + tbl->keyName;

  notePad << _T("  if (!") << s << _T(") ") << s << _T(" = ");
  if (!longKey) notePad << _T("maxKey + 1;");
  else          notePad << _T("nextKey();");
  notePad << nCrlf << nCrlf;

  notePad << _T("  pair = myMap.insert(make_pair(rcd.") << tbl->keyName << _T(", rcd));") << nCrlf;
  notePad << nCrlf;

  if (!longKey) {
    notePad << _T("  if (pair.second && rcd.") << tbl->keyName << _T(" > maxKey) ");
    notePad << _T("maxKey = rcd.") << tbl->keyName;
    }
  else          notePad << _T("  if (pair.second) setKey(rcd.") << tbl->keyName << _T(")");

  notePad << _T(";") << nCrlf << nCrlf;

  notePad << _T("  return pair.second;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void MapBody::createUpdate() {

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->mapName << _T("::update(const ") << tbl->keyType;
  notePad << _T(" oldKey, ") << tbl->rcd << _T("& rcd) {") << nCrlf;

  notePad << _T("Iter x = prev(it);") << nCrlf << nCrlf;

  notePad << _T("  if (!erase(oldKey)) return false;   rcd.newRcd = false;   ");
  notePad << _T("if (!add(rcd)) return false;") << nCrlf << nCrlf;

  notePad << _T("  it = x; return true;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void MapBody::createToTable() {
VarDeclarations decl;

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->myDB << _T("::toTable(AceRecordSet& records, ");
  notePad << tbl->mapName << _T("& myTable) {") << nCrlf;

  decl.add(_T("AceFields"),    _T("fields(records)"));
  decl.add(_T("AFIter"),       _T("iter(fields)"));
  decl.add(_T("AceFieldDsc*"), _T("dsc"));
  decl.add(_T("int"),          _T("i"));
  decl.add(_T("variant_t"),    _T("v"));
  decl.add(tbl->rcd,           _T("rcd"));

  decl.output();   notePad << nCrlf;

  notePad << _T("  for (dsc = iter(), i = 0; dsc; ");
  notePad << _T("dsc = iter++, i++) {") << nCrlf;

  notePad << _T("    v = dsc->value;") << nCrlf;

  createSwitch(_T("    "), _T("v"), _T("false"), ReadTyp);

  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  return myTable.add(rcd);") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void MapBody::createToDatabase() {
VarDeclarations decl;
String          s;

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->myDB << _T("::toDatabase(");
  notePad << tbl->mapName << _T("& myTable) {") << nCrlf;

  decl.add(tbl->iter, _T("iter(myTable)"));
  s = tbl->rcd + _T("*"); decl.add(s, _T("r"));
  decl.output();   notePad << nCrlf;

  notePad << _T("  if (!maps.openRcdSet(_T(\"") << tbl->name;
  notePad << _T("\"), DaoDenyWrite, rcdSet)) return false;") << nCrlf << nCrlf;

  notePad << _T("  for (r = iter(); r; r = iter++) {") << nCrlf << nCrlf;

  notePad << _T("    if (r->toDelete()) {remove(r->") << tbl->keyName << _T("); ");
  notePad << _T("iter.remove(); continue;}") << nCrlf << nCrlf;

  notePad << _T("    if (r->isDirty()) {wrt(*r); r->clearMarks();}") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  rcdSet.close();   return true;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void MapBody::createErase() {

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->myDB << _T("::remove(") << tbl->keyType << _T(" key) ");
  notePad << _T("{return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();}") << nCrlf;
  }


void MapBody::createDBwrt() {
VarDeclarations decl;

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->myDB << _T("::wrt(") << tbl->rcd << _T("& rcd) {") << nCrlf;
  decl.add(_T("AceFields"),   _T("fields(rcdSet)"));
  decl.add(_T("AFIter"),      _T("iter(fields)"));
  decl.add(_T("AceFieldDsc*"), _T("dsc"));
  decl.add(_T("int"),          _T("i"));
  decl.add(_T("variant_t"),    _T("v"));

  decl.output();   notePad << nCrlf;

  notePad << _T("  if (rcdSet.findRecord(rcd.") << tbl->keyName << _T(")) rcdSet.edit();")   << nCrlf;
  notePad << _T("  else rcdSet.addNew();") << nCrlf << nCrlf;

  notePad << _T("  for (dsc = iter(), i = 0; dsc; ");
  notePad << _T("dsc = iter++, i++) {") << nCrlf;

  createSwitch(_T("    "), _T("v"), _T("false"), WrtTyp);   notePad << nCrlf;

  notePad << _T("    dsc->write(v);") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  return rcdSet.update() != 0;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


// Create Switch with all fields in table

void MapBody::createSwitch(TCchar* tab, TCchar* var, TCchar* retVal, SwitchType typ) {
VarDeclarations decl;

String     tabPlus2 = String(tab) + _T("  ");
DTIter     iter(*descTbl);
FieldDesc* fldDesc;
int        i;
String     fldName;
String     s;
String     t;

  notePad << tab << _T("switch (i) {") << nCrlf;

  decl.clear();

  for (fldDesc = iter(), i = 0; fldDesc; fldDesc = iter++, i++) {
    fldName = fldDesc->name;    String n;  n.format(_T("%2i"), i);

    s = tabPlus2 + _T("case ") + n + _T(": ");

    if (!i && typ == WrtTyp) {
      s += _T("rcd.") + tbl->keyName;
      t  = _T("= dsc->value; continue");
      }

    else if (typ == ReadTyp) {
      s += _T("rcd.") + fldName;
      t  = _T("= "); t += var; t += _T("; break") ;
      }

    else {
      s += var;
      t  = _T("= rcd.") + fldName + _T("; break");
      }

    decl.add(s, t);
    }

  decl.output();

  notePad << tabPlus2 << _T("default: return ") << retVal << _T(";") << nCrlf;

  notePad << tabPlus2 << _T("}") << nCrlf;
  }


void MapBody::createGetFldVal() {
int        i;
String     s;
DTIter     iter(*descTbl);
FieldDesc* fldDesc;

  notePad << nCrlf << nCrlf;

  notePad << _T("String ") << tbl->name << _T("Record::getFldVal(int i) {") << nCrlf;
  notePad << _T("  switch (i) {") << nCrlf;

  for (fldDesc = iter(), i = 0; fldDesc; fldDesc = iter++, i++) {
    s.format(_T("    case %2i :"), i);
    notePad << s << fldToString(fldDesc) << nCrlf;
    }

  notePad << _T("    }") << nCrlf << nCrlf;
  notePad << _T("  return _T(\"\");") << nCrlf;
  notePad << _T("  }") << nCrlf << nCrlf;
  }


String fldToString(FieldDesc* fldDesc) {
String s;

  switch (fldDesc->x) {
    case dbBoolean        :
    case dbByte           :
    case dbLong           :
    case dbInteger        : s = _T("{String s; s.format(_T(\"%i\"), ");
                            s += fldDesc->name + _T("); return s;}");  return s;
    case dbCurrency       : break; return _T("Currency");
    case dbSingle         : break; return _T("float");
    case dbDouble         : break; return _T("double");
    case dbDate           : break; return _T("Date");
    case dbBinary         : break; return _T("dbBinary");
    case dbLongBinary     : break; return _T("dbLongBinary");
    case dbText           :
    case dbMemo           : s = _T("return ") + fldDesc->name + _T(";");  return s;
    case dbGUID           : break; return _T("dbGUID");
    case dbBigInt         : break; return _T("dbBigInt");
    case dbVarBinary      : break; return _T("dbVarBinary");
    case dbChar           : break; return _T("char");
    case dbNumeric        : break; return _T("dbNumeric");
    case dbDecimal        : break; return _T("dbDecimal");
    case dbFloat          : break; return _T("float");
    case dbTime           : break; return _T("dbTime");
    case dbTimeStamp      : break; return _T("dbTimeStamp");
    case dbAttachment     : break; return _T("dbAttachment");
    case dbComplexByte    : break; return _T("dbComplexByte");
    case dbComplexInteger : break; return _T("dbComplexInteger");
    case dbComplexLong    : break; return _T("dbComplexLong");
    case dbComplexSingle  : break; return _T("dbComplexSingle");
    case dbComplexDouble  : break; return _T("dbComplexDouble");
    case dbComplexGUID    : break; return _T("dbComplexGUID");
    case dbComplexDecimal : break; return _T("dbComplexDecimal");
    case dbComplexText    : break; return _T("dbComplexText");
    default               : break;
    }
  String t = _T("<"); t += fldDesc->x; t += _T(">");  return t;
  }


void MapBody::createCopy() {
DTIter          iter(*descTbl);
FieldDesc*      fldDesc;
String          indent = _T(" ");
String          s;
String          t;

  notePad << nCrlf;

  notePad << _T("void ") << tbl->rcd << _T("::copy(const ") <<  tbl->rcd << _T("& r) {") << nCrlf;

  s = _T(" MapRecord::copy(r);");

  for (fldDesc = iter(); fldDesc; fldDesc = iter++) {
    t       = fldDesc->name + _T(" = r.") + fldDesc->name + _T(";");

    if (s.length() + t.length() + 4 < 107) {s += _T(' ') + t;}
    else {notePad << indent << s << nCrlf;  s  = _T(' ') + t;}
    }

  if (!s.isEmpty()) notePad << indent << s << nCrlf;
  notePad << _T("  }") << nCrlf;
  }

