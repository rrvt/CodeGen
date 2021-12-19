// LocationPref Table


#include "stdafx.h"
#include "LocationPrefTbl.h"
#include "DAOfields.h"
#include "DAOrecords.h"
#include "NotePad.h"
#include "Utilities.h"


bool LocationPrefTbl::load(DAOtable* daoTable) {
DAOrcdsIter iter(daoTable);
FieldsP     fields;
int         count;

  for (count = 0, fields = iter(DAOdenyWrite); fields; count++, fields = iter++) {
    LocationPrefRcd rcd;   rcd.load(fields);   data = rcd;
    }

  notePad << count << nCrlf; return true;
  }


void LocationPrefRcd::load(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   dsc;
variant_t   v;

  for (dsc = iter(); dsc; dsc = iter++) {
    v = dsc->value();
    switch (iter.index()) {
      case  0: id  = v; break;
      case  1: key = v; break;
      case  2: txt = v; break;
      default: throw _T("LocationPref Record Error");
      }
    }
  }


void LocationPrefTbl::store() {
DAOtable*        daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate LocationPref Table");
DAOrcds          daoRcds(daoTbl);
FieldsP          fieldsP;
LocIter          iter(*this);
LocationPrefRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {

    if (rcd->isDeleted() && daoRcds.findRecord(rcd->id))
                                                       {daoRcds.delCurRcd();   iter.remove();   continue;}
    if (!rcd->isDirty()) continue;

    fieldsP = daoRcds.findRecord(rcd->id);   if (!fieldsP) continue;    // Add new records with addNewRcd

    daoRcds.edit();   rcd->store(fieldsP);   daoRcds.update();   rcd->clearMark();
    }
  }


LocationPrefRcd* LocationPrefTbl::add(LocationPrefRcd& rcd) {
DAOtable* daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate LocationPref Table");
DAOrcds   daoRcds(daoTbl);
FieldsP   fieldsP;

  fieldsP = daoRcds.findRecord(rcd.id);   if (fieldsP) return 0;

  fieldsP = daoRcds.addNew();   rcd.store(fieldsP);  daoRcds.update();  rcd.clearMark();

  return data = rcd;
  }


LocationPrefRcd* LocationPrefTbl::add(String key, String txt) {    // Add a new record to table and database
LocationPrefRcd rcd;

  rcd.key = key;   rcd.txt = txt;   return add(rcd);
  }


void LocationPrefRcd::store(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   field;
variant_t   v;

  for (field = iter(); field; field = iter++) {
    switch (iter.index()) {
      case  0: id = field->value(); continue;
      case  1: v  = key; break;
      case  2: v  = txt; break;
      default: throw _T("LocationPref Record Error");
      }

    *field = v;
    }
  }


void LocationPrefTbl::display() {
LocIter          iter(*this);
LocationPrefRcd* rcd;

  setTabs();

  notePad << _T("LocationPref Table") << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) rcd->display();
  }


void LocationPrefRcd::display() {
  notePad << nTab << id;
  notePad << nTab << key;
  notePad << nCrlf;
  }


void LocationPrefTbl::setTabs() {
LocIter          iter(*this);
LocationPrefRcd* rcd;
int              tab0 = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    maxLng(rcd->id, tab0);
    }

  notePad << nClrTabs;
  notePad << nSetRTab(tab0) << nSetTab(tab0 + 2);
  }

