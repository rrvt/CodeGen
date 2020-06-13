// Table Extension Template


#pragma once
#include "DescTable.h"
#include "Expandable.h"
#include "Utilities.h"


class FldDsc {
public:
String typ;
String name;
String object;
bool   selected;

  FldDsc() : selected(false) { }
  FldDsc(FldDsc& nd) {copy(nd);}
 ~FldDsc() { }

  FldDsc& operator= (FldDsc& nd) {copy(nd); return *this;}

  void set(String& name) {this->name = name; object = objName(name);}

private:
  void copy(FldDsc& nd) {name = nd.name; object = nd.object; typ = nd.typ; selected = nd.selected;}
  };


class Collection {
String                s;
public:

String                name;
String                tblName;
String                tableName;
String                recordName;         // DB Field Name
String                rcdName;            // object Name
int                   noStringsSel;
Expandable<FldDsc, 2> fields;

  Collection() : noStringsSel(0) { }
  void initialize(DescTable& descTbl);
  String& getArgs();            // Get as Arguments when args is true, otherwise as call
  String& getCallArgs();
  };



class TableExtension {
DescTable  descTbl;
Collection col;

public:

   TableExtension() { }
  ~TableExtension() { }

   bool operator() (TableDsc& tbl);

private:

  int  load(String& tableName) {return descTbl.load(maps, tableName);}
  void createTblExtHdr();
  void createTblExtCpp();
  void testArgsEmpty();
  };
