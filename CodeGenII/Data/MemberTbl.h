// MemberTable


#pragma once
#include "DBtables.h"
#include "DAOfields.h"
#include "ExpandableP.h"


class MemberRcd : public DBrcd {
public:
long   badgeNumber;
long   mbrEntityID;
long   emplEntityID;
long   ice_EntityID;
long   assgnPrefID;
long   locationPrefID;
long   statusID;
String callSign;
String fccExpiration;
String startDate;
String dswDate;
String badgeExpDate;
String responder;
String secondaryEmail;
String textMsgPh1;
String textMsgPh2;
String handHeld;
String portMobile;
String portPacket;
String otherEquip;
String multilingual;
String otherCapabilities;
String limitations;
String comments;
String shirtSize;
bool   isOfficer;
String skillCertifications;
String eoc_Certifications;
String updateDate;
bool   badgeOK;
String image;

  MemberRcd() : DBrcd(), badgeNumber(0), mbrEntityID(0), emplEntityID(0), ice_EntityID(0),
                assgnPrefID(0), locationPrefID(0), statusID(0), isOfficer(false), badgeOK(false) { }
 ~MemberRcd() { }

          void load(FieldsP fields);
          void store(FieldsP fields);

  virtual void display();

  // Needed for Insertion Sort of Primary Key
  bool operator== (MemberRcd& r) {return callSign == r.callSign;}
  bool operator>= (MemberRcd& r) {return callSign >= r.callSign;}

  // Needed for Binary Search of Primary Key
  bool operator== (TCchar* callSign) {return this->callSign == callSign;}
  bool operator<  (TCchar* callSign) {return this->callSign <  callSign;}
  bool operator>  (TCchar* callSign) {return this->callSign >  callSign;}

  // Needed for Linear Search with one or more arguments
  bool operator== (long badgeNumber) {return this->badgeNumber == badgeNumber;}
  };


// Iterator Declaration, see IterT.h for details
class MemberTbl;
typedef IterT<MemberTbl, MemberRcd> MbrIter;

// Record Pointer Declaration, see ExpandableP.h for details
typedef RcdPtrT<MemberRcd> MemberRcdP;


class MemberTbl : public DBtable {

ExpandableP<MemberRcd, MemberRcdP, 2> data;

public:

  MemberTbl() : DBtable(_T("Member")) {dbTables = this;}
 ~MemberTbl() { }

  virtual bool operator== (TCchar* name) {return this->name == name;}

          void clear() {data.clear();}
          bool load(DAOtable* daoTable);  // load database table into memory, does not use addNewRcd.

    MemberRcd* add(MemberRcd& rcd);     // Add a new record to table and database
          void store();

    MemberRcd* find(TCchar* callSign) {return data.bSearch(callSign);}
    MemberRcd* find(long badgeNumber) {return data.find(badgeNumber);}

  virtual void display();

  virtual void setTabs();
private:

// returns either a pointer to data (or datum) at index i in array or zero

  MemberRcd* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename MbrIter;
  };


  extern MemberTbl memberTbl;

