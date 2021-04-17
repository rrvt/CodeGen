// Create header and body for DBtable Module that is to be included with Database Table Modules


#pragma once
#include "Expandable.h"
#include "IterT.h"


class Table {
public:

String name;
bool   selected;

  Table() : selected(false) { }
 ~Table() { }

  bool operator>= (Table& tbl) {return name >= tbl.name;}
  bool operator== (Table& tbl) {return name == tbl.name;}

  bool operator== (TCchar* name) {return this->name == name;}
  bool operator<  (TCchar* name) {return this->name <  name;}
  bool operator>  (TCchar* name) {return this->name >  name;}
  };


typedef Expandable<Table, 2> TableData;

class DBtbl;
typedef IterT<DBtbl, Table> DBtblIter;


class DBtbl {

TableData data;

public:

  DBtbl() { }
 ~DBtbl() { }

  void loadTableNames();

  Table* find(TCchar* name) {return data.bSearch(name);
  }

  void hdrCreate();
  void bodyCreate();

private:

  bool selectTables();
  void addDAOinclude(Table* tbl, bool& done);
  void objects();

  // returns either a pointer to data (or datum) at index i in array or zero

  Table* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}       // or data[i].p

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename DBtblIter;
  };


extern DBtbl dbTbl;
