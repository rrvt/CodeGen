// Descriptor Table and Entries


#pragma once
#include "Expandable.h"
#include "MapData.h"


//class FVEntryDoc;


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


class DescTable {
String                    name;
int                       i;
Expandable<FieldDesc, 32> desc;
int                       maxFldLng;
public:

  DescTable() : i(0), maxFldLng(0) {}
 ~DescTable() {}

  void       clear() {desc.clr();}
  int        load(Maps& maps, String& tableName);
  FieldDesc* Add() {return &desc[desc.end()];}

  String&    getName() {return name;}
  FieldDesc* getKeyDesc();

  FieldDesc* startLoop() {i = 0; return i < desc.end() ? &desc[i] : 0;}
  FieldDesc* nextDesc()  {return i+1 < desc.end() ? &desc[++i] : 0;}
  bool       last()      {return i+1 >= desc.end();}

  int        padding()   {return i   < desc.end() ? maxFldLng - desc[i].lng : 0;}
  int        maxLng()    {return maxFldLng;}
  };


struct Table {
String     fileName;
String     name;
String     cls;
String     obj;
String     rcd;
String     map;
String     myDB;
String     entry;
String     rslt;
String     iter;
String     citer;

String     keyType;
String     keyName;
int        keyIndex;

String     accTableName;

  Table(String& accessTableName, String& tblName, FieldDesc* fldDesc) :
    name(        tblName),
    fileName(    tblName + _T("Map")),
    cls(         tblName + _T("Table")),
    rcd(         tblName + _T("Record")),
    map(         tblName + _T("Map")),
    myDB(        tblName + _T("DB")),
    entry(       tblName + _T("Entry")),
    rslt(        tblName + _T("Rslt")),
    iter(        tblName + _T("Iter")),
    citer(       tblName + _T("CIter")),
    keyIndex(0),
    accTableName(accessTableName) {
      obj = cls; obj[0] += _T('a') - _T('A');

      if (fldDesc) {
        keyType  = getDbCppType(fldDesc->x);
        keyName  = fldDesc->name;
        keyIndex = fldDesc->fieldIndex;
        }
      }

private:
  Table() {}
  };

