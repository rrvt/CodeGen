// Person Table Extension Template


#include "stdafx.h"
#include "PersonTbl.h"
#include "Utilities.h"


PersonRecord* PersonTbl::get(String& firstName, String& lastName, bool isAuthor) {
PersonRecord* r = find(firstName, lastName, isAuthor);   if (r) return r;
PersonRecord  rcd;

  rcd.FirstName = firstName;    rcd.LastName = lastName;   rcd.Author = isAuthor;

  rcd.mark();  PersonTable::add(rcd);

  toDatabase();   return find(firstName, lastName, isAuthor);
  }


PersonRecord* PersonTbl::find(String& firstName, String& lastName, bool isAuthor) {
PersonRecord* rcd;

  if (isEmpty(&firstName, &lastName, 0)) return 0;

  for (rcd = startLoop(); rcd; rcd = nextRecord())
     if (rcd->FirstName == firstName && rcd->LastName == lastName && rcd->Author == isAuthor) return rcd;
  return 0;
  }

