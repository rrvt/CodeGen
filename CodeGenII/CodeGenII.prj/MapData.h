// A little class to control the order of initialization of the Table classes
// MapData Map logic, Version 1.5.4.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.


#pragma once
#include "MapsT.h"
#include "Maps.h"


extern TCchar* FileSection;
extern TCchar* DBFileKey;
extern TCchar* GenFilePathKey;


class MapData {

AceDao dao;

public:

String dbFilePath;
String databasePath;

  MapData() {}
 ~MapData() {closeDB();}

  bool    openDB(TCchar* path);

  void    initializeMaps(Maps* mps);

  bool    openRcdSet( TCchar* name, DaoOptions option, AceRecordSet& rcdSet);
  bool    openFldDscs(TCchar* name, AceFieldNames& fldDscs);

private:

  void    closeDB();

  friend bool openDbTable(    TCchar* table);
  friend bool openDataBaseFor(TCchar* table);
  };


extern Maps maps;

