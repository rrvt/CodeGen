// Variable Declarations


#pragma once
#include "Expandable.h"


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

  void clear() {nDecl = max = 0; decl.clear();}

  void add(TCchar* typ, TCchar* name, TCchar* asgn = 0) {decl[nDecl++].init(typ, name, asgn);}
  int  getMaxTypeLng() {return max;}
  void output();
  };

