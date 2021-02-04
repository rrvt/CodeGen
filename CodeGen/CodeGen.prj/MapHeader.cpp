// Map Header file Creation


#include "stdafx.h"
#include "MapHeader.h"
#include "CodeGen.h"
#include "MapCode.h"
#include "NotePad.h"
#include "TableNames.h"
#include "Utilities.h"
#include "VarDecl.h"

void MapHeader::createFile(TableNames& table) {

  tbl = &table;

  createCopyright(tbl->name, theApp.version);

  notePad << _T("#pragma once") << nCrlf;
  notePad << _T("#include \"AceDao.h\"") << nCrlf;
  notePad << _T("#include \"MapBase.h\"") << nCrlf << nCrlf << nCrlf;

  createRecordClass();   notePad << nCrlf << nCrlf;

  createDBclass();       notePad << nCrlf << nCrlf;

  createMapClass();      notePad << nCrlf;
  }



void MapHeader::createRecordClass() {
DTIter          iter(*descTbl);
FieldDesc*      fldDesc;
VarDeclarations decl;

  notePad << _T("struct ") << tbl->rcd << _T(" : public MapRecord {") << nCrlf;

  for (fldDesc = iter(); fldDesc; fldDesc = iter++) {decl.add(getDbCppType(fldDesc->x), fldDesc->name);}

  decl.output();   notePad << nCrlf;

  createCnstr();

   notePad << _T("  ") << tbl->rcd << _T("(const ") << tbl->rcd << _T("& r) {copy(r);}") << nCrlf;

  notePad << _T(" ~") << tbl->rcd << _T("() {}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("& operator= (const ") << tbl->rcd << _T("& r) {");
  notePad << _T("copy(r); return *this;}") << nCrlf;

  notePad << nCrlf;

  notePad << _T("  String getFldVal(int i);") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  void copy(const ") <<  tbl->rcd << _T("& r);") << nCrlf;

  notePad << _T("  };") << nCrlf;
  }


void MapHeader::createCnstr() {
String     space = _T("                                        ");
DTIter     iter(*descTbl);
FieldDesc* fldDesc;
int        n;
String     indent = _T("  ");
String     s;
String     t;

  s = tbl->rcd + _T("() :");    n = s.length() + 3;

  for (fldDesc = iter(); fldDesc; fldDesc = iter++) {
    int typ = fldDesc->x;
    t = fldDesc->name + _T("(");
    if (typ == dbLong) t += _T('0');
    t += _T(')');

    if (iter.isLast()) t += _T(" {}");
    else               t += _T(",");

    if (s.length() + t.length() + n < 107) {     s += _T(' ') + t;}
    else {notePad << indent << s << nCrlf;   s = t;   indent = space.substr(0, n);}
    }

  if (!s.isEmpty()) notePad << indent << s << nCrlf;
  }


void MapHeader::createDBclass() {

  notePad << _T("class ") << tbl->mapName << _T(";") << nCrlf << nCrlf << nCrlf;

  notePad << _T("class ") << tbl->myDB << _T(" {") << nCrlf;
  notePad << _T("AceRecordSet rcdSet;") << nCrlf;
  notePad << _T("protected:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->myDB << _T("() : rcdSet() {}") << nCrlf;
  notePad << _T(" ~") << tbl->myDB << _T("() {}") << nCrlf << nCrlf;

  toTableComment(); notePad << nCrlf;

  notePad << _T("  bool toTable(AceRecordSet& records, ") << tbl->mapName << _T("& myTable);");
  notePad << nCrlf << nCrlf;

 toDatabaseComment(); notePad << nCrlf;

  notePad << _T("  bool toDatabase(") << tbl->mapName << _T("& myTable);") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  bool wrt(") << tbl->rcd << _T("& src);") << nCrlf;
  notePad << _T("  bool remove(") << tbl->keyType << _T(" key);") << nCrlf << nCrlf;

  notePad << _T("  friend class ") << tbl->mapName << _T(";") << nCrlf;

  notePad << _T("  };") << nCrlf;
  }


void MapHeader::createMapClass() {
VarDeclarations decl;
bool            longKey = tbl->keyType == _T("long");

  notePad << _T("class ") << tbl->mapName << _T(" : public MapBase {") << nCrlf << nCrlf;

  notePad << _T("typedef map<const ") << tbl->keyType << _T(", ") << tbl->rcd << _T("> MyMap;") << nCrlf;
  notePad << nCrlf;

  decl.add(_T("static MyMap"), _T("myMap"));
  if (!longKey) decl.add(tbl->keyType, _T("maxKey"));
  decl.add(tbl->myDB,    _T("myDB"));
  decl.output();   notePad << nCrlf;

  notePad << _T("protected:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->mapName << _T("() {initialize();}") << nCrlf << nCrlf;

  notePad << _T("  void initialize() {") << nCrlf;

  if (!longKey) notePad << _T("    maxKey = 0;   ");
  else          notePad << _T("    ");
  notePad << _T("if (!myMap.empty()) myMap.clear();") << nCrlf;
  notePad << _T("    MapBase::initialize(_T(\"") << tbl->name << _T("\"));") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  bool add(") << tbl->rcd << _T("& rcd);") << nCrlf << nCrlf;

  notePad << _T("  int  curSize() {return (int) myMap.size();}") << nCrlf << nCrlf;

  if (!longKey)
            notePad << _T("  ") << tbl->keyType << _T(" nextKey() {return maxKey+1;}") << nCrlf << nCrlf;

  toTableComment(); notePad << nCrlf;

  notePad << _T("  bool toTable(AceRecordSet& records) {return myDB.toTable(records, *this);}");
  notePad << nCrlf << nCrlf;

  toDatabaseComment(); notePad << nCrlf;

  notePad << _T("  bool toDatabase() {return myDB.toDatabase(*this);}") << nCrlf << nCrlf;

  notePad << _T("  friend class ") << tbl->iter << _T(';') << nCrlf;
  notePad << _T("  friend class ") << tbl->myDB << _T(';') << nCrlf;

  notePad << _T("  };") << nCrlf;
  }



void MapHeader::toTableComment() {
  notePad << _T("  // toTable copies all records from a database table into a map container in ");
  notePad << _T("memory.  It is") << nCrlf;
  notePad << _T("  // called from MapsT<MapData>::loadRecords(TblDsc* tableDsc) which ");
  notePad << _T("is in turn") << nCrlf;
  notePad << _T("  // called from MapsT<MapData>::loadAllMaps(String& path).");
  notePad << _T("  Essentially there is a table") << nCrlf;
  notePad << _T("  // with all the database tables and all the tables are copied into a ");
  notePad << _T("corresponding map table.") << nCrlf;
  notePad << _T("  // The tables are implemented as trees for fast access and other properties ");
  notePad << _T("(see std::map)") << nCrlf;
  }


void MapHeader::toDatabaseComment() {
  notePad << _T("  // After all changes have been made in the map, call toDatabase to copy the ");
  notePad << _T("changes") << nCrlf;
  notePad << _T("  // back to the database.") << nCrlf;
  }

