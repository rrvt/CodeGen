// Address Table


#include "stdafx.h"
#include "AdrTbl.h"
#include "NotePad.h"
#include "Utilities.h"


bool AdrTbl::load() {
AdrSetIter iter(adrSet);
AdrSet*    set;
int        count = 0;

  if (!adrSet.isOpen()) return false;

  for (set = iter(); set; set = iter++)
    {AdrRcd rcd;  rcd.load(set);   data = rcd;   if (rcd.id > maxID) maxID = rcd.id;}

  notePad << count << nCrlf; return true;
  }


void AdrRcd::load(AdrSet* set) {
  id       = set->addressID;
  address1 = set->address1;
  address2 = set->address2;
  }


void AdrTbl::store() {
AdrIter    iter(*this);
AdrRcd*    rcd;
AdrSetIter setIter(adrSet);
AdrSet*    set;

  for (rcd = iter(), set = setIter(); rcd; rcd = iter++) if (rcd->dirty) {

    set = setIter.find(rcd->id);   rcd->dirty = false;

    if (!set)        {rcd->add(adrSet); continue;}

    if (rcd->remove) {set->remove(); iter.remove();  continue;}

    rcd->store(*set);
    }
  }


void AdrRcd::store(AdrSet& set) {set.edit();     copy(set);   set.update();}
void AdrRcd::add(  AdrSet& set) {set.addNew();   copy(set);   set.update();}


void AdrRcd::copy(AdrSet& set) {
  set.addressID = id;
  set.address1  = address1;
  set.address2  = address2;
  }


AdrRcd* AdrTbl::add(AdrRcd& rcd) {rcd.id = ++maxID;  rcd.dirty = true;  return data = rcd;}


void AdrTbl::display() {
AdrIter iter(*this);
AdrRcd* rcd;

  setTabs();

  notePad << _T("Address Table") << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) rcd->display();
  }


void AdrRcd::display() {
  notePad << nTab << id;
  notePad << nTab << address1;
  notePad << nTab << address2;
  notePad << nCrlf;
  }


static const int nTabs = 10;


void AdrTbl::setTabs() {
AdrIter iter(*this);
AdrRcd* rcd;
int     max;
int     nFldsLn;
int     tabs[nTabs];
int     tab;
int     i;
int     n;

  for (max = 0, rcd = iter(); rcd; rcd = iter++) {
    maxLng(rcd->address1, max);
    maxLng(rcd->address2, max);
    }

  n = 90 / max;

  nFldsLn = n < 2 ? n : 2;

  for (i = 0; i < nTabs; i++) tabs[i] = 0;

  for (i = 0, rcd = iter(); rcd; i = 0, rcd = iter++) {
    maxLng(rcd->address1, tabs[i]);   i = (i + 1) % nFldsLn;
    maxLng(rcd->address2, tabs[i]);   i = (i + 1) % nFldsLn;
    }

  tab = 4;
  notePad << nClrTabs << nSetRTab(tab) << nSetTab(tab += 2);

  for (i = 0; i < nTabs && tabs[i]; i++) {
    tab += tabs[i] + 2;   notePad << nSetTab(tab);
    }
  }


