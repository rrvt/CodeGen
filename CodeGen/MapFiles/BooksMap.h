// Books Map logic, Version 1.5.4.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct BooksRecord : public MapRecord {
long   ID;
String Title;
long   AuthorID;
long   ProtagID;

  BooksRecord() : ID(0), Title(), AuthorID(0), ProtagID(0) {}
  BooksRecord(const BooksRecord& r) : MapRecord(r), ID(r.ID),
           Title(r.Title), AuthorID(r.AuthorID), ProtagID(r.ProtagID) {}
 ~BooksRecord() {}

  BooksRecord operator= (BooksRecord& r) {
    copy(r, *this); ID = r.ID; Title = r.Title;
    AuthorID = r.AuthorID; ProtagID = r.ProtagID;
    }

  String getFldVal(int i);
  };


class BooksTable;


class BooksDB {
AceRecordSet rcdSet;
public:

  BooksDB() : rcdSet() {}
 ~BooksDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, BooksTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(BooksTable& myTable);

private:

  bool wrt(BooksRecord& src);
  bool erase(long key);
  };


class BooksTable : public MapTable {
public:

typedef map<const long, BooksRecord> MyMap;
typedef MyMap::iterator  Iter;
typedef pair<Iter, bool> Rslt;

private:

static MyMap myMap;

Iter it;
bool increment;
long maxKey;
BooksDB myDB;

public:

  BooksTable() {initialize();}

  void initialize() {
    it = myMap.end(); increment = true; maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("Books"));
    }

  bool add(BooksRecord& rcd);
  void erase() {it = myMap.erase(it); increment = false;}

  BooksRecord* find(const long key) {it = myMap.find(key); return curRcd();}
  BooksRecord* startLoop()  {it = myMap.begin();  return curRcd();}
  BooksRecord* nextRecord() {return it == myMap.end() ? 0 : increment ? bmp() : curRcd();}
  BooksRecord* curRcd()     {increment = true; return it != myMap.end() ? &it->second : 0;}

  BooksRecord* startRLoop() {it = myMap.end(); return prevRecord();}
  BooksRecord* prevRecord() {return it == myMap.begin() ? 0 : &(--it)->second;}

  int  curSize() {return (int) myMap.size();}
  long curKey() {return it != myMap.end() ?  it->first  : -1;}
  long nextKey() {return maxKey+1;}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records) {return myDB.toTable(records, *this);}

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase() {return myDB.toDatabase(*this);}

private:

  BooksRecord* bmp() {return ++it != myMap.end() ? &it->second : 0;}
  };

