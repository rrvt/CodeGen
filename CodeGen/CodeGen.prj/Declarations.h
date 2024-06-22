// Variable Declarations


#pragma once
#include "Expandable.h"
#include "Fields.h"
#include "IterT.h"


class Declaration {
String name;
String typ;
String assign;
int    typLng;
int    objLng;

public:

  Declaration() : typLng(0), objLng(0) {}
  Declaration(Declaration& fd) {copy(fd);}

  void init(FieldType varType, TCchar* varName, TCchar* asgn);
  void init(TCchar*   varType, TCchar* varName, TCchar* asgn);

  Declaration& operator=(Declaration& fd) {copy(fd); return *this;}

private:

  void copy(Declaration& src);
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

  void add(FieldType typ, TCchar* name, TCchar* asgn = 0) {data.nextData().init(typ, name, asgn);}
  void add(TCchar*   typ, TCchar* name, TCchar* asgn = 0) {data.nextData().init(typ, name, asgn);}
  int  getMaxTypeLng() {return maxTyp;}
  void output();

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  Declaration* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}       // or data[i].p

  int   nData()      {return data.end();}                 // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename DeclsIter;
  };

