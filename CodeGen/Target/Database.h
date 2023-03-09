// Database


#pragma once
#include "AccessDB.h"
#include "AdrTbl.h"
#include "MbrTbl.h"


class Database {
public:

  Database() { }
 ~Database() { }

  void load(TCchar* path);
  };


extern Database database;

