// Create Map Body code (i.e. .cpp file)


#pragma once
#include "AceDao.h"
#include "DescTable.h"
#include "TableNames.h"




class MapBody {

enum SwitchType {nilTyp, ReadTyp, WrtTyp};

DescTable*  descTbl;
TableNames* tbl;

public:

  MapBody(DescTable& dsc) : descTbl(&dsc), tbl(0) {}

  void createFile(TableNames& table);

private:

  void createAdd();
  void createUpdate();
  void createToTable();
  void createToDatabase();
  void createErase();
  void createDBwrt();
  void createDBadd();
  void createGetFldVal();
  void createCopy();


  void createSwitch(TCchar* tab, TCchar* var, TCchar* retVal, SwitchType typ);
  };

