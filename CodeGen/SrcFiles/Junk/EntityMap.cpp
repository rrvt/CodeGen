// Entity Map logic, Version 1.4.1
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "MapData.h"
#include "NotePad.h"


EntityTable::MyMap EntityTable::myMap;


bool EntityTable::add(EntityRecord& rcd) {
Rslt rslt;

  if (!rcd.EntityID) rcd.EntityID = maxKey + 1;

  rslt = myMap.insert(make_pair(rcd.EntityID, rcd));

  it = rslt.second ? rslt.first : myMap.end();

  if (rslt.second && rcd.EntityID > maxKey) maxKey = rcd.EntityID;

  return rslt.second;
  }


bool EntityDB::toTable(AceRecordSet& records, EntityTable& myTable) {
AceFields    fields(records);
AceFieldDsc  fld;
bool         rslt;
int          i;
variant_t    v;
EntityRecord rcd;

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    v = fld.value;
    switch (i) {
      case  0 : rcd.EntityID      = v; break;
      case  1 : rcd.FirstName     = v; break;
      case  2 : rcd.MiddleInitial = v; break;
      case  3 : rcd.LastName      = v; break;
      case  4 : rcd.Suffix        = v; break;
      case  5 : rcd.AddrID        = v; break;
      case  6 : rcd.CityStID      = v; break;
      case  7 : rcd.AddrIsPO      = v; break;
      case  8 : rcd.LocationZip   = v; break;
      case  9 : rcd.eMail         = v; break;
      case 10 : rcd.Phone1        = v; break;
      case 11 : rcd.Phone2        = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool EntityDB::toDatabase(EntityTable& myTable) {
EntityRecord* r;

  if (!maps.openRcdSet(_T("Entity"), DaoDenyWrite, rcdSet)) return false;

  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {
    if (r->isDirty()) wrt(*r);

    if (r->toDelete()) {erase(r->EntityID); myTable.erase(r->EntityID);}

    r->clearMarks();
    }

  rcdSet.close();   return true;
  }


bool EntityDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool EntityDB::wrt(EntityRecord& rcd) {
AceFields   fields(rcdSet);
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  if (!rcdSet.findRecord(rcd.EntityID))
    {String s = _T("Unable to find AddressID index with ") + rcd.EntityID; return false;}

  rcdSet.edit();      // Required to update records with new values

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    switch (i) {
      case  0 : if ((long) fld.value != rcd.EntityID) {
                  String s = _T("Update failed to find key: ") + rcd.EntityID;
                  s += _T(" found: ") + fld.value; return false;
                  }
                continue;
      case  1 : v = rcd.FirstName; break;
      case  2 : v = rcd.MiddleInitial; break;
      case  3 : v = rcd.LastName; break;
      case  4 : v = rcd.Suffix; break;
      case  5 : v = rcd.AddrID; break;
      case  6 : v = rcd.CityStID; break;
      case  7 : v = rcd.AddrIsPO; break;
      case  8 : v = rcd.LocationZip; break;
      case  9 : v = rcd.eMail; break;
      case 10 : v = rcd.Phone1; break;
      case 11 : v = rcd.Phone2; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


bool EntityDB::add(EntityRecord& rcd) {
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  rcdSet.addNew();
  AceFields fields(rcdSet);

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {

    switch (i) {
      case  0 : rcd.EntityID = fld.value; continue;
      case  1 : v = rcd.FirstName; break;
      case  2 : v = rcd.MiddleInitial; break;
      case  3 : v = rcd.LastName; break;
      case  4 : v = rcd.Suffix; break;
      case  5 : v = rcd.AddrID; break;
      case  6 : v = rcd.CityStID; break;
      case  7 : v = rcd.AddrIsPO; break;
      case  8 : v = rcd.LocationZip; break;
      case  9 : v = rcd.eMail; break;
      case 10 : v = rcd.Phone1; break;
      case 11 : v = rcd.Phone2; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


String EntityRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), EntityID); return s;}
    case  1 :return FirstName;
    case  2 :return MiddleInitial;
    case  3 :return LastName;
    case  4 :return Suffix;
    case  5 :{String s; s.format(_T("%i"), AddrID); return s;}
    case  6 :{String s; s.format(_T("%i"), CityStID); return s;}
    case  7 :{String s; s.format(_T("%i"), AddrIsPO); return s;}
    case  8 :return LocationZip;
    case  9 :return eMail;
    case 10 :return Phone1;
    case 11 :return Phone2;
    }

  return _T("");
  }

