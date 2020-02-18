// Status Map logic, Version 1.5.3.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "MapData.h"
#include "NotePad.h"


StatusTable::MyMap StatusTable::myMap;


bool StatusTable::add(StatusRecord& rcd) {
Rslt rslt;

  if (!rcd.StsID) rcd.StsID = maxKey + 1;

  rslt = myMap.insert(make_pair(rcd.StsID, rcd));

  it = rslt.second ? rslt.first : myMap.end();

  if (rslt.second && rcd.StsID > maxKey) maxKey = rcd.StsID;

  return rslt.second;
  }


bool StatusDB::toTable(AceRecordSet& records, StatusTable& myTable) {
AceFields    fields(records);
AceFieldDsc  fld;
bool         rslt;
int          i;
variant_t    v;
StatusRecord rcd;

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    v = fld.value;
    switch (i) {
      case  0 : rcd.StsID        = v; break;
      case  1 : rcd.Abbreviation = v; break;
      case  2 : rcd.Description  = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool StatusDB::toDatabase(StatusTable& myTable) {
StatusRecord* r;

  if (!maps.openRcdSet(_T("Status"), DaoDenyWrite, rcdSet)) return false;

  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {

    if (r->toDelete()) {erase(r->StsID); myTable.erase(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool StatusDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool StatusDB::wrt(StatusRecord& rcd) {
AceFields   fields(rcdSet);
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  if (rcdSet.findRecord(rcd.StsID)) rcdSet.edit();
  else rcdSet.addNew();

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    switch (i) {
      case  0 : rcd.StsID = fld.value; continue;
      case  1 : v = rcd.Abbreviation; break;
      case  2 : v = rcd.Description; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


String StatusRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), StsID); return s;}
    case  1 :return Abbreviation;
    case  2 :return Description;
    }

  return _T("");
  }

