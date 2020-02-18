// LocationPref Map logic, Version 1.4.1
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "MapData.h"
#include "NotePad.h"


LocationPrefTable::MyMap LocationPrefTable::myMap;


bool LocationPrefTable::add(LocationPrefRecord& rcd) {
Rslt rslt;

  if (!rcd.LocationPrefID) rcd.LocationPrefID = maxKey + 1;

  rslt = myMap.insert(make_pair(rcd.LocationPrefID, rcd));

  it = rslt.second ? rslt.first : myMap.end();

  if (rslt.second && rcd.LocationPrefID > maxKey) maxKey = rcd.LocationPrefID;

  return rslt.second;
  }


bool LocationPrefDB::toTable(AceRecordSet& records, LocationPrefTable& myTable) {
AceFields          fields(records);
AceFieldDsc        fld;
bool               rslt;
int                i;
variant_t          v;
LocationPrefRecord rcd;

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    v = fld.value;
    switch (i) {
      case  0 : rcd.LocationPrefID = v; break;
      case  1 : rcd.Key            = v; break;
      case  2 : rcd.Txt            = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool LocationPrefDB::toDatabase(LocationPrefTable& myTable) {
LocationPrefRecord* r;

  if (!maps.openRcdSet(_T("LocationPref"), DaoDenyWrite, rcdSet)) return false;

  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {
    if (r->isDirty()) wrt(*r);

    if (r->toDelete()) {erase(r->LocationPrefID); myTable.erase(r->LocationPrefID);}

    r->clearMarks();
    }

  rcdSet.close();   return true;
  }


bool LocationPrefDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool LocationPrefDB::wrt(LocationPrefRecord& rcd) {
AceFields   fields(rcdSet);
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  if (!rcdSet.findRecord(rcd.LocationPrefID))
    {String s = _T("Unable to find AddressID index with ") + rcd.LocationPrefID; return false;}

  rcdSet.edit();      // Required to update records with new values

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    switch (i) {
      case  0 : if ((long) fld.value != rcd.LocationPrefID) {
                  String s = _T("Update failed to find key: ") + rcd.LocationPrefID;
                  s += _T(" found: ") + fld.value; return false;
                  }
                continue;
      case  1 : v = rcd.Key; break;
      case  2 : v = rcd.Txt; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


bool LocationPrefDB::add(LocationPrefRecord& rcd) {
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  rcdSet.addNew();
  AceFields fields(rcdSet);

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {

    switch (i) {
      case  0 : rcd.LocationPrefID = fld.value; continue;
      case  1 : v = rcd.Key; break;
      case  2 : v = rcd.Txt; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


String LocationPrefRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), LocationPrefID); return s;}
    case  1 :return Key;
    case  2 :return Txt;
    }

  return _T("");
  }

