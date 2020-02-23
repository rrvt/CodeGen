// Utility Functions


#include "stdafx.h"
#include "Utilities.h"


bool isEmpty(String* s, ...) {
va_list args;
String* p;

  if (s->size() != 0) return false;

  for (va_start(args, s);  (p = va_arg(args, String*)) && p != 0;) if (p->size() != 0) return false;

  return true;
  }

