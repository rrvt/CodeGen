// Person Map logic, Version 1.5.4.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct PersonRecord : public MapRecord {
long   ID;
String FirstName;
String LastName;
bool   Author;

  PersonRecord() : ID(0), FirstName(), LastName(), Author() {}
  PersonRecord(const PersonRecord& r) : MapRecord(r), ID(r.ID),
           FirstName(r.FirstName), LastName(r.LastName), Author(r.Author) {}
 ~PersonRecord() {}

  PersonRecord operator= (PersonRecord& r) {
    copy(r, *this); ID = r.ID; FirstName = r.FirstName;
    LastName = r.LastName; Author = r.Author;
    }

  String getFldVal(int i);
  };


class PersonTable;


class PersonDB {
AceRecordSet rcdSet;
public:

  PersonDB() : rcdSet() {}
 ~PersonDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, PersonTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(PersonTable& myTable);

private:

  bool wrt(PersonRecord& src);
  bool erase(long key);
  };


class PersonTable : public MapTable {
public:

typedef map<const long, PersonRecord> MyMap;
typedef MyMap::iterator  Iter;
typedef pair<Iter, bool> Rslt;

private:

static MyMap myMap;

Iter it;
bool increment;
long maxKey;
PersonDB myDB;

public:

  PersonTable() {initialize();}

  void initialize() {
    it = myMap.end(); increment = true; maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("Person"));
    }

  bool add(PersonRecord& rcd);
  void erase() {it = myMap.erase(it); increment = false;}

  PersonRecord* find(const long key) {it = myMap.find(key); return curRcd();}
  PersonRecord* startLoop()  {it = myMap.begin();  return curRcd();}
  PersonRecord* nextRecord() {return it == myMap.end() ? 0 : increment ? bmp() : curRcd();}
  PersonRecord* curRcd()     {increment = true; return it != myMap.end() ? &it->second : 0;}

  PersonRecord* startRLoop() {it = myMap.end(); return prevRecord();}
  PersonRecord* prevRecord() {return it == myMap.begin() ? 0 : &(--it)->second;}

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

  PersonRecord* bmp() {return ++it != myMap.end() ? &it->second : 0;}
  };

