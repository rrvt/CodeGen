// AssgnPref Map logic, Version 1.5.3.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct AssgnPrefRecord : public MapRecord {
long   AssgnPrefID;
String APKey;
String Txt;

  AssgnPrefRecord() : AssgnPrefID(0), APKey(), Txt() {}
  AssgnPrefRecord(const AssgnPrefRecord& r) : MapRecord(r), AssgnPrefID(r.AssgnPrefID),
           APKey(r.APKey), Txt(r.Txt) {}
 ~AssgnPrefRecord() {}

  AssgnPrefRecord operator= (AssgnPrefRecord& r) {
    copy(r, *this); AssgnPrefID = r.AssgnPrefID; APKey = r.APKey;
    Txt = r.Txt;
    }

  String getFldVal(int i);
  };


class AssgnPrefTable;


class AssgnPrefDB {
AceRecordSet rcdSet;
public:

  AssgnPrefDB() : rcdSet() {}
 ~AssgnPrefDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, AssgnPrefTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(AssgnPrefTable& myTable);

private:

  bool wrt(AssgnPrefRecord& src);
  bool erase(long key);
  };


class AssgnPrefTable : public MapTable {
public:

typedef map<const long, AssgnPrefRecord> MyMap;
typedef MyMap::iterator  Iter;
typedef pair<Iter, bool> Rslt;

private:

static MyMap myMap;

Iter it;
bool increment;
long maxKey;
AssgnPrefDB myDB;

public:

  AssgnPrefTable() {initialize();}

  void initialize() {
    it = myMap.end(); increment = true; maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("AssgnPref"));
    }

  bool add(AssgnPrefRecord& rcd);
  void erase() {it = myMap.erase(it); increment = false;}

  AssgnPrefRecord* find(const long key) {it = myMap.find(key); return curRcd();}
  AssgnPrefRecord* startLoop()  {it = myMap.begin();  return curRcd();}
  AssgnPrefRecord* nextRecord() {return it == myMap.end() ? 0 : increment ? bmp() : curRcd();}
  AssgnPrefRecord* curRcd()     {increment = true; return it != myMap.end() ? &it->second : 0;}

  AssgnPrefRecord* startRLoop() {it = myMap.end(); return prevRecord();}
  AssgnPrefRecord* prevRecord() {return it == myMap.begin() ? 0 : &(--it)->second;}

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

  AssgnPrefRecord* bmp() {return ++it != myMap.end() ? &it->second : 0;}
  };

