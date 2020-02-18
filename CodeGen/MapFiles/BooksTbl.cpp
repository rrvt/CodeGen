// Books Table Extension Template


#include "stdafx.h"
#include "BooksTbl.h"
#include "Utilities.h"


BooksRecord* BooksTbl::get(String& title) {
BooksRecord* r = find(title);   if (r) return r;
BooksRecord  rcd;

  rcd.Title = title;    rcd.mark();  BooksTable::add(rcd);

  toDatabase();   return find(title);
  }


BooksRecord* BooksTbl::find(String& title) {
BooksRecord* rcd;

  if (isEmpty(&title, 0)) return 0;

  for (rcd = startLoop(); rcd; rcd = nextRecord()) if (rcd->Title == title) return rcd;
  return 0;
  }

