// Address Table


#include "stdafx.h"
#include "AddressTbl.h"
#include "DAOfields.h"
#include "DAOrecords.h"
#include "NotePad.h"
#include "Utilities.h"


bool AddressTbl::load(DAOtable* daoTable) {
DAOrcdsIter iter(daoTable);
FieldsP     fields;
int         count;

  for (count = 0, fields = iter(DAOdenyWrite); fields; count++, fields = iter++) {
    AddressRcd rcd;   rcd.load(fields);   data = rcd;
    }

  notePad << count << nCrlf; return true;
  }


void AddressRcd::load(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   dsc;
variant_t   v;

  for (dsc = iter(); dsc; dsc = iter++) {
    v = dsc->value();
    switch (iter.index()) {
      case  0: id       = v; break;
      case  1: address1 = v; break;
      case  2: address2 = v; break;
      default: throw _T("Address Record Error");
      }
    }
  }


void AddressTbl::store() {
DAOtable*   daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate Address Table");
DAOrcds     daoRcds(daoTbl);
FieldsP     fieldsP;
AdrIter     iter(*this);
AddressRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {

    if (rcd->isDeleted() && daoRcds.findRecord(rcd->id))
                                                       {daoRcds.delCurRcd();   iter.remove();   continue;}
    if (!rcd->isDirty()) continue;

    fieldsP = daoRcds.findRecord(rcd->id);   if (!fieldsP) continue;    // Add new records with addNewRcd

    daoRcds.edit();   rcd->store(fieldsP);   daoRcds.update();   rcd->clearMark();
    }
  }


AddressRcd* AddressTbl::add(AddressRcd& rcd) {
DAOtable* daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate Address Table");
DAOrcds   daoRcds(daoTbl);
FieldsP   fieldsP;

  fieldsP = daoRcds.findRecord(rcd.id);   if (fieldsP) return 0;

  fieldsP = daoRcds.addNew();   rcd.store(fieldsP);  daoRcds.update();  rcd.clearMark();

  return data = rcd;
  }


AddressRcd* AddressTbl::add(String address1, String address2) {    // Add a new record to table and database
AddressRcd rcd;

  rcd.address1 = address1;   rcd.address2 = address2;   return add(rcd);
  }


void AddressRcd::store(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   field;
variant_t   v;

  for (field = iter(); field; field = iter++) {
    switch (iter.index()) {
      case  0: id = field->value(); continue;
      case  1: v  = address1; break;
      case  2: v  = address2; break;
      default: throw _T("Address Record Error");
      }

    *field = v;
    }
  }


AddressRcd* AddressTbl::find(TCchar* address1, TCchar* address2) {
AdrIter     iter(*this);
AddressRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->isInRcd(address1, address2)) return rcd;

  return 0;
  }


void AddressTbl::display() {
AdrIter     iter(*this);
AddressRcd* rcd;

  setTabs();

  notePad << _T("Address Table") << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) rcd->display();
  }


void AddressRcd::display() {
  notePad << nTab << id;
  notePad << nTab << address1;
  notePad << nTab << address2;
  notePad << nCrlf;
  }


void AddressTbl::setTabs() {
AdrIter     iter(*this);
AddressRcd* rcd;
int         tab0 = 0;
int         tab1 = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    maxLng(rcd->id, tab0);
    maxLng(rcd->address1, tab1);
    }

  tab1 += tab0 + 4;

  notePad << nClrTabs;
  notePad << nSetRTab(tab0) << nSetTab(tab0 + 2);
  notePad << nSetTab(tab1);
  }

