// Utility Functions


#include "stdafx.h"
#include "Utilities.h"
#include "NotePad.h"


void toRight(String& s) {
int lng = s.length();
  notePad << nClrTabs << nSetTab(105 - lng);
  notePad << nTab << s << nClrTabs << nCrlf;
  }



void addPadding(int n) {
int i;

  for (i = 0; i < n; i++) notePad << _T(" ");
  }





String normalizeName(String name) {
int    lng = (int) name.length();
int    x;
int    i;
int    j;
Tchar  ch;
String n;

  for (x = (int) name.find(_T(':')); x != String::npos; x = (int) name.find(_T(':'))) name[x] = _T('_');

  for (i = j = 0; i < lng; i++) {ch = name[i];   if (ch > _T(' ')) n += ch;}

  return n;
  }


String objName(String& clsName) {String s = clsName;   s[0] += _T('a') - _T('A');   return s;}

