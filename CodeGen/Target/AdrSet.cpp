// AdrSet Record


#include "stdafx.h"
#include "AdrSet.h"
#include "AccessDB.h"


AdrSet::AdrSet() : AccRcdSet(accessDB.db()), addressID(0), address1(), address2() { }


bool AdrSet::open(TCchar* path) {

  opened = false;

  if (!accessDB.isOpen() && !accessDB.open(path)) return false;

  SetState(CRecordset::dynaset, NULL, CRecordset::none);          // Cache state info and allocate hstmt

  if (!AllocHstmt()) return false;

  try {
    OnSetOptions(m_hstmt);   AllocStatusArrays();   m_nFields = 3;

    if (!Open(dynaset, _T("Address"), CRecordset::none)) return false;

    AllocRowset();          // Allocate memory and cache info
    }
  catch(...) {Close(); return false;}

  return opened = true;
  }


AdrSet* AdrSetIter::find(int id) {
AdrSet* set = &rcd;

  for ( ; set && set->addressID <= id; set = (*this)++) if (set->addressID == id) return set;
  for ( ; set && set->addressID >= id; set = (*this)--) if (set->addressID == id) return set;

  return 0;
  }


bool AdrSet::edit()
  {if (!opened) return false;   try {Edit(); return true;} catch(...) {return false;}}


bool AdrSet::addNew()
  {if (!opened) return false;   try {AddNew(); return true;} catch(...) {return false;}}


bool AdrSet::update()
  {if (!opened) return false;   try {Update(); movePrev(); return true;} catch(...) {return false;}}


bool AdrSet::remove()
  {if (!opened) return false;   try {Delete(); movePrev(); return true;} catch(...) {return false;}}


void AdrSet::DoFieldExchange(CFieldExchange* pFX) {

  pFX->SetFieldType(CFieldExchange::outputColumn);

  RFX_Int( pFX, _T("AddressID"), addressID);
  RFX_Text(pFX, _T("Address1"),  address1);
  RFX_Text(pFX, _T("Address2"),  address2);
  }
