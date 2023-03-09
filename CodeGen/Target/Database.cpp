// Database


#include "stdafx.h"
#include "Database.h"


Database database;
AccessDB accessDB;
AdrTbl   adrTbl;
MbrTbl   mbrTbl;


void Database::load(TCchar* path) {
  accessDB.open(path);
  adrTbl.open(path);   adrTbl.load();
//  mbrTbl.load(path);
  }

