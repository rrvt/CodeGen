// Create MapData Header File


#include "stdafx.h"
#include "MapCode.h"
#include "NotePad.h"
#include "Utilities.h"



void MapCode::createMapDataHdr() {
TableDsc* tbl;
String    s;
int       maxNameLng = 0;
int       lng;

  for (tbl = tableDscrs.startLoop(); tbl; tbl = tableDscrs.nextEntry()) {
    if (tbl->selected) {lng = tbl->name.length();   if (lng > maxNameLng) maxNameLng = lng;}
    }

  notePad << _T("// A little class to control the order of initialization of the Table classes");
  notePad << nCrlf;

  createCopyright(_T("MapData"));   notePad << nCrlf;

  notePad << _T("#pragma once") << nCrlf;
  notePad << _T("#include \"MapsT.h\"") << nCrlf;
  notePad << _T("#include \"Maps.h\"") << nCrlf << nCrlf << nCrlf;

  notePad << _T("extern TCchar* FileSection;") << nCrlf;
  notePad << _T("extern TCchar* DBFileKey;") << nCrlf;
  notePad << _T("extern TCchar* GenFilePathKey;") << nCrlf << nCrlf << nCrlf;

  notePad << _T("class MapData {") << nCrlf << nCrlf;
  notePad << _T("AceDao dao;") << nCrlf << nCrlf;

  notePad << _T("public:") << nCrlf << nCrlf;

  maxNameLng += 5;                                            // Account for "Table" added to each name

  notePad << _T("String dbFilePath;") << nCrlf;
  notePad << _T("String databasePath;") << nCrlf << nCrlf;

  notePad << _T("  MapData() {}") << nCrlf;
  notePad << _T(" ~MapData() {closeDB();}") << nCrlf << nCrlf;

  notePad << _T("  bool    openDB(String& path);") << nCrlf << nCrlf;
  notePad << _T("  void    initializeMaps(Maps* mps);") << nCrlf << nCrlf;
  notePad << _T("  bool    openRcdSet( TCchar* name, DaoOptions option, AceRecordSet& rcdSet);") << nCrlf;
  notePad << _T("  bool    openFldDscs(TCchar* name, AceFieldNames& fldDscs);") << nCrlf;
  notePad << nCrlf;

  notePad << _T("private:") << nCrlf << nCrlf;

  notePad << _T("  void    closeDB();") << nCrlf << nCrlf;

  notePad << _T("  friend bool openDbTable(    TCchar* table);") << nCrlf;
  notePad << _T("  friend bool openDataBaseFor(TCchar* table);") << nCrlf;
  notePad << _T("  };") << nCrlf << nCrlf << nCrlf;

  notePad << _T("extern Maps maps;") << nCrlf << nCrlf;
  }

void MapCode::createMapsHdr() {
int       maxNameLng = 0;
int       lng;
TableDsc* tbl;

  notePad << _T("// The Map Objects") << nCrlf << nCrlf << nCrlf;
  notePad << _T("#pragma once") << nCrlf;

  for (tbl = tableDscrs.startLoop(); tbl; tbl = tableDscrs.nextEntry())
                    if (tbl->selected) notePad << _T("#include \"") << tbl->name << _T("Tbl.h\"") << nCrlf;

  notePad << nCrlf << nCrlf;

    for (tbl = tableDscrs.startLoop(); tbl; tbl = tableDscrs.nextEntry()) {
      if (tbl->selected) {lng = tbl->name.length();   if (lng > maxNameLng) maxNameLng = lng;}
      }

  notePad << nSetTab(maxNameLng + 11);

  for (tbl = tableDscrs.startLoop(); tbl; tbl = tableDscrs.nextEntry())
    if (tbl->selected) {
      notePad << _T("extern ") << tbl->name << _T("Tbl") << nTab;
      notePad << objName(tbl->name) << _T("Table;") << nCrlf;
      }
  }

