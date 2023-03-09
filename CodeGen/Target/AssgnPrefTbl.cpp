// AssgnPref Table


#include "stdafx.h"
#include "AssgnPrefTbl.h"
#include "DAOfields.h"
#include "DAOrecords.h"
#include "NotePad.h"
#include "Utilities.h"


bool AssgnPrefTbl::load(DAOtable* daoTable) {
DAOrcdsIter iter(daoTable);
FieldsP     fields;
int         count;

  for (count = 0, fields = iter(DAOdenyWrite); fields; count++, fields = iter++) {
    AssgnPrefRcd rcd;   rcd.load(fields);   data = rcd;
    }

  notePad << count << nCrlf; return true;
  }


void AssgnPrefRcd::load(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   dsc;
variant_t   v;

  for (dsc = iter(); dsc; dsc = iter++) {
    v = dsc->value();
    switch (iter.index()) {
      case  0: id    = v; break;
      case  1: apkey = v; break;
      case  2: txt   = v; break;
      default: throw _T("AssgnPref Record Error");
      }
    }
  }


void AssgnPrefTbl::store() {
DAOtable*     daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate AssgnPref Table");
DAOrcds       daoRcds(daoTbl);
FieldsP       fieldsP;
PrfIter       iter(*this);
AssgnPrefRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {

    if (rcd->isDeleted() && daoRcds.findRecord(rcd->id))
                                                       {daoRcds.delCurRcd();   iter.remove();   continue;}
    if (!rcd->isDirty()) continue;

    fieldsP = daoRcds.findRecord(rcd->id);   if (!fieldsP) continue;    // Add new records with addNewRcd

    daoRcds.edit();   rcd->store(fieldsP);   daoRcds.update();   rcd->clearMark();
    }
  }


AssgnPrefRcd* AssgnPrefTbl::add(AssgnPrefRcd& rcd) {
DAOtable* daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate AssgnPref Table");
DAOrcds   daoRcds(daoTbl);
FieldsP   fieldsP;

  fieldsP = daoRcds.findRecord(rcd.id);   if (fieldsP) return 0;

  fieldsP = daoRcds.addNew();   rcd.store(fieldsP);  daoRcds.update();  rcd.clearMark();

  return data = rcd;
  }


AssgnPrefRcd* AssgnPrefTbl::add(String apkey, String txt) {    // Add a new record to table and database
AssgnPrefRcd rcd;

  rcd.apkey = apkey;   rcd.txt = txt;   return add(rcd);
  }


void AssgnPrefRcd::store(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   field;
variant_t   v;

  for (field = iter(); field; field = iter++) {
    switch (iter.index()) {
      case  0: id = field->value(); continue;
      case  1: v  = apkey; break;
      case  2: v  = txt; break;
      default: throw _T("AssgnPref Record Error");
      }

    *field = v;
    }
  }


void AssgnPrefTbl::display() {
PrfIter       iter(*this);
AssgnPrefRcd* rcd;

  setTabs();

  notePad << _T("AssgnPref Table") << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) rcd->display();
  }


void AssgnPrefRcd::display() {
  notePad << nTab << id;
  notePad << nTab << apkey;
  notePad << nCrlf;
  }


void AssgnPrefTbl::setTabs() {
PrfIter       iter(*this);
AssgnPrefRcd* rcd;
int           tab0 = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    maxLng(rcd->id, tab0);
    }

  notePad << nClrTabs;
  notePad << nSetRTab(tab0) << nSetTab(tab0 + 2);
  }

