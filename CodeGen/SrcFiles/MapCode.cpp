// Create Data Base Map Code


#include "stdafx.h"
#include "MapCode.h"
#include "NotePad.h"
#include "TableExtension.h"


void VarDeclarations::output() {
int i;

  max = 0;

  for (i = 0; i < nDecl; i++) if (decl[i].typLng > max) max = decl[i].typLng;

  for (i = 0; i < nDecl; i++) {
    VarDecl& var = decl[i];
    notePad << var.typ; addPadding(max-var.typLng + 1); notePad << var.name;
    if (var.assign.length()) notePad << _T(" = ") << var.assign;
    notePad << _T(";") << nCrlf;
    }
  }



void MapCode::createTableExtensions() {
TableDsc*      tbl;
TableExtension tableExt;

  for (tbl = tableDscrs.startLoop(); tbl; tbl = tableDscrs.nextEntry())
                                                            if (tbl->selected && !tableExt(*tbl)) break;
  }

