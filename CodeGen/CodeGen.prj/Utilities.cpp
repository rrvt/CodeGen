// Utilities


#include "stdafx.h"
#include "Utilities.h"
#include "Date.h"
#include "NotePad.h"


static String blks = _T("          ");

static String tryFreq(TCchar* p);
static bool   getFactor(double& posFact, Tchar ch, Tchar baseCh);





void createCopyright(TCchar* name, TCchar* version) {
  notePad << _T("// ") << name << _T(" Map logic, Version ") << version << nCrlf;
  notePad << _T("// Copyright Bob -- K6RWY, 2019.  ");
  notePad << _T("All rights reserved.") << nCrlf << nCrlf;
  }



void toRight(String& s) {
int lng = s.length();
  notePad << nClrTabs << nSetTab(105 - lng);
  notePad << nTab << s << nClrTabs << nCrlf;
  }



void addPadding(int n) {
int i;

  for (i = 0; i < n; i++) notePad << _T(" ");
  }



String addTab(String& s, int max) {int n = max - s.length(); return s + blks.substr(0, n);}


String normalizeDate(TCchar* date) {
String s  = date ? date : _T("");   if (s.isEmpty()) return s;
Date   dt = s;

  s = dt.format(_T("%D"));  return s;
  }

String normalizeTime(TCchar* time) {
String s  = time ? time : _T("");   if (s.isEmpty()) return s;
Date   dt = s;

  s = dt.format(_T("%R"));  return s;
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


String objName(String& clsName) {
String s = clsName;
Tchar& ch = s[0];
    if (_T('A') <= ch && ch <= _T('Z')) {s[0] += _T('a') - _T('A');   return s;}
    return s;
    }


String getDateNow() {Date dt;   dt.getToday();   return dt.format(_T("%D"));}

String getTimeNow() {Date dt;   dt.getToday();   return dt.format(_T("%R"));}



static TCchar vowel[] = {_T('a'), _T('e'), _T('i'), _T('o'), _T('u'),
                         _T('A'), _T('E'), _T('I'), _T('O'), _T('U')};

static bool isVowel(Tchar ch);


// Find a 4 character abbreviation from a name.  Use it as a suggestion for the user.

String findAbbr(TCchar* p) {
String t = p;
int    lng = t.length();
String s;
int    i;
Tchar  ch;

  for (i = lng-1; i > 0; i--) {
    ch = t[i];

    if (isVowel(ch)) {s = t.substr(0, i); t = s + t.substr(i+1);}

    if (t.length() == 4) return t;
    }

  while (t.length() > 4) t = tryFreq(t);

  return t;
  }


bool isVowel(Tchar ch) {
int i;
int n = noElements(vowel);

  for (i = 0; i < n; i++) if (ch == vowel[i]) return true;

  return false;
  }


struct LetterFreq {
TCchar ch;
double freq;
};

static LetterFreq freqList[] = {{_T('a'), 8.497 },
                                {_T('b'), 1.492 },
                                {_T('c'), 2.202 },
                                {_T('d'), 4.253 },
                                {_T('e'), 11.162},
                                {_T('f'), 2.228 },
                                {_T('g'), 2.015 },
                                {_T('h'), 6.094 },
                                {_T('i'), 7.546 },
                                {_T('j'), 0.153 },
                                {_T('k'), 1.292 },
                                {_T('l'), 4.025 },
                                {_T('m'), 2.406 },
                                {_T('n'), 6.749 },
                                {_T('o'), 7.507 },
                                {_T('p'), 1.929 },
                                {_T('q'), 0.095 },
                                {_T('r'), 7.587 },
                                {_T('s'), 6.327 },
                                {_T('t'), 9.356 },
                                {_T('u'), 2.758 },
                                {_T('v'), 0.978 },
                                {_T('w'), 2.560 },
                                {_T('x'), 0.150 },
                                {_T('y'), 1.994 },
                                {_T('z'), 0.077 }
                                };


String tryFreq(TCchar* p) {
String s         = p;
int    lng       = s.length();
double avgFrq    = 0;
int    n         = noElements(freqList);
double maxFactor = 0;
int    i;
int    pos;
Tchar  ch;
String t;

  for (i = 0; i < n; i++) avgFrq += freqList[i].freq;     avgFrq /= n;

  for (i = lng-1; i > 0; i--) {
    double f = i;  f /= lng;  f *= avgFrq;
    ch = s[i];

    if (getFactor(f, ch, _T('a'))) {if (f > maxFactor) {maxFactor = f; pos = i; continue;}}
    if (getFactor(f, ch, _T('A'))) {if (f > maxFactor) {maxFactor = f; pos = i; continue;}}
    }

  t = s.substr(0, pos);  s = t + s.substr(pos+1);

  return s;
  }


bool getFactor(double& posFact, Tchar ch, Tchar baseCh) {
int x;

  x = ch - baseCh;

  if (0 <= x && x < noElements(freqList)) {posFact = freqList[x].freq; return true;}

  return false;
  }


