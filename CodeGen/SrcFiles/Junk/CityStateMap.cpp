// CityState Map logic, Version 1.4.1
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "MapData.h"
#include "NotePad.h"


CityStateTable::MyMap CityStateTable::myMap;


bool CityStateTable::add(CityStateRecord& rcd) {
Rslt rslt;

  if (!rcd.CityStateID) rcd.CityStateID = maxKey + 1;

  rslt = myMap.insert(make_pair(rcd.CityStateID, rcd));

  it = rslt.second ? rslt.first : myMap.end();

  if (rslt.second && rcd.CityStateID > maxKey) maxKey = rcd.CityStateID;

  return rslt.second;
  }


bool CityStateDB::toTable(AceRecordSet& records, CityStateTable& myTable) {
AceFields       fields(records);
AceFieldDsc     fld;
bool            rslt;
int             i;
variant_t       v;
CityStateRecord rcd;

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    v = fld.value;
    switch (i) {
      case  0 : rcd.CityStateID = v; break;
      case  1 : rcd.City        = v; break;
      case  2 : rcd.State       = v; break;
      case  3 : rcd.Zip         = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool CityStateDB::toDatabase(CityStateTable& myTable) {
CityStateRecord* r;

  if (!maps.openRcdSet(_T("CityState"), DaoDenyWrite, rcdSet)) return false;

  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {
    if (r->isDirty()) wrt(*r);

    if (r->toDelete()) {erase(r->CityStateID); myTable.erase(r->CityStateID);}

    r->clearMarks();
    }

  rcdSet.close();   return true;
  }


bool CityStateDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool CityStateDB::wrt(CityStateRecord& rcd) {
AceFields   fields(rcdSet);
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  if (!rcdSet.findRecord(rcd.CityStateID))
    {String s = _T("Unable to find AddressID index with ") + rcd.CityStateID; return false;}

  rcdSet.edit();      // Required to update records with new values

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    switch (i) {
      case  0 : if ((long) fld.value != rcd.CityStateID) {
                  String s = _T("Update failed to find key: ") + rcd.CityStateID;
                  s += _T(" found: ") + fld.value; return false;
                  }
                continue;
      case  1 : v = rcd.City; break;
      case  2 : v = rcd.State; break;
      case  3 : v = rcd.Zip; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


bool CityStateDB::add(CityStateRecord& rcd) {
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  rcdSet.addNew();
  AceFields fields(rcdSet);

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {

    switch (i) {
      case  0 : rcd.CityStateID = fld.value; continue;
      case  1 : v = rcd.City; break;
      case  2 : v = rcd.State; break;
      case  3 : v = rcd.Zip; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


String CityStateRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), CityStateID); return s;}
    case  1 :return City;
    case  2 :return State;
    case  3 :return Zip;
    }

  return _T("");
  }

