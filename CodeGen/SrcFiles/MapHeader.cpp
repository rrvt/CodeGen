// Map Header file Creation


#include "stdafx.h"
#include "MapHeader.h"
#include "CodeGen.h"
#include "MapCode.h"
#include "NotePad.h"
#include "Utilities.h"


void MapHeader::createFile(Table& table) {
//VarDeclarations decl;

  tbl = &table;

  createCopyright(tbl->name);

  notePad << _T("#pragma once") << nCrlf;
  notePad << _T("#include \"AceDao.h\"") << nCrlf;
  notePad << _T("#include \"MapTable.h\"") << nCrlf << nCrlf << nCrlf;

  createRecordClass();

  createMyDBclass();

  createMyTableClass();

  notePad << nCrlf;
  }



void MapHeader::createRecordClass() {
FieldDesc*      fldDesc;
int             j;
VarDeclarations decl;

  notePad << _T("struct ") << tbl->rcd << _T(" : public MapRecord {") << nCrlf;

  for (fldDesc = descTbl->startLoop(); fldDesc; fldDesc = descTbl->nextDesc()) {
    decl.add(getDbCppType(fldDesc->x), fldDesc->name);
    }

  decl.output();

  notePad << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("() : ");

  for (fldDesc = descTbl->startLoop(), j = 0; fldDesc; fldDesc = descTbl->nextDesc(), j++) {
    int ty = fldDesc->x;
    notePad << fldDesc->name << _T("(");

    switch (ty) {
      case dbLong: notePad << _T("0"); break;
      }
    notePad << _T(")");

    if (descTbl->last())  notePad << _T(" {}") << nCrlf;
    else if (j < 4)      notePad << _T(", ");
    else                {notePad << _T(",") << nCrlf << _T("           "); j = -1;}
    }

   notePad << _T("  ") << tbl->rcd << _T("(const ") << tbl->rcd << _T("& r) : ");

   notePad << _T("MapRecord(r), ");

   for (fldDesc = descTbl->startLoop(), j = 2; fldDesc; fldDesc = descTbl->nextDesc(), j++) {
     notePad << fldDesc->name << _T("(r.") << fldDesc->name << _T(")");

     if (descTbl->last()) notePad << _T(" {}") << nCrlf;
     else if (j < 2)      notePad << _T(", ");
     else                {notePad << _T(",") << nCrlf << _T("           "); j = -1;}
     }

  notePad << _T(" ~") << tbl->rcd << _T("() {}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T(" operator= (") << tbl->rcd << _T("& r) {") << nCrlf;
  notePad << _T("    copy(r, *this); ");

  for (fldDesc = descTbl->startLoop(), j = 1; fldDesc; fldDesc = descTbl->nextDesc(), j++) {

    notePad << fldDesc->name << _T(" = r.") << fldDesc->name << _T(";");

    if (descTbl->last()) notePad << nCrlf << _T("    }") << nCrlf;
    else if (j < 2)      notePad << _T(" ");
    else                {notePad << nCrlf << _T("    "); j = -1;}
    }

  notePad << nCrlf;

  notePad << _T("  String getFldVal(int i);") << nCrlf ;

  notePad << _T("  };") << nCrlf << nCrlf << nCrlf;
  }


void MapHeader::createMyDBclass() {
//FieldDesc*      fldDesc;
//VarDeclarations decl;

  notePad << _T("class ") << tbl->cls << _T(";") << nCrlf << nCrlf << nCrlf;

  notePad << _T("class ") << tbl->myDB << _T(" {") << nCrlf;
  notePad << _T("AceRecordSet rcdSet;") << nCrlf;
  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->myDB << _T("() : rcdSet() {}") << nCrlf;
  notePad << _T(" ~") << tbl->myDB << _T("() {}") << nCrlf << nCrlf;

  toTableComment(); notePad << nCrlf;

  notePad << _T("  bool toTable(AceRecordSet& records, ") << tbl->cls << _T("& myTable);");
  notePad << nCrlf << nCrlf;

 toDatabaseComment(); notePad << nCrlf;

  notePad << _T("  bool toDatabase(") << tbl->cls << _T("& myTable);") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  bool wrt(") << tbl->rcd << _T("& src);") << nCrlf;
  notePad << _T("  bool erase(") << tbl->keyType << _T(" key);") << nCrlf;
//  notePad << _T("  bool add(") << tbl->rcd << _T("& rcd);") << nCrlf;
  notePad << _T("  };") << nCrlf << nCrlf << nCrlf;
  }


void MapHeader::createMyTableClass() {

  notePad << _T("class ") << tbl->cls << _T(" : public MapTable {") << nCrlf;
  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("typedef map<const ") << tbl->keyType << _T(", ") << tbl->rcd << _T("> MyMap;") << nCrlf;
  notePad << _T("typedef MyMap::iterator  Iter;") << nCrlf;
  notePad << _T("typedef pair<Iter, bool> Rslt;") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;
  notePad << _T("static MyMap myMap;") << nCrlf << nCrlf;
  notePad << _T("Iter it;") << nCrlf;
  notePad << _T("bool increment;") << nCrlf;
  notePad << tbl->keyType << _T(" maxKey;") << nCrlf;
  notePad << tbl->myDB    << _T(" myDB;") << nCrlf << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->cls << _T("() {initialize();}") << nCrlf << nCrlf;

  notePad << _T("  void initialize() {") << nCrlf;
  notePad << _T("    it = myMap.end(); increment = true; maxKey = 0;");
  notePad << _T("   if (!myMap.empty()) myMap.clear();") << nCrlf;
  notePad << _T("    MapTable::initialize(_T(\"") << tbl->name << _T("\"));") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;


  notePad << _T("  bool add(") << tbl->rcd << _T("& rcd);") << nCrlf;
#if 0
  notePad << _T("  bool update(const ") << tbl->keyType << _T(" oldKey, ");
  notePad << tbl->rcd << _T("& rcd);") << nCrlf;
#endif

  notePad << _T("  void erase() {it = myMap.erase(it); increment = false;}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("* find(const ") << tbl->keyType;
  notePad << _T(" key) {it = myMap.find(key); return curRcd();}") << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("* startLoop()  {it = myMap.begin();  return curRcd();}") << nCrlf;
//  notePad << _T("return it != myMap.end() ? &it->second : 0;}") << nCrlf;
  notePad << _T("  ") << tbl->rcd << _T("* nextRecord() {return it == myMap.end() ? 0 :");
  notePad << _T(" increment ? bmp() : curRcd();}") << nCrlf;

  notePad << _T("  ") << tbl->rcd;
  notePad << _T("* curRcd()     {increment = true; return it != myMap.end() ? &it->second : 0;}");
  notePad << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("* startRLoop() {it = myMap.end(); return prevRecord();}");
  notePad << nCrlf;
  notePad << _T("  ") << tbl->rcd;
  notePad << _T("* prevRecord() {return it == myMap.begin() ? 0 : &(--it)->second;}") << nCrlf << nCrlf;

  notePad << _T("  int  curSize() {return (int) myMap.size();}") << nCrlf;
  notePad << _T("  ") << tbl->keyType << _T(" curKey() {return it != myMap.end() ?  ");
  notePad << _T("it->first  : -1;}") << nCrlf;
  notePad << _T("  ") << tbl->keyType << _T(" nextKey() {return maxKey+1;}") << nCrlf << nCrlf;

  toTableComment(); notePad << nCrlf;

  notePad << _T("  bool toTable(AceRecordSet& records) {return myDB.toTable(records, *this);}");
  notePad << nCrlf << nCrlf;

  toDatabaseComment(); notePad << nCrlf;

  notePad << _T("  bool toDatabase() {return myDB.toDatabase(*this);}") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd;
  notePad << _T("* bmp() {return ++it != myMap.end() ? &it->second : 0;}") << nCrlf;
  notePad << _T("  };") << nCrlf;
  }


void MapHeader::toTableComment() {
  notePad << _T("  // toTable copies all records from a database table into a map container in ");
  notePad << _T("memory.  It is") << nCrlf;
  notePad << _T("  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which ");
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



void createCopyright(TCchar* name) {
  notePad << _T("// ") << name << _T(" Map logic, Version ") << theApp.version << nCrlf;
  notePad << _T("// Copyright Bob -- K6RWY, 2019.  ");
  notePad << _T("All rights reserved.") << nCrlf << nCrlf;
  }

