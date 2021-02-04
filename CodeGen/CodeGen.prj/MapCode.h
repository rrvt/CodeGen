// Map Code


#pragma once
#include "DescTable.h"
#include "MapBody.h"
#include "MapHeader.h"
#include "TableNames.h"


class Collection;


class MapCode {
DescTable  descTbl;

public:
TableNames tbl;
String     key;

  MapCode(TCchar* tblName, TCchar* abbr) : descTbl(tblName), tbl(tblName, abbr, getKeyDesc()) { }
 ~MapCode() {}

  FieldDesc* getKeyDesc() {return descTbl.getKeyDesc();}

  void       createHeader() {MapHeader mh(descTbl); mh.createFile(tbl);}
  void       createCpp()    {MapBody   mb(descTbl); mb.createFile(tbl);}

private:

  MapCode() : descTbl(0), tbl(0) { }
  };

