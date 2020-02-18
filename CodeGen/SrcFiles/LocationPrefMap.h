// LocationPref Map logic, Version 1.5.3.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct LocationPrefRecord : public MapRecord {
long   LocationPrefID;
String Key;
String Txt;

  LocationPrefRecord() : LocationPrefID(0), Key(), Txt() {}
  LocationPrefRecord(const LocationPrefRecord& r) : MapRecord(r), LocationPrefID(r.LocationPrefID),
           Key(r.Key), Txt(r.Txt) {}
 ~LocationPrefRecord() {}

  LocationPrefRecord operator= (LocationPrefRecord& r) {
    copy(r, *this); LocationPrefID = r.LocationPrefID; Key = r.Key;
    Txt = r.Txt;
    }

  String getFldVal(int i);
  };


class LocationPrefTable;


class LocationPrefDB {
AceRecordSet rcdSet;
public:

  LocationPrefDB() : rcdSet() {}
 ~LocationPrefDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, LocationPrefTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(LocationPrefTable& myTable);

private:

  bool wrt(LocationPrefRecord& src);
  bool erase(long key);
  };


class LocationPrefTable : public MapTable {
public:

typedef map<const long, LocationPrefRecord> MyMap;
typedef MyMap::iterator  Iter;
typedef pair<Iter, bool> Rslt;

private:

static MyMap myMap;

Iter it;
bool increment;
long maxKey;
LocationPrefDB myDB;

public:

  LocationPrefTable() {initialize();}

  void initialize() {
    it = myMap.end(); increment = true; maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("LocationPref"));
    }

  bool add(LocationPrefRecord& rcd);
  void erase() {it = myMap.erase(it); increment = false;}

  LocationPrefRecord* find(const long key) {it = myMap.find(key); return curRcd();}
  LocationPrefRecord* startLoop()  {it = myMap.begin();  return curRcd();}
  LocationPrefRecord* nextRecord() {return it == myMap.end() ? 0 : increment ? bmp() : curRcd();}
  LocationPrefRecord* curRcd()     {increment = true; return it != myMap.end() ? &it->second : 0;}

  LocationPrefRecord* startRLoop() {it = myMap.end(); return prevRecord();}
  LocationPrefRecord* prevRecord() {return it == myMap.begin() ? 0 : &(--it)->second;}

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

  LocationPrefRecord* bmp() {return ++it != myMap.end() ? &it->second : 0;}
  };

