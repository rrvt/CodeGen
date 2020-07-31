// Descriptor Table and Entries


#pragma once
#include "Expandable.h"
#include "MapData.h"


struct FieldDesc {
int          fieldIndex;
String       name;
int          lng;
_variant_t   v;
DataTypeEnum x;
bool         isIndex;

  FieldDesc() : fieldIndex(0), lng(0), v(), x(dbBoolean), isIndex(false) {}
  FieldDesc(FieldDesc& fd) {copy(fd, *this);}
  FieldDesc& operator=(FieldDesc& fd) {copy(fd, *this); return *this;}

private:

  void copy(FieldDesc& src, FieldDesc& dst)
      {dst.name = src.name; dst.lng = src.lng; dst.v = src.v; dst.x = src.x; dst.isIndex = src.isIndex;}
  };


class DescTable;
typedef IterT<DescTable, FieldDesc> DTIter;


class DescTable {
String                    name;
int                       i;
Expandable<FieldDesc, 32> desc;
int                       maxFldLng;
public:

  DescTable() : i(0), maxFldLng(0) {}
  DescTable(TCchar* tableName) {load(maps, tableName);}
 ~DescTable() {}

  void       clear() {desc.clr();}
  int        load(Maps& maps, TCchar* tableName);
  FieldDesc* Add() {return &desc[desc.end()];}

  String&    getName() {return name;}
  FieldDesc* getKeyDesc();

  int        padding()   {return i   < desc.end() ? maxFldLng - desc[i].lng : 0;}
  int        maxLng()    {return maxFldLng;}

private:

  // returns either a pointer to data (or datum) at index i in array or zero
  FieldDesc* datum(int i) {return 0 <= i && i < nData() ? &desc[i] : 0;}

  // returns number of data items in array
  int   nData()      {return desc.end();}

  friend typename DTIter;
  };






