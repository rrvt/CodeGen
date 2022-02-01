// Status Table


#include "stdafx.h"
#include "StatusTbl.h"
#include "DAOfields.h"
#include "DAOrecords.h"
#include "NotePad.h"
#include "Utilities.h"


bool StatusTbl::load(DAOtable* daoTable) {
DAOrcdsIter iter(daoTable);
FieldsP     fields;
int         count;

  for (count = 0, fields = iter(DAOdenyWrite); fields; count++, fields = iter++) {
    StatusRcd rcd;   rcd.load(fields);   data = rcd;
    }

  notePad << count << nCrlf; return true;
  }


void StatusRcd::load(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   dsc;
variant_t   v;

  for (dsc = iter(); dsc; dsc = iter++) {
    v = dsc->value();
    switch (iter.index()) {
      case  0: id           = v; break;
      case  1: abbreviation = v; break;
      case  2: description  = v; break;
      default: throw _T("Status Record Error");
      }
    }
  }


void StatusTbl::store() {
DAOtable*  daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate Status Table");
DAOrcds    daoRcds(daoTbl);
FieldsP    fieldsP;
StsIter    iter(*this);
StatusRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {

    if (rcd->isDeleted() && daoRcds.findRecord(rcd->id))
                                                       {daoRcds.delCurRcd();   iter.remove();   continue;}
    if (!rcd->isDirty()) continue;

    fieldsP = daoRcds.findRecord(rcd->id);   if (!fieldsP) continue;    // Add new records with addNewRcd

    daoRcds.edit();   rcd->store(fieldsP);   daoRcds.update();   rcd->clearMark();
    }
  }


StatusRcd* StatusTbl::add(StatusRcd& rcd) {
DAOtable* daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate Status Table");
DAOrcds   daoRcds(daoTbl);
FieldsP   fieldsP;

  fieldsP = daoRcds.findRecord(rcd.id);   if (fieldsP) return 0;

  fieldsP = daoRcds.addNew();   rcd.store(fieldsP);  daoRcds.update();  rcd.clearMark();

  return data = rcd;
  }


StatusRcd* StatusTbl::add(String abbreviation, String description) {    // Add a new record to table and database
StatusRcd rcd;

  rcd.abbreviation = abbreviation;   rcd.description = description;   return add(rcd);
  }


void StatusRcd::store(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   field;
variant_t   v;

  for (field = iter(); field; field = iter++) {
    switch (iter.index()) {
      case  0: id = field->value(); continue;
      case  1: v  = abbreviation; break;
      case  2: v  = description; break;
      default: throw _T("Status Record Error");
      }

    *field = v;
    }
  }


void StatusTbl::display() {
StsIter    iter(*this);
StatusRcd* rcd;

  setTabs();

  notePad << _T("Status Table") << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) rcd->display();
  }


void StatusRcd::display() {
  notePad << nTab << id;
  notePad << nTab << abbreviation;
  notePad << nCrlf;
  }


void StatusTbl::setTabs() {
StsIter    iter(*this);
StatusRcd* rcd;
int        tab0 = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    maxLng(rcd->id, tab0);
    }

  notePad << nClrTabs;
  notePad << nSetRTab(tab0) << nSetTab(tab0 + 2);
  }

