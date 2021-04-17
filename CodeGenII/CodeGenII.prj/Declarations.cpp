// Variable Declarations


#include "stdafx.h"
#include "Declarations.h"
#include "NotePad.h"
#include "Utilities.h"


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

