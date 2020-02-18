// AssgnPref Map logic, Version 1.5.3.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "MapData.h"
#include "NotePad.h"


AssgnPrefTable::MyMap AssgnPrefTable::myMap;


bool AssgnPrefTable::add(AssgnPrefRecord& rcd) {
Rslt rslt;

  if (!rcd.AssgnPrefID) rcd.AssgnPrefID = maxKey + 1;

  rslt = myMap.insert(make_pair(rcd.AssgnPrefID, rcd));

  it = rslt.second ? rslt.first : myMap.end();

  if (rslt.second && rcd.AssgnPrefID > maxKey) maxKey = rcd.AssgnPrefID;

  return rslt.second;
  }


bool AssgnPrefDB::toTable(AceRecordSet& records, AssgnPrefTable& myTable) {
AceFields       fields(records);
AceFieldDsc     fld;
bool            rslt;
int             i;
variant_t       v;
AssgnPrefRecord rcd;

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    v = fld.value;
    switch (i) {
      case  0 : rcd.AssgnPrefID = v; break;
      case  1 : rcd.APKey       = v; break;
      case  2 : rcd.Txt         = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool AssgnPrefDB::toDatabase(AssgnPrefTable& myTable) {
AssgnPrefRecord* r;

  if (!maps.openRcdSet(_T("AssgnPref"), DaoDenyWrite, rcdSet)) return false;

  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {

    if (r->toDelete()) {erase(r->AssgnPrefID); myTable.erase(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool AssgnPrefDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool AssgnPrefDB::wrt(AssgnPrefRecord& rcd) {
AceFields   fields(rcdSet);
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  if (rcdSet.findRecord(rcd.AssgnPrefID)) rcdSet.edit();
  else rcdSet.addNew();

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    switch (i) {
      case  0 : rcd.AssgnPrefID = fld.value; continue;
      case  1 : v = rcd.APKey; break;
      case  2 : v = rcd.Txt; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


String AssgnPrefRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), AssgnPrefID); return s;}
    case  1 :return APKey;
    case  2 :return Txt;
    }

  return _T("");
  }

