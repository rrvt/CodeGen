// Maps Code, i.e. MapData and Maps declarations


#include "stdafx.h"
#include "MapsCode.h"
#include "CodeGen.h"
#include "NotePad.h"
#include "TblList.h"
#include "Utilities.h"
#include "VarDecl.h"


static TCchar* DataTitle = _T("// A little class to initialize of the Table classes ")
                           _T("and load the data from the database");


void MapsCode::createMapDataHdr() {
TLIter  iter(tblList);
TblDsc* dsc;
String  s;
int     maxNameLng = 0;
int     lng;

  for (dsc = iter(); dsc; dsc = iter++) {
    if (dsc->selected) {lng = dsc->accName.length();   if (lng > maxNameLng) maxNameLng = lng;}
    }

  notePad << DataTitle << nCrlf;

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

  notePad << _T("  bool    openDB(TCchar* path);") << nCrlf << nCrlf;
  notePad << _T("  void    initializeMaps();") << nCrlf << nCrlf;
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
TLIter  iter(tblList);
TblDsc* dsc;

  notePad << _T("// The Map Objects") << nCrlf << nCrlf << nCrlf;
  notePad << _T("#pragma once") << nCrlf;

  for (dsc = iter(); dsc; dsc = iter++)
            if (dsc->selected) notePad << _T("#include \"") << dsc->accName << _T("Table.h\"") << nCrlf;

  notePad << nCrlf << nCrlf;

  mapObjDecl(true);
  }


void MapsCode::mapObjDecl(bool isExtern) {
TLIter          iter(tblList);
TblDsc*         dsc;
VarDeclarations decl;
String          typ;
String          obj;

  decl.clear();

  for (dsc = iter(); dsc; dsc = iter++) if (dsc->selected) {
    typ.clear();
    if (isExtern) typ = _T("extern ");

    typ += dsc->accName + _T("Table");
    obj = objName(dsc->accName) + _T("Table");
    decl.add(typ, obj);
    }

  decl.output();
  }


void MapsCode::createMapDataCpp() {
VarDeclarations decl;
TLIter          iter(tblList);
TblDsc*         dsc;
String          s;
bool            selected;

  notePad << DataTitle << nCrlf;

  createCopyright(_T("MapData"), theApp.version);    notePad << nCrlf;

  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"MapData.h\"") << nCrlf;
  notePad << _T("#include \"IniFile.h\"") << nCrlf;
  notePad << _T("#include \"NotePad.h\"") << nCrlf << nCrlf << nCrlf;

  notePad << _T("TCchar* FileSection    = _T(\"DataBase File Names\");") << nCrlf;
  notePad << _T("TCchar* DBFileKey      = _T(\"DataBase File\");") << nCrlf;
  notePad << _T("TCchar* GenFilePathKey = _T(\"GenFilePath\");") << nCrlf << nCrlf << nCrlf;

  notePad << _T("Maps maps;") << nCrlf << nCrlf << nCrlf;


  notePad << _T("void MapData::initializeMaps() {") << nCrlf;
  decl.add(_T("TLIter"),     _T("iter(tblList)"));
  decl.add(_T("TblDsc*"),    _T("dsc"));
  decl.add(_T("AceTables"),  _T("aceTables(dao)"));
  decl.add(_T("ATIter"),     _T("atIter(aceTables)"));
  decl.add(_T("TableDesc*"), _T("atDsc"));

  decl.output();  notePad << nCrlf;

  selected = false;

  for (dsc = iter(); dsc; dsc = iter++) if (dsc->selected) {
    notePad << _T("  tblList.add(") << objName(dsc->accName) << _T("Table);") << nCrlf;
    selected = true;
    }

  notePad << nCrlf;

  if (selected) {
    notePad << _T("  for (dsc = iter(); dsc; dsc = iter++) ");
    notePad << _T("if (dsc->mapTable) dsc->mapTable->initialize();") << nCrlf << nCrlf;
    }

  notePad << _T("  for (atDsc = atIter(); atDsc; atDsc = atIter++) ");
  notePad << _T("tblList.add(atDsc->name, 0);") << nCrlf;

  notePad << _T("  }") << nCrlf << nCrlf << nCrlf;

  notePad << _T("bool MapData::openDB(TCchar* path) {return dao.open(path);}") << nCrlf << nCrlf << nCrlf;

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

  notePad << _T("// The Map Objects") << nCrlf << nCrlf << nCrlf;
  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"Maps.h\"") << nCrlf << nCrlf << nCrlf;

  mapObjDecl(false);
  notePad << nCrlf;
  }

