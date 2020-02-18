// Entity Map logic, Version 1.5.3.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct EntityRecord : public MapRecord {
long   EntityID;
String FirstName;
String MiddleInitial;
String LastName;
String Suffix;
long   AddrID;
long   CityStID;
bool   AddrIsPO;
String LocationZip;
String eMail;
String Phone1;
String Phone2;

  EntityRecord() : EntityID(0), FirstName(), MiddleInitial(), LastName(), Suffix(),
           AddrID(0), CityStID(0), AddrIsPO(), LocationZip(), eMail(),
           Phone1(), Phone2() {}
  EntityRecord(const EntityRecord& r) : MapRecord(r), EntityID(r.EntityID),
           FirstName(r.FirstName), MiddleInitial(r.MiddleInitial), LastName(r.LastName),
           Suffix(r.Suffix), AddrID(r.AddrID), CityStID(r.CityStID),
           AddrIsPO(r.AddrIsPO), LocationZip(r.LocationZip), eMail(r.eMail),
           Phone1(r.Phone1), Phone2(r.Phone2) {}
 ~EntityRecord() {}

  EntityRecord operator= (EntityRecord& r) {
    copy(r, *this); EntityID = r.EntityID; FirstName = r.FirstName;
    MiddleInitial = r.MiddleInitial; LastName = r.LastName; Suffix = r.Suffix;
    AddrID = r.AddrID; CityStID = r.CityStID; AddrIsPO = r.AddrIsPO;
    LocationZip = r.LocationZip; eMail = r.eMail; Phone1 = r.Phone1;
    Phone2 = r.Phone2;
    }

  String getFldVal(int i);
  };


class EntityTable;


class EntityDB {
AceRecordSet rcdSet;
public:

  EntityDB() : rcdSet() {}
 ~EntityDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, EntityTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(EntityTable& myTable);

private:

  bool wrt(EntityRecord& src);
  bool erase(long key);
  };


class EntityTable : public MapTable {
public:

typedef map<const long, EntityRecord> MyMap;
typedef MyMap::iterator  Iter;
typedef pair<Iter, bool> Rslt;

private:

static MyMap myMap;

Iter it;
bool increment;
long maxKey;
EntityDB myDB;

public:

  EntityTable() {initialize();}

  void initialize() {
    it = myMap.end(); increment = true; maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("Entity"));
    }

  bool add(EntityRecord& rcd);
  void erase() {it = myMap.erase(it); increment = false;}

  EntityRecord* find(const long key) {it = myMap.find(key); return curRcd();}
  EntityRecord* startLoop()  {it = myMap.begin();  return curRcd();}
  EntityRecord* nextRecord() {return it == myMap.end() ? 0 : increment ? bmp() : curRcd();}
  EntityRecord* curRcd()     {increment = true; return it != myMap.end() ? &it->second : 0;}

  EntityRecord* startRLoop() {it = myMap.end(); return prevRecord();}
  EntityRecord* prevRecord() {return it == myMap.begin() ? 0 : &(--it)->second;}

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

  EntityRecord* bmp() {return ++it != myMap.end() ? &it->second : 0;}
  };

