// Table Descriptor Report


#include "stdafx.h"
#include "TableDscRpt.h"
#include "CScrView.h"
#include "DescTable.h"
#include "TableDscrs.h"


void TableDscRpt::create() {
int       i;
TDIter    iter(tableDscrs);
TableDsc* dsc;

  np.clear();  detTabs();   noLines = 0;  noPages = 0;

  for (i = 0, dsc = iter(); dsc; dsc = iter++) {

    if (dsc->selected) {

      if (!isNewPage(3) && i++) {np << nCrlf; noLines++;}

      dspRecords(dsc->accName);
      }
    }
  }


void TableDscRpt::detTabs() {
TDIter    iter(tableDscrs);
TableDsc* dsc;

  for (maxLng = 0, dsc = iter(); dsc; dsc = iter++) {
    if (dsc->selected) detTblTabs(dsc->accName);
    }
  }


void TableDscRpt::detTblTabs(String& name) {
DescTable  descTbl;
DTIter     iter(descTbl);
FieldDesc* dsc;

  descTbl.load(maps, name);

  for (dsc = iter(); dsc; dsc = iter++) {
    int lng = dsc->name.length();   if (lng > maxLng) maxLng = lng;
    }
  }


void TableDscRpt::dspRecords(String& name) {
DescTable  descTbl;
DTIter     iter(descTbl);
FieldDesc* dsc;

  descTbl.load(maps, name);   tableName = name;

  noLines += header(np, printing);

  for (dsc = iter(); dsc; dsc = iter++) {

    if (isNewPage(1)) noLines += header(np, printing);

    np << nTab << dsc->fieldIndex;
    np << nTab << dsc->name;
    np << nTab << getDbCppType(dsc->x);
    np << nTab << dsc->isIndex;
    np << nCrlf;   noLines++;
    }
  }


bool TableDscRpt::isNewPage(int n) {

  if (noLines + n <= maxLines) return false;

  if (noPages++) np << nEndPage;

  noLines = 0;  return true;
  }



int TableDscRpt::header(NotePad& ntpd, bool printing) {
int tab0 = 3;
int tab1 = tab0 + 2;
int tab2 = tab1 + maxLng + 3;
int tab3 = tab2 + 16;

  np << tableName << _T(" Table") << nCrlf;

  np << nClrTabs << nSetRTab(tab0) << nSetTab(tab1) << nSetTab(tab2) << nSetRTab(tab3);

  np << nTab << _T("No") << nTab << _T("Name")  << nTab << _T("Type");
  np << nTab << _T("Is Index") << nCrlf;   return 2;

  }


void TableDscRpt::footer(Display& dev, int pageN) {

  if (pageN > maxPages) maxPages = pageN;

  dev << dCenter << pageN << _T(" of ") << maxPages << dflushFtr;
  }



