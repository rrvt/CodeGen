// Create Map Header Code


#pragma once
#include "AceDao.h"
#include "DescTable.h"


class MapHeader {
DescTable* descTbl;
Table*     tbl;

public:

  MapHeader(DescTable& dsc) : descTbl(&dsc), tbl(0) {}

  void createFile(Table& table);

private:

  MapHeader() : descTbl(0), tbl(0) {}

  void createRecordClass();
  void createMyDBclass();
  void createMyTableClass();
  void toTableComment();
  void toDatabaseComment();
  };




void createCopyright(TCchar* name);

