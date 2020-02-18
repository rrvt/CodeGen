// Address Map logic, Version 1.5.3.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct AddressRecord : public MapRecord {
long   AddressID;
String Address1;
String Address2;

  AddressRecord() : AddressID(0), Address1(), Address2() {}
  AddressRecord(const AddressRecord& r) : MapRecord(r), AddressID(r.AddressID),
           Address1(r.Address1), Address2(r.Address2) {}
 ~AddressRecord() {}

  AddressRecord operator= (AddressRecord& r) {
    copy(r, *this); AddressID = r.AddressID; Address1 = r.Address1;
    Address2 = r.Address2;
    }

  String getFldVal(int i);
  };


class AddressTable;


class AddressDB {
AceRecordSet rcdSet;
public:

  AddressDB() : rcdSet() {}
 ~AddressDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, AddressTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(AddressTable& myTable);

private:

  bool wrt(AddressRecord& src);
  bool erase(long key);
  };


class AddressTable : public MapTable {
public:

typedef map<const long, AddressRecord> MyMap;
typedef MyMap::iterator  Iter;
typedef pair<Iter, bool> Rslt;

private:

static MyMap myMap;

Iter it;
bool increment;
long maxKey;
AddressDB myDB;

public:

  AddressTable() {initialize();}

  void initialize() {
    it = myMap.end(); increment = true; maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("Address"));
    }

  bool add(AddressRecord& rcd);
  void erase() {it = myMap.erase(it); increment = false;}

  AddressRecord* find(const long key) {it = myMap.find(key); return curRcd();}
  AddressRecord* startLoop()  {it = myMap.begin();  return curRcd();}
  AddressRecord* nextRecord() {return it == myMap.end() ? 0 : increment ? bmp() : curRcd();}
  AddressRecord* curRcd()     {increment = true; return it != myMap.end() ? &it->second : 0;}

  AddressRecord* startRLoop() {it = myMap.end(); return prevRecord();}
  AddressRecord* prevRecord() {return it == myMap.begin() ? 0 : &(--it)->second;}

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

  AddressRecord* bmp() {return ++it != myMap.end() ? &it->second : 0;}
  };

