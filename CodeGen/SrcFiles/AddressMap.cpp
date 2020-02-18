// Address Map logic, Version 1.5.3.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "MapData.h"
#include "NotePad.h"


AddressTable::MyMap AddressTable::myMap;


bool AddressTable::add(AddressRecord& rcd) {
Rslt rslt;

  if (!rcd.AddressID) rcd.AddressID = maxKey + 1;

  rslt = myMap.insert(make_pair(rcd.AddressID, rcd));

  it = rslt.second ? rslt.first : myMap.end();

  if (rslt.second && rcd.AddressID > maxKey) maxKey = rcd.AddressID;

  return rslt.second;
  }


bool AddressDB::toTable(AceRecordSet& records, AddressTable& myTable) {
AceFields     fields(records);
AceFieldDsc   fld;
bool          rslt;
int           i;
variant_t     v;
AddressRecord rcd;

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    v = fld.value;
    switch (i) {
      case  0 : rcd.AddressID = v; break;
      case  1 : rcd.Address1  = v; break;
      case  2 : rcd.Address2  = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool AddressDB::toDatabase(AddressTable& myTable) {
AddressRecord* r;

  if (!maps.openRcdSet(_T("Address"), DaoDenyWrite, rcdSet)) return false;

  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {

    if (r->toDelete()) {erase(r->AddressID); myTable.erase(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool AddressDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool AddressDB::wrt(AddressRecord& rcd) {
AceFields   fields(rcdSet);
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  if (rcdSet.findRecord(rcd.AddressID)) rcdSet.edit();
  else rcdSet.addNew();

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    switch (i) {
      case  0 : rcd.AddressID = fld.value; continue;
      case  1 : v = rcd.Address1; break;
      case  2 : v = rcd.Address2; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


String AddressRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), AddressID); return s;}
    case  1 :return Address1;
    case  2 :return Address2;
    }

  return _T("");
  }

