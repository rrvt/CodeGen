// List of Fields in a Table


#pragma once
#include "DAOfields.h"
#include "Expandable.h"
#include "IterT.h"


struct FieldDsc {
String name;
String type;
bool   isIndex;
bool   isSelected;

  FieldDsc() : isIndex(false), isSelected(false) { }
  FieldDsc(FieldDsc& fd) {copy(fd);}
 ~FieldDsc() { }

 void add(DAOfield* field);

  FieldDsc& operator= (FieldDsc& fd) {copy(fd); return *this;}

private:

  void changeCase(String& name);

  void copy(FieldDsc& fd);
  };


class FieldList;
typedef IterT<FieldList, FieldDsc> FldListIter;


class FieldList {

Expandable<FieldDsc, 2> data;

public:

  FieldList() { }
 ~FieldList() { }

  void      add(DAOfield* field);
  FieldDsc* findPrimKey();

  FieldDsc* findSelected();

  int       maxLength();

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  FieldDsc* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}       // or data[i].p

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename FldListIter;
  };

