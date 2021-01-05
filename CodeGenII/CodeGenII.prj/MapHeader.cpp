// Map Header file Creation


#include "stdafx.h"
#include "MapHeader.h"
#include "CodeGenII.h"
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
  notePad << _T("#include \"MapTable.h\"") << nCrlf << nCrlf << nCrlf;

  createRecordClass();

  createMyDBclass();

  createMyTableClass();

  createMyIterClass();

  notePad << nCrlf;
  }



void MapHeader::createRecordClass() {
DTIter          iter(*descTbl);
FieldDesc*      fldDesc;
int             j;
VarDeclarations decl;

  notePad << _T("struct ") << tbl->rcd << _T(" : public MapRecord {") << nCrlf;

  for (fldDesc = iter(); fldDesc; fldDesc = iter++) {
    decl.add(getDbCppType(fldDesc->x), fldDesc->name);
    }

  decl.output();

  notePad << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("() : ");

  for (fldDesc = iter(), j = 0; fldDesc; fldDesc = iter++, j++) {
    int ty = fldDesc->x;
    notePad << fldDesc->name << _T("(");

    switch (ty) {
      case dbLong: notePad << _T("0"); break;
      }
    notePad << _T(")");

    if (iter.isLast()) notePad << _T(" {}") << nCrlf;
    else if (j < 4)    notePad << _T(", ");
    else              {notePad << _T(",") << nCrlf << _T("           "); j = -1;}
    }

   notePad << _T("  ") << tbl->rcd << _T("(const ") << tbl->rcd << _T("& r) : ");

   notePad << _T("MapRecord(r), ");

   for (fldDesc = iter(), j = 2; fldDesc; fldDesc = iter++, j++) {
     notePad << fldDesc->name << _T("(r.") << fldDesc->name << _T(")");

     if (iter.isLast()) notePad << _T(" {}") << nCrlf;
     else if (j < 2)    notePad << _T(", ");
     else              {notePad << _T(",") << nCrlf << _T("           "); j = -1;}
     }

  notePad << _T(" ~") << tbl->rcd << _T("() {}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T(" operator= (") << tbl->rcd << _T("& r) {") << nCrlf;
  notePad << _T("    copy(r, *this); ");

  for (fldDesc = iter(), j = 1; fldDesc; fldDesc = iter++, j++) {

    notePad << fldDesc->name << _T(" = r.") << fldDesc->name << _T(";");

    if (iter.isLast()) notePad << nCrlf << _T("    }") << nCrlf;
    else if (j < 2)    notePad << _T(" ");
    else              {notePad << nCrlf << _T("    "); j = -1;}
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
VarDeclarations decl;

  notePad << _T("class ") << tbl->cls << _T(" : public MapTable {") << nCrlf << nCrlf;

  notePad << _T("typedef map<const ") << tbl->keyType << _T(", ") << tbl->rcd << _T("> MyMap;") << nCrlf;
  notePad << nCrlf;

  decl.add(_T("static MyMap"), _T("myMap"));
  decl.add(tbl->keyType, _T("maxKey"));
  decl.add(tbl->myDB,    _T("myDB"));
  decl.output();   notePad << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->cls << _T("() {initialize();}") << nCrlf << nCrlf;

  notePad << _T("  void initialize() {") << nCrlf;
  notePad << _T("    maxKey = 0;   if (!myMap.empty()) myMap.clear();") << nCrlf;
  notePad << _T("    MapTable::initialize(_T(\"") << tbl->name << _T("\"));") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  bool add(") << tbl->rcd << _T("& rcd);") << nCrlf << nCrlf;

  notePad << _T("  int  curSize() {return (int) myMap.size();}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->keyType << _T(" nextKey() {return maxKey+1;}") << nCrlf << nCrlf;

  toTableComment(); notePad << nCrlf;

  notePad << _T("  bool toTable(AceRecordSet& records) {return myDB.toTable(records, *this);}");
  notePad << nCrlf << nCrlf;

  toDatabaseComment(); notePad << nCrlf;

  notePad << _T("  bool toDatabase() {return myDB.toDatabase(*this);}") << nCrlf << nCrlf;

  notePad << _T("  friend class ") << tbl->iter << _T(';') << nCrlf;

  notePad << _T("  };") << nCrlf << nCrlf << nCrlf;
  }


void MapHeader::createMyIterClass() {
VarDeclarations decl;
String prefix;

  notePad << _T("class ") << tbl->iter << _T(" {") << nCrlf << nCrlf;

  prefix = _T("typedef ") + tbl->cls + _T("::MyMap");  decl.add(prefix, _T("MyMap"));
  decl.add(_T("typedef MyMap::iterator"), _T("MyIter"));
  decl.output();   notePad << nCrlf;

  decl.clear();
  decl.add(_T("MyMap&"), _T("myMap"));
  decl.add(_T("MyIter"), _T("iter"));
  decl.output();   notePad << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  notePad << _T("typedef pair<MyIter, bool> Pair;") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->iter << _T("(") << tbl->cls;
  notePad << _T("& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("* operator() (bool fwd = true) {") << nCrlf;
  notePad << _T("    if (fwd) {iter = myMap.begin(); return iter == myMap.end() ? 0 : ");
  notePad << _T("&iter->second;}") << nCrlf;
  notePad << _T("    else     {iter = myMap.end();   return decr();}") << nCrlf;
  notePad << _T("    }") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("* operator++ (int)") << nCrlf;
  notePad << _T("                            {return iter == myMap.end() ? 0 : ");
  notePad << _T("++iter == myMap.end() ? 0 : &iter->second;}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("* operator-- (int) {return decr();}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("* find(const long key)") << nCrlf;
  notePad << _T("                               {iter = myMap.find(key);  ");
  notePad << _T("return iter == myMap.end() ? 0 : &iter->second;}") << nCrlf << nCrlf;

  notePad << _T("  void erase() {iter = myMap.erase(iter);}") << nCrlf << nCrlf;

  notePad << _T("  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}") << nCrlf << nCrlf;

  notePad << _T("  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}") << nCrlf;
  notePad << _T("  bool isBbegin() {return iter == myMap.begin();}") << nCrlf << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->rcd << _T("* decr() {return iter == myMap.begin() ? 0 : ");
  notePad << _T("&(--iter)->second;}") << nCrlf << nCrlf;

  notePad << _T("  ") << tbl->iter << _T("() : myMap(*(MyMap*) 0) { }                   ");
  notePad << _T("// Prevents uninitizlized iterator") << nCrlf;
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

