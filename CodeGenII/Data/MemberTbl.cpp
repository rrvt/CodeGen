// Member Table


#include "stdafx.h"
#include "MemberTbl.h"
#include "DAOfields.h"
#include "DAOrecords.h"
#include "NotePad.h"
#include "Utilities.h"


bool MemberTbl::load(DAOtable* daoTable) {
DAOrcdsIter iter(daoTable);
FieldsP     fields;
int         count;

  for (count = 0, fields = iter(DAOdenyWrite); fields; count++, fields = iter++) {
    MemberRcd rcd;   rcd.load(fields);   data = rcd;
    }

  notePad << count << nCrlf; return true;
  }


void MemberRcd::load(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   dsc;
variant_t   v;

  for (dsc = iter(); dsc; dsc = iter++) {
    v = dsc->value();
    switch (iter.index()) {
      case  0: id                  = v; break;
      case  1: badgeNumber         = v; break;
      case  2: mbrEntityID         = v; break;
      case  3: emplEntityID        = v; break;
      case  4: ice_EntityID        = v; break;
      case  5: assgnPrefID         = v; break;
      case  6: locationPrefID      = v; break;
      case  7: statusID            = v; break;
      case  8: callSign            = v; break;
      case  9: fccExpiration       = v; break;
      case 10: startDate           = v; break;
      case 11: dswDate             = v; break;
      case 12: badgeExpDate        = v; break;
      case 13: responder           = v; break;
      case 14: secondaryEmail      = v; break;
      case 15: textMsgPh1          = v; break;
      case 16: textMsgPh2          = v; break;
      case 17: handHeld            = v; break;
      case 18: portMobile          = v; break;
      case 19: portPacket          = v; break;
      case 20: otherEquip          = v; break;
      case 21: multilingual        = v; break;
      case 22: otherCapabilities   = v; break;
      case 23: limitations         = v; break;
      case 24: comments            = v; break;
      case 25: shirtSize           = v; break;
      case 26: isOfficer           = v; break;
      case 27: skillCertifications = v; break;
      case 28: eoc_Certifications  = v; break;
      case 29: updateDate          = v; break;
      case 30: badgeOK             = v; break;
      case 31: image               = v; break;
      default: throw _T("Member Record Error");
      }
    }
  }


void MemberTbl::store() {
DAOtable*  daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate Member Table");
DAOrcds    daoRcds(daoTbl);
FieldsP    fieldsP;
MbrIter    iter(*this);
MemberRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {

    if (rcd->isDeleted() && daoRcds.findRecord(rcd->id))
                                                       {daoRcds.delCurRcd();   iter.remove();   continue;}
    if (!rcd->isDirty()) continue;

    fieldsP = daoRcds.findRecord(rcd->id);   if (!fieldsP) continue;    // Add new records with addNewRcd

    daoRcds.edit();   rcd->store(fieldsP);   daoRcds.update();   rcd->clearMark();
    }
  }


MemberRcd* MemberTbl::add(MemberRcd& rcd) {
DAOtable* daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate Member Table");
DAOrcds   daoRcds(daoTbl);
FieldsP   fieldsP;

  fieldsP = daoRcds.findRecord(rcd.id);   if (fieldsP) return 0;

  fieldsP = daoRcds.addNew();   rcd.store(fieldsP);  daoRcds.update();  rcd.clearMark();

  return data = rcd;
  }


void MemberRcd::store(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   field;
variant_t   v;

  for (field = iter(); field; field = iter++) {
    switch (iter.index()) {
      case  0: id = field->value(); continue;
      case  1: v  = badgeNumber; break;
      case  2: v  = mbrEntityID; break;
      case  3: v  = emplEntityID; break;
      case  4: v  = ice_EntityID; break;
      case  5: v  = assgnPrefID; break;
      case  6: v  = locationPrefID; break;
      case  7: v  = statusID; break;
      case  8: v  = callSign; break;
      case  9: v  = fccExpiration; break;
      case 10: v  = startDate; break;
      case 11: v  = dswDate; break;
      case 12: v  = badgeExpDate; break;
      case 13: v  = responder; break;
      case 14: v  = secondaryEmail; break;
      case 15: v  = textMsgPh1; break;
      case 16: v  = textMsgPh2; break;
      case 17: v  = handHeld; break;
      case 18: v  = portMobile; break;
      case 19: v  = portPacket; break;
      case 20: v  = otherEquip; break;
      case 21: v  = multilingual; break;
      case 22: v  = otherCapabilities; break;
      case 23: v  = limitations; break;
      case 24: v  = comments; break;
      case 25: v  = shirtSize; break;
      case 26: v  = isOfficer; break;
      case 27: v  = skillCertifications; break;
      case 28: v  = eoc_Certifications; break;
      case 29: v  = updateDate; break;
      case 30: v  = badgeOK; break;
      case 31: v  = image; break;
      default: throw _T("Member Record Error");
      }

    *field = v;
    }
  }


void MemberTbl::display() {
MbrIter    iter(*this);
MemberRcd* rcd;

  setTabs();

  notePad << _T("Member Table") << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) rcd->display();
  }


void MemberRcd::display() {
  notePad << nTab << callSign;
  notePad << nTab << badgeNumber;
  notePad << nCrlf;
  }


void MemberTbl::setTabs() {
MbrIter    iter(*this);
MemberRcd* rcd;
int        tab0 = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    maxLng(rcd->callSign, tab0);
    }

  notePad << nClrTabs;
  notePad << nSetRTab(tab0) << nSetTab(tab0 + 2);
  }

