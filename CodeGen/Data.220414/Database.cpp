// Database


#include "stdafx.h"
#include "Database.h"


Database database;
AccessDB accessDB;
MbrTbl   mbrTbl;
StsTbl   stsTbl;


bool Database::load(TCchar* path) {
  if (!accessDB.open(path)) return false;
  if (!mbrTbl.load(path))   return false;
  if (!stsTbl.load(path))   return false;

  return true;
  }

