// Member Map logic, Version 1.5.3.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "MapData.h"
#include "NotePad.h"


MemberTable::MyMap MemberTable::myMap;


bool MemberTable::add(MemberRecord& rcd) {
Rslt rslt;

  if (!rcd.MemberID) rcd.MemberID = maxKey + 1;

  rslt = myMap.insert(make_pair(rcd.MemberID, rcd));

  it = rslt.second ? rslt.first : myMap.end();

  if (rslt.second && rcd.MemberID > maxKey) maxKey = rcd.MemberID;

  return rslt.second;
  }


bool MemberDB::toTable(AceRecordSet& records, MemberTable& myTable) {
AceFields    fields(records);
AceFieldDsc  fld;
bool         rslt;
int          i;
variant_t    v;
MemberRecord rcd;

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    v = fld.value;
    switch (i) {
      case  0 : rcd.MemberID            = v; break;
      case  1 : rcd.BadgeNumber         = v; break;
      case  2 : rcd.MbrEntityID         = v; break;
      case  3 : rcd.EmplEntityID        = v; break;
      case  4 : rcd.ICE_EntityID        = v; break;
      case  5 : rcd.AssgnPrefID         = v; break;
      case  6 : rcd.LocationPrefID      = v; break;
      case  7 : rcd.StatusID            = v; break;
      case  8 : rcd.CallSign            = v; break;
      case  9 : rcd.FCCExpiration       = v; break;
      case 10 : rcd.StartDate           = v; break;
      case 11 : rcd.DSWDate             = v; break;
      case 12 : rcd.BadgeExpDate        = v; break;
      case 13 : rcd.Responder           = v; break;
      case 14 : rcd.SecondaryEmail      = v; break;
      case 15 : rcd.TextMsgPh1          = v; break;
      case 16 : rcd.TextMsgPh2          = v; break;
      case 17 : rcd.HandHeld            = v; break;
      case 18 : rcd.PortMobile          = v; break;
      case 19 : rcd.PortPacket          = v; break;
      case 20 : rcd.OtherEquip          = v; break;
      case 21 : rcd.Multilingual        = v; break;
      case 22 : rcd.OtherCapabilities   = v; break;
      case 23 : rcd.Limitations         = v; break;
      case 24 : rcd.Comments            = v; break;
      case 25 : rcd.ShirtSize           = v; break;
      case 26 : rcd.IsOfficer           = v; break;
      case 27 : rcd.SkillCertifications = v; break;
      case 28 : rcd.EOC_Certifications  = v; break;
      case 29 : rcd.UpdateDate          = v; break;
      case 30 : rcd.BadgeOK             = v; break;
      case 31 : rcd.Image               = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool MemberDB::toDatabase(MemberTable& myTable) {
MemberRecord* r;

  if (!maps.openRcdSet(_T("Member"), DaoDenyWrite, rcdSet)) return false;

  for (r = myTable.startLoop(); r; r = myTable.nextRecord()) {

    if (r->toDelete()) {erase(r->MemberID); myTable.erase(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool MemberDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool MemberDB::wrt(MemberRecord& rcd) {
AceFields   fields(rcdSet);
AceFieldDsc fld;
int         i;
variant_t   v;
bool        rslt;

  if (rcdSet.findRecord(rcd.MemberID)) rcdSet.edit();
  else rcdSet.addNew();

  for (rslt = fields.startLoop(fld), i = 0; rslt; rslt = fields.nextField(fld), i++) {
    switch (i) {
      case  0 : rcd.MemberID = fld.value; continue;
      case  1 : v = rcd.BadgeNumber; break;
      case  2 : v = rcd.MbrEntityID; break;
      case  3 : v = rcd.EmplEntityID; break;
      case  4 : v = rcd.ICE_EntityID; break;
      case  5 : v = rcd.AssgnPrefID; break;
      case  6 : v = rcd.LocationPrefID; break;
      case  7 : v = rcd.StatusID; break;
      case  8 : v = rcd.CallSign; break;
      case  9 : v = rcd.FCCExpiration; break;
      case 10 : v = rcd.StartDate; break;
      case 11 : v = rcd.DSWDate; break;
      case 12 : v = rcd.BadgeExpDate; break;
      case 13 : v = rcd.Responder; break;
      case 14 : v = rcd.SecondaryEmail; break;
      case 15 : v = rcd.TextMsgPh1; break;
      case 16 : v = rcd.TextMsgPh2; break;
      case 17 : v = rcd.HandHeld; break;
      case 18 : v = rcd.PortMobile; break;
      case 19 : v = rcd.PortPacket; break;
      case 20 : v = rcd.OtherEquip; break;
      case 21 : v = rcd.Multilingual; break;
      case 22 : v = rcd.OtherCapabilities; break;
      case 23 : v = rcd.Limitations; break;
      case 24 : v = rcd.Comments; break;
      case 25 : v = rcd.ShirtSize; break;
      case 26 : v = rcd.IsOfficer; break;
      case 27 : v = rcd.SkillCertifications; break;
      case 28 : v = rcd.EOC_Certifications; break;
      case 29 : v = rcd.UpdateDate; break;
      case 30 : v = rcd.BadgeOK; break;
      case 31 : v = rcd.Image; break;
      default : return false;
      }

    fld.write(v);
    }

  return rcdSet.update() != 0;
  }


String MemberRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), MemberID); return s;}
    case  1 :{String s; s.format(_T("%i"), BadgeNumber); return s;}
    case  2 :{String s; s.format(_T("%i"), MbrEntityID); return s;}
    case  3 :{String s; s.format(_T("%i"), EmplEntityID); return s;}
    case  4 :{String s; s.format(_T("%i"), ICE_EntityID); return s;}
    case  5 :{String s; s.format(_T("%i"), AssgnPrefID); return s;}
    case  6 :{String s; s.format(_T("%i"), LocationPrefID); return s;}
    case  7 :{String s; s.format(_T("%i"), StatusID); return s;}
    case  8 :return CallSign;
    case  9 :return FCCExpiration;
    case 10 :return StartDate;
    case 11 :return DSWDate;
    case 12 :return BadgeExpDate;
    case 13 :return Responder;
    case 14 :return SecondaryEmail;
    case 15 :return TextMsgPh1;
    case 16 :return TextMsgPh2;
    case 17 :return HandHeld;
    case 18 :return PortMobile;
    case 19 :return PortPacket;
    case 20 :return OtherEquip;
    case 21 :return Multilingual;
    case 22 :return OtherCapabilities;
    case 23 :return Limitations;
    case 24 :return Comments;
    case 25 :return ShirtSize;
    case 26 :{String s; s.format(_T("%i"), IsOfficer); return s;}
    case 27 :return SkillCertifications;
    case 28 :return EOC_Certifications;
    case 29 :return UpdateDate;
    case 30 :{String s; s.format(_T("%i"), BadgeOK); return s;}
    case 31 :return Image;
    }

  return _T("");
  }

