// Database


#include "stdafx.h"
#include "Database.h"


Database  database;
AccessDB  accessDB;
AccFldDsc accFldDsc;
AccTblDsc accTblDsc;


void Database::load(TCchar* path) {
  accessDB.open(path);
  }

