// Defines all Database Tables and a list of them


#pragma once
#include "DBtablesB.h"


class DBtables : public DBtablesB {

public:

  DBtables() : DBtablesB() { }
 ~DBtables() { }

  DBtables& operator+= (DBtable* tbl) {data += tbl; return *this;}
  DBtables& operator=  (DBtable* tbl) {data  = tbl; return *this;}
  };

extern DBtables dbTables;

