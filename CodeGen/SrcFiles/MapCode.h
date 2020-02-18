// Map Code


#pragma once
#include "DescTable.h"
#include "MapBody.h"
#include "MapHeader.h"


class Collection;


class VarDecl {
String name;
String typ;
int    typLng;
String assign;

public:

  VarDecl() : typLng(0) {}
  VarDecl(VarDecl& fd) {copy(fd, *this);}

  void init(TCchar* varType, TCchar* varName, TCchar* asgn) {
    typ = varType; name = varName; typLng = typ.length(); if (asgn) assign = asgn;
    }

  VarDecl& operator=(VarDecl& fd) {copy(fd, *this); return *this;}

private:

  void copy(VarDecl& src, VarDecl& dst) {
    dst.name = src.name; dst.typ = src.typ; dst.typLng = src.typLng; dst.assign = src.assign;
    }

  friend class VarDeclarations;
  };


class VarDeclarations {
int                     nDecl;
Expandable <VarDecl, 8> decl;
int                     max;

public:

  VarDeclarations() : nDecl(0) {max = 0;}

  void add(TCchar* typ, TCchar* name, TCchar* asgn = 0) {decl[nDecl++].init(typ, name, asgn);}
  int  getMaxTypeLng() {return max;}
  void output();
  };


class MapCode {
DescTable  descTbl;

public:
String      key;

  MapCode() {}
 ~MapCode() {}

  int        load(String& tableName) {return descTbl.load(maps, tableName);}
  FieldDesc* getKeyDesc() {return descTbl.getKeyDesc();}

  void       createHeader(Table& table) {MapHeader mh(descTbl); mh.createFile(table);}
  void       createCpp(   Table& table) {MapBody   mb(descTbl); mb.createFile(table);}

  void       createMapDataHdr();
  void       createMapDataCpp();

  void       createMapsHdr();
  void       createMapsCpp();

  void       createTableExtensions();

private:

  void    createTblExtHdr(Collection& c);
  void    createTblExtCpp(Collection& c);
  };

