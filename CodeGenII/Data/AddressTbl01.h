// AddressTable


#pragma once
#include "DBtables.h"
#include "DAOfields.h"
#include "ExpandableP.h"


class AddressRcd : public DBrcd {
public:
String address1;
String address2;

  AddressRcd() : DBrcd() { }
 ~AddressRcd() { }

          void load(FieldsP fields);
          void store(FieldsP fields);

  virtual void display();

  // Needed for Insertion Sort of Primary Key
  bool operator== (AddressRcd& r) {return id == r.id;}
  bool operator>= (AddressRcd& r) {return id >= r.id;}

  // Needed for Binary Search of Primary Key
  bool operator== (long id) {return this->id == id;}
  bool operator<  (long id) {return this->id <  id;}
  bool operator>  (long id) {return this->id >  id;}

  // Needed for Linear Search with one or more arguments
  bool isInRcd(TCchar* address1, TCchar* address2)
                                        {return this->address1 == address1 && this->address2 == address2;}
  };


// Iterator Declaration, see IterT.h for details
class AddressTbl;
typedef IterT<AddressTbl, AddressRcd> AdrIter;

// Record Pointer Declaration, see ExpandableP.h for details
typedef RcdPtrT<AddressRcd> AddressRcdP;


class AddressTbl : public DBtable {

ExpandableP<AddressRcd, AddressRcdP, 2> data;

public:

  AddressTbl() : DBtable(_T("Address")) {dbTables = this;}
 ~AddressTbl() { }

  virtual bool operator== (TCchar* name) {return this->name == name;}

          void clear() {data.clear();}
          bool load(DAOtable* daoTable);  // load database table into memory, does not use addNewRcd.

   AddressRcd* add(AddressRcd& rcd);     // Add a new record to table and database
   AddressRcd* add(String address1, String address2);   // Add a new record to table and database

          void store();

   AddressRcd* find(long id) {return data.bSearch(id);}
   AddressRcd* find(TCchar* address1, TCchar* address2);

  virtual void display();

  virtual void setTabs();
private:

// returns either a pointer to data (or datum) at index i in array or zero

  AddressRcd* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename AdrIter;
  };


  extern AddressTbl addressTbl;

