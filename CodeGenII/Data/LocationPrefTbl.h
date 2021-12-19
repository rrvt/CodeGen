// LocationPrefTable


#pragma once
#include "DBtables.h"
#include "DAOfields.h"
#include "ExpandableP.h"


class LocationPrefRcd : public DBrcd {
public:
String key;
String txt;

  LocationPrefRcd() : DBrcd() { }
 ~LocationPrefRcd() { }

          void load(FieldsP fields);
          void store(FieldsP fields);

  virtual void display();

  // Needed for Insertion Sort of Primary Key
  bool operator== (LocationPrefRcd& r) {return id == r.id;}
  bool operator>= (LocationPrefRcd& r) {return id >= r.id;}

  // Needed for Binary Search of Primary Key
  bool operator== (long id) {return this->id == id;}
  bool operator<  (long id) {return this->id <  id;}
  bool operator>  (long id) {return this->id >  id;}

  // Needed for Linear Search with one or more arguments
  bool operator== (TCchar* key) {return this->key == key;}
  };


// Iterator Declaration, see IterT.h for details
class LocationPrefTbl;
typedef IterT<LocationPrefTbl, LocationPrefRcd> LocIter;

// Record Pointer Declaration, see ExpandableP.h for details
typedef RcdPtrT<LocationPrefRcd> LocationPrefRcdP;


class LocationPrefTbl : public DBtable {

ExpandableP<LocationPrefRcd, LocationPrefRcdP, 2> data;

public:

  LocationPrefTbl() : DBtable(_T("LocationPref")) {dbTables = this;}
 ~LocationPrefTbl() { }

      virtual bool operator== (TCchar* name) {return this->name == name;}

              void clear() {data.clear();}
              bool load(DAOtable* daoTable);  // load database table into memory, does not use addNewRcd.

  LocationPrefRcd* add(LocationPrefRcd& rcd);     // Add a new record to table and database
  LocationPrefRcd* add(String key, String txt);   // Add a new record to table and database

              void store();

  LocationPrefRcd* find(long id) {return data.bSearch(id);}
  LocationPrefRcd* find(TCchar* key) {return data.find(key);}

      virtual void display();

      virtual void setTabs();
private:

// returns either a pointer to data (or datum) at index i in array or zero

  LocationPrefRcd* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename LocIter;
  };


  extern LocationPrefTbl locationPrefTbl;

