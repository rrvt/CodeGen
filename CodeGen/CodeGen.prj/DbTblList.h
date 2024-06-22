// Database Table List


#pragma once
#include "Expandable.h"
#include "Fields.h"
#include "IterT.h"



class TblItem {
public:

String    name;
String    abbr;
String    primKey;
FieldType pKeyType;
bool      selected;

  TblItem() : selected(false) { }
  TblItem(TblItem& ti) {copy(ti);}
 ~TblItem() { }

  void load(TCchar* name);
  void getPKey();

  void setAbbr(TCchar* abbr);

  TblItem& operator=(TblItem& ti) {copy(ti); return *this;}

  bool operator>= (TblItem& tbl) {return name >= tbl.name;}
  bool operator== (TblItem& tbl) {return name == tbl.name;}

  bool operator== (TCchar* name) {return this->name == name;}
  bool operator<  (TCchar* name) {return this->name <  name;}
  bool operator>  (TCchar* name) {return this->name >  name;}

private:

  void    setPKey(  TCchar*   primKey);
  void    setPKType(FieldType pKeyType);
  void    getAbbr();
  void    loadPKey();
  String& sect(String& s) {s = name + _T("Sect");   return s;}

  void copy(TblItem& ti);
  };


typedef Expandable<TblItem, 2> TableData;

class DbTblList;
typedef IterT<DbTblList, TblItem> DbTblIter;


class DbTblList {

TableData data;

public:

  DbTblList() { }
 ~DbTblList() { }

  void     load(TCchar* path);

  TblItem* find(TCchar* name) {return data.bSearch(name);}

  void     display();

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  TblItem* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}       // or data[i].p

  int    nData()      {return data.end();}                // returns number of data items in array

  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename DbTblIter;
  };


extern DbTblList dbTblList;

