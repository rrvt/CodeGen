// Variable Declarations


#include "pch.h"
#include "Declarations.h"
#include "NotePad.h"
#include "Utilities.h"


void Declaration::init(FieldType varType, TCchar* varName, TCchar* asgn) {
  switch (varType) {
    case IdxFld     :
    case IntFld     : typ = _T("int");     break;
    case StgFld     :
    case LongStgFld : typ = _T("Cstring"); break;
    case BoolFld    : typ = _T("BOOL");    break;
    default         : typ = _T("Cstring"); break;
    }

  name   = varName;
  typLng = typ.length();
  if (asgn) {assign = asgn;  objLng = name.length();}
  }


void Declaration::init(TCchar* varType, TCchar* varName, TCchar* asgn) {
  typ  = varType;  typLng = typ.length();
  name = varName;
  if (asgn) {assign = asgn;  objLng = name.length();}
  }



void Declaration::copy(Declaration& src) {
    name   = src.name;
    typ    = src.typ;
    assign = src.assign;
    typLng = src.typLng;
    objLng = src.objLng;
    }



void Declarations::output() {
DeclsIter    iter(*this);
Declaration* decl;

  maxObj = maxTyp = 0;

  for (decl = iter(); decl; decl = iter++) {
    if (decl->typLng > maxTyp) maxTyp = decl->typLng;
    if (decl->objLng > maxObj) maxObj = decl->objLng;
    }

  maxTyp++;   maxObj++;

  for (decl = iter(); decl; decl = iter++) {
    notePad << addTab(decl->typ, maxTyp);


    if (!decl->assign.isEmpty()) {
      notePad << addTab(decl->name, maxObj);
      notePad << _T("= ") << decl->assign;
      }
    else notePad << decl->name;

    notePad << _T(";") << nCrlf;
    }
  }

