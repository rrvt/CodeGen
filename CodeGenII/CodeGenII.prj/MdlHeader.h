// Module Header Creation


#pragma once
#include "Module.h"


class MdlHeader {

Module&    module;
String&    namePfx;
String&    tblName;
String&    tblObj;
String&    rcdName;
String&    ptrName;
String&    iterName;

DAOtable*  daoTbl;
FieldList& fieldList;
FieldDsc*  primaryKey;             // Key in database record
String     indexName;
String     indexType;
int        noFields;


public:

  MdlHeader(Module& mod) : module   (mod),
                           namePfx  (mod.namePfx),
                           tblName  (mod.tblName),
                           tblObj   (mod.tblObj),
                           rcdName  (mod.rcdName),
                           ptrName  (mod.ptrName),
                           iterName (mod.iterName),
                           fieldList(mod.fieldList) { }

  void create();


private:

  void record();
  void constructor();
  void rcdComparison(TCchar* op);
  void binComparison(TCchar* op);
  void linComparison();

  void iterator();

  void table();

  MdlHeader() : module  (*(Module*)0),
                namePfx (*(String*)0),
                tblName (*(String*)0),
                tblObj  (*(String*)0),
                rcdName (*(String*)0),
                ptrName (*(String*)0),
                iterName(*(String*)0), fieldList(*(FieldList*)0) { }
  };

