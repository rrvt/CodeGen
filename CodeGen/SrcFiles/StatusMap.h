// Status Map logic, Version 1.5.3.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct StatusRecord : public MapRecord {
long   StsID;
String Abbreviation;
String Description;

  StatusRecord() : StsID(0), Abbreviation(), Description() {}
  StatusRecord(const StatusRecord& r) : MapRecord(r), StsID(r.StsID),
           Abbreviation(r.Abbreviation), Description(r.Description) {}
 ~StatusRecord() {}

  StatusRecord operator= (StatusRecord& r) {
    copy(r, *this); StsID = r.StsID; Abbreviation = r.Abbreviation;
    Description = r.Description;
    }

  String getFldVal(int i);
  };


class StatusTable;


class StatusDB {
AceRecordSet rcdSet;
public:

  StatusDB() : rcdSet() {}
 ~StatusDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, StatusTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(StatusTable& myTable);

private:

  bool wrt(StatusRecord& src);
  bool erase(long key);
  };


class StatusTable : public MapTable {
public:

typedef map<const long, StatusRecord> MyMap;
typedef MyMap::iterator  Iter;
typedef pair<Iter, bool> Rslt;

private:

static MyMap myMap;

Iter it;
bool increment;
long maxKey;
StatusDB myDB;

public:

  StatusTable() {initialize();}

  void initialize() {
    it = myMap.end(); increment = true; maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("Status"));
    }

  bool add(StatusRecord& rcd);
  void erase() {it = myMap.erase(it); increment = false;}

  StatusRecord* find(const long key) {it = myMap.find(key); return curRcd();}
  StatusRecord* startLoop()  {it = myMap.begin();  return curRcd();}
  StatusRecord* nextRecord() {return it == myMap.end() ? 0 : increment ? bmp() : curRcd();}
  StatusRecord* curRcd()     {increment = true; return it != myMap.end() ? &it->second : 0;}

  StatusRecord* startRLoop() {it = myMap.end(); return prevRecord();}
  StatusRecord* prevRecord() {return it == myMap.begin() ? 0 : &(--it)->second;}

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

  StatusRecord* bmp() {return ++it != myMap.end() ? &it->second : 0;}
  };

