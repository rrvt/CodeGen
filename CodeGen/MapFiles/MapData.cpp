// A little class to control the order of initialization of the Table classes
// MapData Map logic, Version 1.5.4.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.



#include "stdafx.h"
#include "MapData.h"
#include "IniFile.h"
#include "NotePad.h"


TCchar* FileSection    = _T("DataBase File Names");
TCchar* DBFileKey      = _T("DataBase File");
TCchar* GenFilePathKey = _T("GenFilePath");


Maps maps;


void MapData::initializeMaps(Maps* mps) {
AceTables aceTables(dao);

  tableDscrs.add(booksTable, mps);
  tableDscrs.add(personTable, mps);

  for (TableDsc* tblDsc = tableDscrs.startLoop(); tblDsc; tblDsc = tableDscrs.nextEntry())
                                                    if (tblDsc->mapTable) tblDsc->mapTable->initialize();
  }


bool MapData::openDB(String& path) {return dao.open(path);}


void MapData::closeDB() {dao.close();}


bool MapData::openRcdSet(TCchar* name, DaoOptions option, AceRecordSet& rcdSet) {
AceTables tables(dao);

  return rcdSet.open(tables.find(name), DaoDenyWrite);
  }


bool MapData::openFldDscs(TCchar* name, AceFieldNames& fldDscs) {
AceTables  tables(dao);
TableDesc* tableDsc = tables.find(name);       if (!tableDsc) return 0;

  return fldDscs.open(tableDsc);
  }

