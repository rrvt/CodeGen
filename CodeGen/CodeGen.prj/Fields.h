// Names of each field in the table


#pragma once
#include "ExpandableP.h"
#include "IterT.h"

class AccFldDsc;


enum FieldType {NilFld, IdxFld, IntFld, StgFld, LongStgFld, BoolFld, UnkFld};


class Field {
public:

String    name;
FieldType type;
String    typeName;
long      length;
bool      isIndex;
bool      isSelected;


  Field() : type(NilFld), isIndex(false), isSelected(false) { }
 ~Field() { }

  void load(AccFldDsc* dsc);

  void display();
  };


class Fields;
typedef DatumPtrT<Field, int> FieldP;                     // Usually defined just before iterator
typedef IterT<Fields, Field>  FldsIter;


class Fields {
ExpandableP<Field, int, FieldP, 2> data;

public:
String table;

  Fields() { }
 ~Fields() { }

  bool load(TCchar* path, TCchar* table);

  int    nData()      {return data.end();}                // returns number of data items in array

  String getArgList(int& n);
  String getArgsComp();
  String getArgs();

  void display();

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  Field* datum(int i) {return 0 <= i && i < nData() ? data[i] : 0;}

  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename FldsIter;
  };


extern Fields fields;
