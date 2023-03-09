// Database


#pragma once
#include "AccessDB.h"
#include "MbrTbl.h"
#include "StsTbl.h"


class Database {
public:

  Database() { }
 ~Database() { }

  bool load(TCchar* path);
  };


extern Database database;

