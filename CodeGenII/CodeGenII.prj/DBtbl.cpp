// Create header and body for DBtable Module that is to be included with Database Table Modules


#include "stdafx.h"
#include "DBtbl.h"
#include "DAOtables.h"
#include "DBTblSelDlg.h"
#include "Declarations.h"
#include "NotePad.h"



DBtbl dbTbl;


#if 0
// Defines all Database Tables and a list of them


#pragma once
#include "DBtablesB.h"


class DBtables : public DBtablesB {

public:

  DBtables() : DBtablesB() { }
 ~DBtables() { }

  DBtables& operator+= (DBtable* tbl) {data += tbl; return *this;}
  DBtables& operator=  (DBtable* tbl) {data  = tbl; return *this;}
  };

extern DBtables dbTables;
#endif

void DBtbl::hdrCreate() {
  if (!selectTables()) return;

  notePad.clear();

  notePad << _T("// Defines all Database Tables and a list of them") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("#pragma once") << nCrlf;
  notePad << _T("#include \"DBtablesB.h\"") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("class DBtables : public DBtablesB {") << nCrlf;
  notePad << nCrlf;

  notePad << _T("public:") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  DBtables() : DBtablesB() { }") << nCrlf;
  notePad << _T(" ~DBtables() { }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  DBtables& operator+= (DBtable* tbl) {data += tbl; return *this;}") << nCrlf;
  notePad << _T("  DBtables& operator=  (DBtable* tbl) {data  = tbl; return *this;}") << nCrlf;
  notePad << _T("  };") << nCrlf;
  notePad << nCrlf;

  notePad << _T("extern DBtables dbTables;") << nCrlf;
  notePad << nCrlf;
  }




void DBtbl::bodyCreate() {
DBtblIter iter(*this);
Table*    tbl;
bool      daoDone = false;

  notePad.clear();

  notePad << _T("// Defines all Database Tables and a list of them") << nCrlf;
  notePad << _T("// The DBtable object must be defined before the individual table objects.") << nCrlf;
  notePad << _T("// This module determines the order of initialization.") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("#include \"stdafx.h\"") << nCrlf;
  notePad << _T("#include \"DBtables.h\"") << nCrlf;

  for (tbl = iter(); tbl; tbl = iter++) {

    if (!tbl->selected) continue;

    addDAOinclude(tbl, daoDone);

    notePad << _T("#include \"") << tbl->name << _T("Tbl.h\"") << nCrlf;
    }

  addDAOinclude(0, daoDone);
  notePad << nCrlf;
  notePad << nCrlf;

  objects();
  }


void DBtbl::addDAOinclude(Table* tbl, bool& done) {
  if (done) return;
  if (!tbl || tbl->name > _T("DAOtables.h"))
                                    {notePad << _T("#include \"DAOtables.h\"") << nCrlf;   done = true;}
  }


void DBtbl::objects() {
DBtblIter    iter(*this);
Table*       tbl;
Declarations decl;

  decl.add(_T("DAOtables"), _T("daoTables"));
  decl.add(_T("DBtables"),  _T("dbTables"));

  for (tbl = iter(); tbl; tbl = iter++) {

    if (!tbl->selected) continue;

    String typ = tbl->name + _T("Tbl");
    String obj = typ;
    Tchar& ch = obj[0]; if (_T('A') <= ch && ch <= _T('Z')) ch += _T('a') - _T('A');

    decl.add(typ, obj);
    }
  decl.output();
  }


void DBtbl::loadTableNames() {
DAOiter     iter(daoTables);
DAOtable* daoTbl;
  for (daoTbl = iter(); daoTbl; daoTbl = iter++) {Table tbl;   tbl.name = daoTbl->name;   data = tbl;}
  }


bool DBtbl::selectTables() {DBtblSelDlg dlg(data, *this);   return dlg.DoModal() == IDOK;}


