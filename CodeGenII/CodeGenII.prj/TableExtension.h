// Table Extension Template


#pragma once
#include "DescTable.h"
#include "Expandable.h"
#include "TableNames.h"
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


class Collection;
typedef IterT<Collection, FldDsc> ClnIter;


class Collection {
String                s;
Expandable<FldDsc, 2> fields;

public:

int noStringsSel;

  Collection(DescTable& descTbl) : noStringsSel(0) {initialize(descTbl);}

  String& getArgs();            // Get as Arguments when args is true, otherwise as call
  String& getCallArgs();

private:

  void initialize(DescTable& descTbl);

  Collection();

  // returns either a pointer to data (or datum) at index i in array or zero
  FldDsc* datum(int i) {return 0 <= i && i < nData() ? &fields[i] : 0;}

  // returns number of data items in array
  int   nData()      {return fields.end();}

  friend typename ClnIter;
  };



class TableExtension {
DescTable  descTbl;
Collection col;
TableNames tbl;

public:

   TableExtension(TCchar* tblName) : descTbl(tblName), col(descTbl), tbl(tblName) { }
  ~TableExtension() { }

   bool operator() (TableDsc& tbl);

private:

  int  load(String& tableName) {return descTbl.load(maps, tableName);}
  void createTblExtHdr();
  void createTblExtCpp();
  void testArgsEmpty();

  TableExtension() : col(*(DescTable*) 0), tbl(0) { }
  };

