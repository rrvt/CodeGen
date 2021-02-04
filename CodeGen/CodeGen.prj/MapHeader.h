// Create Map Header Code


#pragma once
#include "AceDao.h"
#include "DescTable.h"
#include "TableNames.h"


class MapHeader {
DescTable*  descTbl;
TableNames* tbl;

public:

  MapHeader(DescTable& dsc) : descTbl(&dsc), tbl(0) {}

  void createFile(TableNames& table);

private:

  MapHeader() : descTbl(0), tbl(0) {}

  void createRecordClass();
  void createCnstr();
  void createDBclass();
  void createMapClass();
  void toTableComment();
  void toDatabaseComment();
  };

