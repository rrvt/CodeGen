// Utilities


#include "pch.h"
#include "Capitalize.h"


static String s;

String& capitalize(TCchar* tc) {

  s = tc ? tc : _T("");

  Tchar& ch = s[0];    if (ch < _T('A') || _T('Z') < ch) ch += _T('A') - _T('a');   return s;
  }


String& notCaped(TCchar* tc) {

  s = tc ? tc : _T("");

  Tchar& ch = s[0];   if (_T('A') <= ch && ch <= _T('Z')) ch +=  _T('a') - _T('A');   return s;
  }

