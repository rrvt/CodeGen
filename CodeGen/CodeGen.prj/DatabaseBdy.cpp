// Create the local database objects body


#include "pch.h"
#include "DatabaseBdy.h"
#include "DbTblList.h"
#include "Declarations.h"
#include "ModNames.h"
#include "NotePad.h"


void DatabaseBdy::create() {
DbTblIter    iter(dbTblList);
TblItem*     tblItem;
Declarations decl;
String       left;
String       right;

  notePad.clear();

  notePad << _T("// Database") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("#include \"pch.h\"") << nCrlf;
  notePad << _T("#include \"Database.h\"") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  decl.add(_T("Database"), _T("database"));
  decl.add(_T("AccessDB"), _T("accessDB"));

  for (tblItem = iter(); tblItem; tblItem = iter++) {

    if (!tblItem->selected) continue;

    if (!modNames.set(tblItem->name)) {notePad << _T("modNames failure") << nCrlf; return;}

    decl.add(modNames.tblCls, modNames.tblObj);
    }
  decl.output();
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("bool Database::load(TCchar* path) {") << nCrlf;
  notePad << _T("  if (!accessDB.open(path)) return false;") << nCrlf;

  for (tblItem = iter(); tblItem; tblItem = iter++) {

    if (!tblItem->selected) continue;

    if (!modNames.set(tblItem->name)) {notePad << _T("modNames failure") << nCrlf; return;}

    notePad << _T("  if (!") << modNames.tblObj << _T(".load(path))   return false;") << nCrlf;
    }
  notePad << nCrlf;

  notePad << _T("  return true;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("Database::~Database() {accessDB.close();}") << nCrlf;
  }

