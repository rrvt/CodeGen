// AssgnPrefTable


#pragma once
#include "DBtables.h"
#include "DAOfields.h"
#include "ExpandableP.h"


class AssgnPrefRcd : public DBrcd {
public:
String apkey;
String txt;

  AssgnPrefRcd() : DBrcd() { }
 ~AssgnPrefRcd() { }

          void load(FieldsP fields);
          void store(FieldsP fields);

  virtual void display();

  // Needed for Insertion Sort of Primary Key
  bool operator== (AssgnPrefRcd& r) {return id == r.id;}
  bool operator>= (AssgnPrefRcd& r) {return id >= r.id;}

  // Needed for Binary Search of Primary Key
  bool operator== (long id) {return this->id == id;}
  bool operator<  (long id) {return this->id <  id;}
  bool operator>  (long id) {return this->id >  id;}

  // Needed for Linear Search with one or more arguments
  bool operator== (TCchar* apkey) {return this->apkey == apkey;}
  };


// Iterator Declaration, see IterT.h for details
class AssgnPrefTbl;
typedef IterT<AssgnPrefTbl, AssgnPrefRcd> PrfIter;

// Record Pointer Declaration, see ExpandableP.h for details
typedef RcdPtrT<AssgnPrefRcd> AssgnPrefRcdP;


class AssgnPrefTbl : public DBtable {

ExpandableP<AssgnPrefRcd, AssgnPrefRcdP, 2> data;

public:

  AssgnPrefTbl() : DBtable(_T("AssgnPref")) {dbTables = this;}
 ~AssgnPrefTbl() { }

   virtual bool operator== (TCchar* name) {return this->name == name;}

           void clear() {data.clear();}
           bool load(DAOtable* daoTable);  // load database table into memory, does not use addNewRcd.

  AssgnPrefRcd* add(AssgnPrefRcd& rcd);     // Add a new record to table and database
  AssgnPrefRcd* add(String apkey, String txt);   // Add a new record to table and database

           void store();

  AssgnPrefRcd* find(long id) {return data.bSearch(id);}
  AssgnPrefRcd* find(TCchar* apkey) {return data.find(apkey);}

   virtual void display();

   virtual void setTabs();
private:

// returns either a pointer to data (or datum) at index i in array or zero

  AssgnPrefRcd* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename PrfIter;
  };


  extern AssgnPrefTbl assgnPrefTbl;

