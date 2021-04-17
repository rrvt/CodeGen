// Variable Declarations


#pragma once
#include "Expandable.h"
#include "IterT.h"


class Declaration {
String name;
String typ;
String assign;
int    typLng;
int    objLng;

public:

  Declaration() : typLng(0), objLng(0) {}
  Declaration(Declaration& fd) {copy(fd, *this);}

  void init(TCchar* varType, TCchar* varName, TCchar* asgn) {
    typ = varType; name = varName; typLng = typ.length();
    if (asgn) {assign = asgn;  objLng = name.length();}
    }

  Declaration& operator=(Declaration& fd) {copy(fd, *this); return *this;}

private:

  void copy(Declaration& src, Declaration& dst) {
    dst.name = src.name; dst.typ = src.typ; dst.typLng = src.typLng; dst.assign = src.assign;
    }

  friend class Declarations;
  };


class Declarations;
typedef IterT<Declarations, Declaration> DeclsIter;


class Declarations {
Expandable <Declaration, 8> data;
int                         maxTyp;
int                         maxObj;

public:

  Declarations() : maxTyp(0), maxObj(0) {}

  void clear() {maxObj = maxTyp = 0; data.clear();}

  void add(TCchar* typ, TCchar* name, TCchar* asgn = 0) {data.nextData().init(typ, name, asgn);}
  int  getMaxTypeLng() {return maxTyp;}
  void output();

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  Declaration* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}       // or data[i].p

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename DeclsIter;
  };

