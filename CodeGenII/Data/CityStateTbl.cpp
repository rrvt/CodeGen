// CityState Table


#include "stdafx.h"
#include "CityStateTbl.h"
#include "DAOfields.h"
#include "DAOrecords.h"
#include "NotePad.h"
#include "Utilities.h"


bool CityStateTbl::load(DAOtable* daoTable) {
DAOrcdsIter iter(daoTable);
FieldsP     fields;
int         count;

  for (count = 0, fields = iter(DAOdenyWrite); fields; count++, fields = iter++) {
    CityStateRcd rcd;   rcd.load(fields);   data = rcd;
    }

  notePad << count << nCrlf; return true;
  }


void CityStateRcd::load(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   dsc;
variant_t   v;

  for (dsc = iter(); dsc; dsc = iter++) {
    v = dsc->value();
    switch (iter.index()) {
      case  0: id    = v; break;
      case  1: city  = v; break;
      case  2: state = v; break;
      case  3: zip   = v; break;
      default: throw _T("CityState Record Error");
      }
    }
  }


void CityStateTbl::store() {
DAOtable*     daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate CityState Table");
DAOrcds       daoRcds(daoTbl);
FieldsP       fieldsP;
CtyIter       iter(*this);
CityStateRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {

    if (rcd->isDeleted() && daoRcds.findRecord(rcd->id))
                                                       {daoRcds.delCurRcd();   iter.remove();   continue;}
    if (!rcd->isDirty()) continue;

    fieldsP = daoRcds.findRecord(rcd->id);   if (!fieldsP) continue;    // Add new records with addNewRcd

    daoRcds.edit();   rcd->store(fieldsP);   daoRcds.update();   rcd->clearMark();
    }
  }


CityStateRcd* CityStateTbl::add(CityStateRcd& rcd) {
DAOtable* daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate CityState Table");
DAOrcds   daoRcds(daoTbl);
FieldsP   fieldsP;

  fieldsP = daoRcds.findRecord(rcd.id);   if (fieldsP) return 0;

  fieldsP = daoRcds.addNew();   rcd.store(fieldsP);  daoRcds.update();  rcd.clearMark();

  return data = rcd;
  }


void CityStateRcd::store(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   field;
variant_t   v;

  for (field = iter(); field; field = iter++) {
    switch (iter.index()) {
      case  0: id = field->value(); continue;
      case  1: v  = city; break;
      case  2: v  = state; break;
      case  3: v  = zip; break;
      default: throw _T("CityState Record Error");
      }

    *field = v;
    }
  }


CityStateRcd* CityStateTbl::find(TCchar* city, TCchar* zip) {
CtyIter       iter(*this);
CityStateRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->isInRcd(city, zip)) return rcd;

  return 0;
  }


void CityStateTbl::display() {
CtyIter       iter(*this);
CityStateRcd* rcd;

  setTabs();

  notePad << _T("CityState Table") << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) rcd->display();
  }


void CityStateRcd::display() {
  notePad << nTab << id;
  notePad << nTab << city;
  notePad << nTab << zip;
  notePad << nCrlf;
  }


void CityStateTbl::setTabs() {
CtyIter       iter(*this);
CityStateRcd* rcd;
int           tab0 = 0;
int           tab1 = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    maxLng(rcd->id, tab0);
    maxLng(rcd->city, tab1);
    }

  tab1 += tab0 + 4;

  notePad << nClrTabs;
  notePad << nSetRTab(tab0) << nSetTab(tab0 + 2);
  notePad << nSetTab(tab1);
  }

