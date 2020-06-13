// Create MapData Header File


#include "stdafx.h"
#include "MapCode.h"
#include "NotePad.h"
#include "Utilities.h"



void MapCode::createMapDataCpp() {
TableDsc* tbl;
String    s;
bool      selected;

  notePad << _T("// A little class to control the order of initialization of the Table classes");
  notePad << nCrlf;

  createCopyright(_T("MapData"));    notePad << nCrlf << nCrlf;

  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"MapData.h\"") << nCrlf;
  notePad << _T("#include \"IniFile.h\"") << nCrlf;
  notePad << _T("#include \"NotePad.h\"") << nCrlf << nCrlf << nCrlf;

  notePad << _T("TCchar* FileSection    = _T(\"DataBase File Names\");") << nCrlf;
  notePad << _T("TCchar* DBFileKey      = _T(\"DataBase File\");") << nCrlf;
  notePad << _T("TCchar* GenFilePathKey = _T(\"GenFilePath\");") << nCrlf << nCrlf << nCrlf;

  notePad << _T("Maps maps;") << nCrlf << nCrlf << nCrlf;


  notePad << _T("void MapData::initializeMaps(Maps* mps) {") << nCrlf;
  notePad << _T("AceTables aceTables(dao);") << nCrlf;

  selected = false;

  for (tbl = tableDscrs.startLoop(); tbl; tbl = tableDscrs.nextEntry())
    if (tbl->selected) {
      notePad << nCrlf << _T("  tableDscrs.add(") << objName(tbl->name) << _T("Table, mps);");
      selected = true;
      }

  if (selected) {
    notePad << nCrlf << nCrlf;

    notePad << _T("  for (TableDsc* tblDsc = tableDscrs.startLoop(); tblDsc; ");
    notePad << _T("tblDsc = tableDscrs.nextEntry())") << nCrlf;
    s =  _T("if (tblDsc->mapTable) tblDsc->mapTable->initialize();");  toRight(s);
    }

  notePad << nCrlf;
  notePad << _T("  for (TableDesc* dsc = aceTables.startLoop(); dsc; dsc = aceTables.nextTable())");
  notePad << nCrlf;
  s = _T("tableDscrs.add(dsc->name, 0, mps);");   toRight(s);

  notePad << _T("  }") << nCrlf << nCrlf << nCrlf;

//  for (dsc = aceTables.startLoop(); dsc; dsc = aceTables.nextTable()) tableDscrs.add(dsc->name, 0, mps);


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


void MapCode::createMapsCpp() {
int       maxNameLng = 0;
int       lng;
TableDsc* tbl;

  notePad << _T("// The Map Objects") << nCrlf << nCrlf << nCrlf;
  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"Maps.h\"") << nCrlf << nCrlf << nCrlf;

    for (tbl = tableDscrs.startLoop(); tbl; tbl = tableDscrs.nextEntry()) {
      if (tbl->selected) {lng = tbl->name.length();   if (lng > maxNameLng) maxNameLng = lng;}
      }

  notePad << nSetTab(maxNameLng + 4);

  for (tbl = tableDscrs.startLoop(); tbl; tbl = tableDscrs.nextEntry())
    if (tbl->selected) {
      notePad << tbl->name << _T("Tbl") << nTab;
      notePad << objName(tbl->name) << _T("Table;") << nCrlf;
      }

  notePad << nCrlf;
  }

