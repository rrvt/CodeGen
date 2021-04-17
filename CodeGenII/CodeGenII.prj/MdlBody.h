// Module Body Creation


#pragma once
#include "Module.h"


class MdlBody {

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

  MdlBody(Module& mod) : module   (mod),
                         namePfx  (mod.namePfx),
                         tblName  (mod.tblName),
                         tblObj   (mod.tblObj),
                         rcdName  (mod.rcdName),
                         ptrName  (mod.ptrName),
                         iterName (mod.iterName),
                         fieldList(mod.fieldList) { }

  void create();

private:

  void load();
  void rcdLoad();
  void store();
  void addNewRcd();
  void addRef();
  void rcdStore();
  bool find();
  void display();
  void dspRcd();
  void setTabs();
  void tabOut();

  MdlBody() : module  (*(Module*)0),
                namePfx (*(String*)0),
                tblName (*(String*)0),
                tblObj  (*(String*)0),
                rcdName (*(String*)0),
                ptrName (*(String*)0),
                iterName(*(String*)0), fieldList(*(FieldList*)0) { }
  };


