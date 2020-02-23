// Person Map logic, Version 1.5.4.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "MapData.h"
#include "NotePad.h"


PersonTable::MyMap PersonTable::myMap;


bool PersonTable::add(PersonRecord& rcd) {
Rslt rslt;

  if (!rcd.ID) rcd.ID = maxKey + 1;

  rslt = myMap.insert(make_pair(rcd.ID, rcd));

  it = rslt.second ? rslt.first : myMap.end();

  if (rslt.second && rcd.ID > maxKey) maxKey = rcd.ID;

  return rslt.second;
  }


bool PersonDB::toTable(AceRecordSet& records, PersonTable& myTable) {
AceFields    fields(records);
AceFieldDsc  fld;
bool         rslt;
int          i;
variant_t    v;
PersonRecord rcd;

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    v = fld.value;
    switch (i) {
      case  0 : rcd.ID        = v; break;
      case  1 : rcd.FirstName = v; break;
      case  2 : rcd.LastName  = v; break;
      case  3 : rcd.Author    = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool PersonDB::toDatabase(PersonTable& myTable) {
PersonRecord* r;

  if (!maps.openRcdSet(_T("Person"), DaoDenyWrite, rcdSet)) return false;

  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {

    if (r->toDelete()) {erase(r->ID); myTable.erase(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool PersonDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool PersonDB::wrt(PersonRecord& rcd) {
AceFields   fields(rcdSet);
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  if (rcdSet.findRecord(rcd.ID)) rcdSet.edit();
  else rcdSet.addNew();

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    switch (i) {
      case  0 : rcd.ID = fld.value; continue;
      case  1 : v = rcd.FirstName; break;
      case  2 : v = rcd.LastName; break;
      case  3 : v = rcd.Author; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


String PersonRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), ID); return s;}
    case  1 :return FirstName;
    case  2 :return LastName;
    case  3 :{String s; s.format(_T("%i"), Author); return s;}
    }

  return _T("");
  }

