// Create Module


#pragma once
#include "DAOAccess.h"
#include "FieldList.h"


enum {PageWidth = 106};


class Module {
public:

String    namePfx;
String    tblName;
String    tblAbbr;
String    tblObj;
String    rcdName;
String    ptrName;
String    iterName;

DAOtable* daoTbl;
FieldList fieldList;
FieldDsc* primaryKey;             // Key in database record
String    indexName;
String    indexType;
int       noFields;

  Module(TCchar* name);
 ~Module() { }

  bool   getSearchFields();

  String getArgList(int& n);
  String getArgsComp();
  String getArgs();

private:

  Module() { }
  };

