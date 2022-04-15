// Names used in the Module (class)

#pragma once
#include "Fields.h"


struct ModNames {
String    abbr;
String    accTbl;
String    tblCls;
String    tblObj;
String    rcdCls;
String    rcdPCls;
String    tblIter;
String    setCls;
String    setObj;
String    setIterCls;

String    dbIndex;
String    index;
FieldType indexType;

int       noFields;

  bool set(TCchar* table);
  };


extern ModNames modNames;
