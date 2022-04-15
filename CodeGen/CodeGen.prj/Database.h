// Database


#pragma once
#include "AccessDB.h"
#include "AccFldDsc.h"
#include "AccTblDsc.h"


class Database {
public:

  Database() { }
 ~Database() { }

  void load(TCchar* path);
  };


extern Database database;

