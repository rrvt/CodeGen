// Create Map Body code (i.e. .cpp file)


#include "stdafx.h"
#include "MapBody.h"
#include "MapCode.h"
#include "MapHeader.h"
#include "NotePad.h"
#include "Utilities.h"


static String fldToString(FieldDesc* fldDesc);


void MapBody::createFile(Table& table) {
String fldName;
String converter;

  tbl = &table;

  createCopyright(tbl->name);

  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"MapData.h\"") << nCrlf;
  notePad << _T("#include \"NotePad.h\"") << nCrlf << nCrlf << nCrlf;

  notePad << tbl->cls << _T("::MyMap ") << tbl->cls << _T("::myMap;") << nCrlf;
//  notePad << tbl->cls << _T("        ") << objName(tbl->cls) << _T(";") << nCrlf;


  createAdd();
//  createUpdate();
  createToTable();
  createToDatabase();
  createErase();
  createDBwrt();
//  createDBadd();
  createGetFldVal();
  }


void MapBody::createAdd() {
String s;

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->cls << _T("::add(") << tbl->rcd << _T("& rcd) {") << nCrlf;
  notePad << _T("Rslt rslt;") << nCrlf << nCrlf;

  s = _T("rcd.") + tbl->keyName;

  notePad << _T("  if (!") << s << _T(") ") << s << _T(" = maxKey + 1;") << nCrlf << nCrlf;

  notePad << _T("  rslt = myMap.insert(make_pair(rcd.") << tbl->keyName << _T(", rcd));") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  it = rslt.second ? rslt.first : myMap.end();") << nCrlf << nCrlf;
  notePad << _T("  if (rslt.second && rcd.") << tbl->keyName << _T(" > maxKey) ");
  notePad << _T("maxKey = rcd.") << tbl->keyName << _T(";") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  return rslt.second;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void MapBody::createUpdate() {

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->cls << _T("::update(const ") << tbl->keyType;
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
  notePad << tbl->cls << _T("& myTable) {") << nCrlf;

  decl.add(_T("AceFields"),   _T("fields(records)"));
  decl.add(_T("AceFieldDsc"), _T("fld"));
  decl.add(_T("bool"),        _T("rslt"));
  decl.add(_T("int"),         _T("i"));
  decl.add(_T("variant_t"),   _T("v"));
  decl.add(tbl->rcd,          _T("rcd"));

  decl.output();   notePad << nCrlf;

  notePad << _T("  for (rslt = fields.startLoop(fld), i = 0; rslt; ");
  notePad << _T("rslt = fields.nextField(fld), i++) {") << nCrlf;

  notePad << _T("    v = fld.value;") << nCrlf;

  createSwitch(_T("    "), _T("v"), _T("false"), ReadTyp);

  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  return myTable.add(rcd);") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }




void MapBody::createToDatabase() {
VarDeclarations decl;
String          s;

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->myDB << _T("::toDatabase(") << tbl->cls << _T("& myTable) {") << nCrlf;

  s = tbl->rcd + _T("*"); decl.add(s, _T("r")); decl.output();   notePad << nCrlf;

  notePad << _T("  if (!maps.openRcdSet(_T(\"") << tbl->name;
  notePad << _T("\"), DaoDenyWrite, rcdSet)) return false;") << nCrlf << nCrlf;

  notePad << _T("  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {") << nCrlf << nCrlf;

  notePad << _T("    if (r->toDelete()) {erase(r->") << tbl->keyName << _T("); ");
  notePad << _T("myTable.erase(); continue;}") << nCrlf << nCrlf;

  notePad << _T("    if (r->isDirty()) {wrt(*r); r->clearMarks();}") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  rcdSet.close();   return true;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void MapBody::createErase() {

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->myDB << _T("::erase(") << tbl->keyType << _T(" key) {") << nCrlf;
  notePad << _T("  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }





void MapBody::createDBwrt() {
VarDeclarations decl;

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->myDB << _T("::wrt(") << tbl->rcd << _T("& rcd) {") << nCrlf;
  decl.add(_T("AceFields"), _T("fields(rcdSet)"));
  decl.add(_T("AceFieldDsc"), _T("fld"));
  decl.add(_T("int"),         _T("i"));
  decl.add(_T("variant_t"),   _T("v"));
  decl.add(_T("bool"),        _T("rslt"));

  decl.output();   notePad << nCrlf;

  notePad << _T("  if (rcdSet.findRecord(rcd.") << tbl->keyName << _T(")) rcdSet.edit();")   << nCrlf;
  notePad << _T("  else rcdSet.addNew();") << nCrlf << nCrlf;

  notePad << _T("  for (rslt = fields.startLoop(fld), i = 0; rslt; ");
  notePad << _T("rslt = fields.nextField(fld), i++) {") << nCrlf;

  createSwitch(_T("    "), _T("v"), _T("false"), WrtTyp);   notePad << nCrlf;

  notePad << _T("    fld.write(v);") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  return rcdSet.update() != 0;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }



#if 0
void MapBody::createDBadd() {
VarDeclarations decl;

  notePad << nCrlf << nCrlf;

  notePad << _T("bool ") << tbl->myDB << _T("::add(") << tbl->rcd << _T("& rcd) {") << nCrlf;
  decl.add(_T("AceFieldDsc"), _T("fld"));
  decl.add(_T("int"),         _T("i"));
  decl.add(_T("variant_t"),   _T("v"));
  decl.add(_T("bool"),        _T("rslt"));

  decl.output();   notePad << nCrlf;

  notePad << _T("  rcdSet.addNew();") << nCrlf;
  notePad << _T("  AceFields fields(rcdSet);") << nCrlf << nCrlf;

  notePad << _T("  for (rslt = fields.startLoop(fld), i = 0; rslt; ");
  notePad << _T("rslt = fields.nextField(fld), i++) {") << nCrlf << nCrlf;

  createSwitch(_T("    "), _T("v"), _T("false"), NewRcdTyp);   notePad << nCrlf;

  notePad << _T("    fld.write(v);") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  return rcdSet.update() != 0;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }
#endif


// Create Switch with all fields in table

void MapBody::createSwitch(TCchar* tab, TCchar* var, TCchar* retVal, SwitchType typ) {
String     tabPlus2 = String(tab) + _T("  ");
FieldDesc* fldDesc;
int        i;
String     fldName;

  notePad << tab << _T("switch (i) {") << nCrlf;

  for (fldDesc = descTbl->startLoop(), i = 0; fldDesc; fldDesc = descTbl->nextDesc(), i++) {
    fldName = fldDesc->name;

    notePad << tabPlus2 << _T("case ");

    if (i < 10) notePad << _T(" ");      notePad << i << _T(" : ");
    if (i == 0 && typ == WrtTyp)
             {notePad << _T("rcd.") << tbl->keyName << _T(" = fld.value; continue;") << nCrlf; continue;}

    switch (typ) {
      case ReadTyp  : notePad << _T("rcd.") << fldName;  addPadding(descTbl->padding());
                      notePad << _T(" = ") << var << _T(";");
                      notePad << _T(" break;") << nCrlf;
                      break;

      case WrtTyp   : notePad << var << _T(" = ") << _T("rcd.") << fldName << _T("; break;") << nCrlf;
                      break;
      }
    }

  notePad << tabPlus2 << _T("default : return ") << retVal << _T(";") << nCrlf;
  notePad << tabPlus2 << _T("}") << nCrlf;
  }



void MapBody::createGetFldVal() {
int        i;
String     s;
FieldDesc* fldDesc;

  notePad << nCrlf << nCrlf;

  notePad << _T("String ") << tbl->name << _T("Record::getFldVal(int i) {") << nCrlf;
  notePad << _T("  switch (i) {") << nCrlf;

  for (fldDesc = descTbl->startLoop(), i = 0; fldDesc; fldDesc = descTbl->nextDesc(), i++) {
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

