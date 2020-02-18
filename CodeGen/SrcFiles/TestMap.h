// Test Map Template


#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct Record : public MapRecord {
long   key;
String fld1;
String fld2;

  Record() : key(0) {}
  Record(const Record& r) : key(r.key), fld1(r.fld1), fld2(r.fld2) {}

 ~Record() {fld1.clear(); fld2.clear();}

  Record& operator= (Record& r) {key = r.key; fld1 = r.fld1; fld2 = r.fld2; return *this;}
  };


class MyTable;


class MyDB {
AceRecordSet rcdSet;
public:

  MyDB() : rcdSet() {}
 ~MyDB() {}

  // insertDBrecordsIntoMap copies all records into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is inturn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map.

  bool toTable(AceRecordSet& records, MyTable& myTable);  // Used by MapsT to initialize map

  // After all changes have been made in the map, call updateDatabase to copy the changes
  // back to the database.

  bool toDatabase(MyTable& myTable);                            // Flush changed records to database

private:

  bool wrt(Record& src);
  bool erase(long  key);
  bool add(Record& rcd);
  };



class MyTable : public MapTable {
public:

typedef map<const long, Record> MyMap;
typedef MyMap::iterator         Iter;
typedef pair<Iter, bool>        Rslt;

private:

static MyMap myMap;
Iter         it;
long         maxKey;
MyDB         myDB;

public:

  MyTable() {initialize();}

  void initialize() {
    it = myMap.end(); maxKey = LONG_MIN;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("MyTable"));
    }

  bool    add(   const Record& rcd);
//  bool    update(const long oldKey, Record& rcd);
  int     erase( const long key) {it = myMap.end(); return myMap.erase(key);}

  Record* find(const long key) {it = myMap.find(key); return curRcd();}

  Record* startLoop()  {it = myMap.begin();         return it != myMap.end()   ? &it->second : 0;}

  Record* nextRecord() {return it == myMap.end()   ? 0 : ++it != myMap.end()   ? &it->second : 0;}

  Record* startRLoop() {it = myMap.end(); return prevRecord();}

  Record* prevRecord() {return it == myMap.begin() ? 0 : &(--it)->second;}

  Record* curRcd() {return it != myMap.end() ? &it->second : 0;}
  long    curKey() {return it != myMap.end() ?  it->first  : -1;}
  int     curSize() {return (int) myMap.size();}
  long    nextKey() {return maxKey+1;}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is inturn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding tabless.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records) {return myDB.toTable(records, *this);}

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase() {return myDB.toDatabase(*this);}
  };

