// Table Extension Template


#pragma once
#include "DescTable.h"
#include "Expandable.h"
#include "TableNames.h"
#include "Utilities.h"


class VarDeclarations;


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

  String& getArgs(bool doChar = false);         // Get as Arguments when args is true, otherwise as call
  String& getCallArgs();

  bool    allFieldsUsed();
  String& argsEmpty();
  int     getArgDecls(VarDeclarations& decl);
  String& getArgs(int n);
  String& argsToRcd();

  int     noChecked();

private:

  void initialize(DescTable& descTbl);

  Collection();

  // returns either a pointer to data (or datum) at index i in array or zero
  FldDsc* datum(int i) {return 0 <= i && i < nData() ? &fields[i] : 0;}

  // returns number of data items in array
  int   nData()      {return fields.end();}

  friend typename ClnIter;
  };



class TableCode {
DescTable  descTbl;
Collection col;
TableNames tbl;

public:

   TableCode(TCchar* tblName) : descTbl(tblName), col(descTbl), tbl(tblName) { }
  ~TableCode() { }

   bool operator() (TblDsc& tbl);

private:

  int  load(String& tableName) {return descTbl.load(maps, tableName);}
  void createHeader();
  void createIterClass();

  void createBody();
  void createGet();
  void createFindID();
  void createFindIDargs(String& idFld);
  void createFind();
  void createAdd();

  void testArgsEmpty();

  TableCode() : col(*(DescTable*) 0), tbl(0) { }
  };

