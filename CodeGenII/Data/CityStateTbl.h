// CityStateTable


#pragma once
#include "DBtables.h"
#include "DAOfields.h"
#include "ExpandableP.h"


class CityStateRcd : public DBrcd {
public:
String city;
String state;
String zip;

  CityStateRcd() : DBrcd() { }
 ~CityStateRcd() { }

          void load(FieldsP fields);
          void store(FieldsP fields);

  virtual void display();

  // Needed for Insertion Sort of Primary Key
  bool operator== (CityStateRcd& r) {return id == r.id;}
  bool operator>= (CityStateRcd& r) {return id >= r.id;}

  // Needed for Binary Search of Primary Key
  bool operator== (long id) {return this->id == id;}
  bool operator<  (long id) {return this->id <  id;}
  bool operator>  (long id) {return this->id >  id;}

  // Needed for Linear Search with one or more arguments
  bool isInRcd(TCchar* city, TCchar* zip) {return this->city == city && this->zip == zip;}
  };


// Iterator Declaration, see IterT.h for details
class CityStateTbl;
typedef IterT<CityStateTbl, CityStateRcd> CtyIter;

// Record Pointer Declaration, see ExpandableP.h for details
typedef RcdPtrT<CityStateRcd> CityStateRcdP;


class CityStateTbl : public DBtable {

ExpandableP<CityStateRcd, CityStateRcdP, 2> data;

public:

  CityStateTbl() : DBtable(_T("CityState")) {dbTables = this;}
 ~CityStateTbl() { }

   virtual bool operator== (TCchar* name) {return this->name == name;}

           void clear() {data.clear();}
           bool load(DAOtable* daoTable);  // load database table into memory, does not use addNewRcd.

  CityStateRcd* add(CityStateRcd& rcd);     // Add a new record to table and database
           void store();

  CityStateRcd* find(long id) {return data.bSearch(id);}
  CityStateRcd* find(TCchar* city, TCchar* zip);

   virtual void display();

   virtual void setTabs();
private:

// returns either a pointer to data (or datum) at index i in array or zero

  CityStateRcd* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename CtyIter;
  };


  extern CityStateTbl cityStateTbl;

