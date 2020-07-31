// Maps Code, i.e. MapData and Maps declarations


#include "stdafx.h"
#include "MapsCode.h"
#include "CodeGenII.h"
#include "NotePad.h"
#include "TableDscrs.h"
#include "Utilities.h"
#include "VarDecl.h"


void MapsCode::createMapDataHdr() {
TDIter    iter(tableDscrs);
TableDsc* dsc;
String    s;
int       maxNameLng = 0;
int       lng;

  for (dsc = iter(); dsc; dsc = iter++) {
    if (dsc->selected) {lng = dsc->accName.length();   if (lng > maxNameLng) maxNameLng = lng;}
    }

  notePad << _T("// A little class to control the order of initialization of the Table classes");
  notePad << nCrlf;

  createCopyright(_T("MapData"), theApp.version);   notePad << nCrlf;

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

void MapsCode::createMapsHdr() {
int       maxNameLng = 0;
int       lng;
TDIter    iter(tableDscrs);
TableDsc* dsc;

  notePad << _T("// The Map Objects") << nCrlf << nCrlf << nCrlf;
  notePad << _T("#pragma once") << nCrlf;

  for (dsc = iter(); dsc; dsc = iter++)
                  if (dsc->selected) notePad << _T("#include \"") << dsc->accName << _T("Tbl.h\"") << nCrlf;

  notePad << nCrlf << nCrlf;

    for (dsc = iter(); dsc; dsc = iter++) {
      if (dsc->selected) {lng = dsc->accName.length();   if (lng > maxNameLng) maxNameLng = lng;}
      }

  notePad << nSetTab(maxNameLng + 11);

  for (dsc = iter(); dsc; dsc = iter++)
    if (dsc->selected) {
      notePad << _T("extern ") << dsc->accName << _T("Tbl") << nTab;
      notePad << objName(dsc->accName) << _T("Table;") << nCrlf;
      }
  }



void MapsCode::createMapDataCpp() {
VarDeclarations decl;

TDIter          iter(tableDscrs);
TableDsc*       dsc;
String          s;
bool            selected;

  notePad << _T("// A little class to control the order of initialization of the Table classes");
  notePad << nCrlf;

  createCopyright(_T("MapData"), theApp.version);    notePad << nCrlf << nCrlf;

  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"MapData.h\"") << nCrlf;
  notePad << _T("#include \"IniFile.h\"") << nCrlf;
  notePad << _T("#include \"NotePad.h\"") << nCrlf << nCrlf << nCrlf;

  notePad << _T("TCchar* FileSection    = _T(\"DataBase File Names\");") << nCrlf;
  notePad << _T("TCchar* DBFileKey      = _T(\"DataBase File\");") << nCrlf;
  notePad << _T("TCchar* GenFilePathKey = _T(\"GenFilePath\");") << nCrlf << nCrlf << nCrlf;

  notePad << _T("Maps maps;") << nCrlf << nCrlf << nCrlf;


  notePad << _T("void MapData::initializeMaps(Maps* mps) {") << nCrlf;
  decl.add(_T("TDIter"),     _T("tdIter(tableDscrs)"));
  decl.add(_T("TableDsc*"),  _T("dsc"));
  decl.add(_T("AceTables"),  _T("aceTables(dao)"));
  decl.add(_T("ATIter"),     _T("atIter(aceTables)"));
  decl.add(_T("TableDesc*"), _T("atDsc"));

  decl.output();  notePad << nCrlf;

  selected = false;

  for (dsc = iter(); dsc; dsc = iter++)
    if (dsc->selected) {
      notePad << _T("  tableDscrs.add(") << objName(dsc->accName) << _T("Table, mps);") << nCrlf;
      selected = true;
      }
  notePad << nCrlf;

  if (selected) {
    notePad << _T("  for (dsc = tdIter(); dsc; dsc = tdIter++) ");
    notePad << _T("if (dsc->mapTable) dsc->mapTable->initialize();") << nCrlf << nCrlf;
    }

  notePad << _T("  for (atDsc = atIter(); atDsc; atDsc = atIter++) ");
  notePad << _T("tableDscrs.add(atDsc->name, 0, mps);") << nCrlf;

  notePad << _T("  }") << nCrlf << nCrlf << nCrlf;

  notePad << _T("bool MapData::openDB(String& path) {return dao.open(path);}") << nCrlf << nCrlf << nCrlf;

  notePad << _T("void MapData::closeDB() {dao.close();}") << nCrlf << nCrlf << nCrlf;

  notePad << _T("bool MapData::openRcdSet(TCchar* name, DaoOptions option, AceRecordSet& rcdSet) {");
  notePad << nCrlf;

  notePad << _T("AceTables tables(dao);") << nCrlf << nCrlf;

  notePad << _T("  return rcdSet.open(tables.find(name), DaoDenyWrite);") << nCrlf;
  notePad << _T("  }") << nCrlf << nCrlf << nCrlf;


  notePad << _T("bool MapData::openFldDscs(TCchar* name, AceFieldNames& fldDscs) {") << nCrlf;
  notePad << _T("AceTables  tables(dao);") << nCrlf;
  notePad << _T("TableDesc* tableDsc = tables.find(name);       if (!tableDsc) return 0;");
  notePad << nCrlf << nCrlf;

  notePad << _T("  return fldDscs.open(tableDsc);") << nCrlf;
  notePad << _T("  }") << nCrlf << nCrlf;
  }


void MapsCode::createMapsCpp() {
int       maxNameLng = 0;
int       lng;
TDIter    iter(tableDscrs);
TableDsc* dsc;

  notePad << _T("// The Map Objects") << nCrlf << nCrlf << nCrlf;
  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"Maps.h\"") << nCrlf << nCrlf << nCrlf;

    for (dsc = iter(); dsc; dsc = iter++) {
      if (dsc->selected) {lng = dsc->accName.length();   if (lng > maxNameLng) maxNameLng = lng;}
      }

  notePad << nSetTab(maxNameLng + 4);

  for (dsc = iter(); dsc; dsc = iter++)
    if (dsc->selected) {
      notePad << dsc->accName << _T("Tbl") << nTab;
      notePad << objName(dsc->accName) << _T("Table;") << nCrlf;
      }

  notePad << nCrlf;
  }

