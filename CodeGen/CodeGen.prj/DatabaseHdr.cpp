// Create the local database objects


#include "pch.h"
#include "DatabaseHdr.h"
#include "DbTblList.h"
#include "ModNames.h"
#include "NotePad.h"


void DatabaseHdr::create() {
DbTblIter    iter(dbTblList);
TblItem*     tblItem;

  notePad.clear();

  notePad << _T("// Database") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("#pragma once") << nCrlf;
  notePad << _T("#include \"AccessDB.h\"") << nCrlf;

  for (tblItem = iter(); tblItem; tblItem = iter++) {

    if (!tblItem->selected) continue;

    if (!modNames.set(tblItem->name)) {notePad << _T("modNames failure") << nCrlf; return;}

    notePad << _T("#include \"") << modNames.tblCls << _T(".h\"") << nCrlf;
    }
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("class Database {") << nCrlf;
  notePad << _T("public:") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  Database() { }") << nCrlf;
  notePad << _T(" ~Database() { }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  bool load(TCchar* path);") << nCrlf;
  notePad << _T("  };") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("extern Database database;") << nCrlf;
  notePad << nCrlf;
  }

