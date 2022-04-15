// Add a linear search to the table classes


#pragma once
#include "Expandable.h"
#include "Fields.h"
#include "IterT.h"


struct SrchFld  {
String    name;
FieldType type;

  SrchFld() : type(NilFld) { }
  SrchFld(SrchFld& sf) {copy(sf);}

  SrchFld& operator= (SrchFld& sf) {copy(sf); return *this;}

private:

  void copy(SrchFld& sf) {name = sf.name; type = sf.type;}
  };


class LinSrch;
typedef IterT<LinSrch, SrchFld> LSrchIter;



class LinSrch {

Expandable<SrchFld, 2> data;
int                    n;

public:

  LinSrch() : n(0) { }
 ~LinSrch() { }

  void getFields();
  void addRcdHdrFn();

  void addTblHdrFn();
  void addTblBdyFn();

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  SrchFld* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}       // or data[i].p

  int    nData()      {return data.end();}                       // returns number of data items in array

  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename LSrchIter;
  };


extern LinSrch linSrch;
