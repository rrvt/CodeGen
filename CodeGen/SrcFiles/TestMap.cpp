// Test Map Template


#include "stdafx.h"
#include "TestMap.h"
#include "MapData.h"


MyTable::MyMap MyTable::myMap;


bool MyTable::add(const Record& rcd) {
Rslt rslt;

  rslt = myMap.insert(make_pair(rcd.key, rcd));

  it = rslt.second ? rslt.first : myMap.end();   if (rslt.second && rcd.key > maxKey) maxKey = rcd.key;

  return rslt.second;
  }


#if 0
bool MyTable::update(const long oldKey, Record& rcd) {
Iter x = prev(it);

  if (!erase(oldKey)) return false;   rcd.newRcd = false;   if (!add(rcd)) return false;

  it = x; return true;
  }
#endif


bool MyDB::toTable(AceRecordSet& records, MyTable& myTable) {
AceFields     fields(records);
AceFieldDsc   fld;
bool          rslt;
int           i;
variant_t     v;
Record        rcd;

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    v = fld.value;
    switch (i) {
      case  0 : rcd.key   = v; break;
      case  1 : rcd.fld1  = v; break;
      case  2 : rcd.fld2  = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool MyDB::toDatabase(MyTable& myTable) {
Record* r;

  if (!maps.openRcdSet(_T("MyTable"), DaoDenyWrite, rcdSet)) return false;

  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {
    if (r->isDirty()) wrt(*r);
    if (r->toDelete()) {erase(r->key);            myTable.erase(r->key);}
    r->clearMarks();
    }

  rcdSet.close();   return true;
  }


bool MyDB::erase(long key) {return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();}


bool MyDB::wrt(Record& src) {
AceFields   fields(rcdSet);
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  if (!rcdSet.findRecord(src.key))
              {String s = _T("Unable to find AddressID index with ") + src.key; return false;}

  rcdSet.edit();                               // Required to update records with new values

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {

    switch (i) {
      case  0 : if ((long)fld.value != src.key) {
                  String s = _T("Update failed to find key: ") + src.key;
                  s += _T(" found: ") + fld.value; return false;
                  }
                continue;

      case  1 : v             = src.fld1; break;
      case  2 : v             = src.fld2; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


bool MyDB::add(Record& rcd) {
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  rcdSet.addNew();   AceFields fields(rcdSet);

    for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {

      switch (i) {
        case  0 : rcd.key = fld.value; continue;
        case  1 : v = rcd.fld1; break;
        case  2 : v = rcd.fld2; break;
        default : return false;
        }

      fld.write(v);
      }

  return rcdSet.update() != 0;
  }

