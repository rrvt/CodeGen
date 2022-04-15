// Names used in the Module (class)


#include "stdafx.h"
#include "ModNames.h"
#include "Capitalize.h"
#include "DbTblList.h"


ModNames modNames;


bool ModNames::set(TCchar* table) {
TblItem* tblItem = dbTblList.find(table);   if (!tblItem) return false;

  abbr      = tblItem->abbr;

  accTbl    = table;
  tblCls    = abbr + _T("Tbl");

  tblObj    = notCaped(tblCls);

  rcdCls    = abbr    + _T("Rcd");
  rcdPCls   = rcdCls  + _T('P');
  tblIter   = abbr    + _T("Iter");

  setCls    = abbr    + _T("Set");
  setObj    = notCaped(setCls);
  setIterCls= setCls  + _T("Iter");

  dbIndex   = tblItem->primKey;
  index     = notCaped(dbIndex);
  indexType = tblItem->pKeyType;
  return true;
  }



#if 1
#else
AbbrDlg dlg;

  dlg.table = table;

  if (dlg.DoModal() != IDOK) return false;

  abbr      = capitalize(dlg.abbr);

#endif

