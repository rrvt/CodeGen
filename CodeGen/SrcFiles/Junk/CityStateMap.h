// CityState Map logic, Version 1.4.1
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct CityStateRecord : public MapRecord {
long   CityStateID;
String City;
String State;
String Zip;

  CityStateRecord() : CityStateID(0), City(), State(), Zip() {}
  CityStateRecord(const CityStateRecord& r) : MapRecord(r), CityStateID(r.CityStateID), City(r.City),
           State(r.State), Zip(r.Zip) {}
 ~CityStateRecord() {}

  CityStateRecord operator= (CityStateRecord& r) {
    copy(r, *this); CityStateID = r.CityStateID; City = r.City; State = r.State;
    Zip = r.Zip;
    }

  String getFldVal(int i);
  };


class CityStateTable;


class CityStateDB {
AceRecordSet rcdSet;
public:

  CityStateDB() : rcdSet() {}
 ~CityStateDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, CityStateTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(CityStateTable& myTable);

private:

  bool wrt(CityStateRecord& src);
  bool erase(long key);
  bool add(CityStateRecord& rcd);
  };


class CityStateTable : public MapTable {
public:

typedef map<const long, CityStateRecord> MyMap;
typedef MyMap::iterator  Iter;
typedef pair<Iter, bool> Rslt;

private:

static MyMap myMap;

Iter it;
long maxKey;
CityStateDB myDB;

public:

  CityStateTable() {initialize();}

  void initialize() {
    it = myMap.end(); maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("CityState"));
    }

  bool add(CityStateRecord& rcd);
  int  erase( const long key) {it = myMap.end(); return myMap.erase(key);}

  CityStateRecord* find(const long key) {it = myMap.find(key); return curRcd();}
  CityStateRecord* startLoop()  {it = myMap.begin();           return it != myMap.end() ? &it->second : 0;}
  CityStateRecord* nextRecord() {return it == myMap.end() ? 0 :     ++it != myMap.end() ? &it->second : 0;}
  CityStateRecord* startRLoop() {it = myMap.end(); return prevRecord();}
  CityStateRecord* prevRecord() {return it == myMap.begin() ? 0 : &(--it)->second;}
  CityStateRecord* curRcd()     {return it != myMap.end() ? &it->second : 0;}

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
  };

