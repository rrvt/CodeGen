// StatusTable


#pragma once
#include "DBtables.h"
#include "DAOfields.h"
#include "ExpandableP.h"


class StatusRcd : public DBrcd {
public:
String abbreviation;
String description;

  StatusRcd() : DBrcd() { }
 ~StatusRcd() { }

          void load(FieldsP fields);
          void store(FieldsP fields);

  virtual void display();

  // Needed for Insertion Sort of Primary Key
  bool operator== (StatusRcd& r) {return id == r.id;}
  bool operator>= (StatusRcd& r) {return id >= r.id;}

  // Needed for Binary Search of Primary Key
  bool operator== (long id) {return this->id == id;}
  bool operator<  (long id) {return this->id <  id;}
  bool operator>  (long id) {return this->id >  id;}

  // Needed for Linear Search with one or more arguments
  bool operator== (TCchar* abbreviation) {return this->abbreviation == abbreviation;}
  };


// Iterator Declaration, see IterT.h for details
class StatusTbl;
typedef IterT<StatusTbl, StatusRcd> StsIter;

// Record Pointer Declaration, see ExpandableP.h for details
typedef RcdPtrT<StatusRcd> StatusRcdP;


class StatusTbl : public DBtable {

ExpandableP<StatusRcd, StatusRcdP, 2> data;

public:

  StatusTbl() : DBtable(_T("Status")) {dbTables = this;}
 ~StatusTbl() { }

  virtual bool operator== (TCchar* name) {return this->name == name;}

          void clear() {data.clear();}
          bool load(DAOtable* daoTable);  // load database table into memory, does not use addNewRcd.

    StatusRcd* add(StatusRcd& rcd);     // Add a new record to table and database
    StatusRcd* add(String abbreviation, String description);   // Add a new record to table and database

          void store();

    StatusRcd* find(long id) {return data.bSearch(id);}
    StatusRcd* find(TCchar* abbreviation) {return data.find(abbreviation);}

  virtual void display();

  virtual void setTabs();
private:

// returns either a pointer to data (or datum) at index i in array or zero

  StatusRcd* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename StsIter;
  };


  extern StatusTbl statusTbl;

