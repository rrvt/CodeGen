// Utilities


#pragma once


void createCopyright(TCchar* name, TCchar* version);


void   toRight(String& s);


void   addPadding(int n);    // Add n spaces of padding to notepad output

String addTab(String& s, int max);

String normalizeName(String name);
String normalizeDate(TCchar* date);
String normalizeTime(TCchar* time);

String objName(String& clsName);

String getDateNow();
String getTimeNow();

String findAbbr(TCchar* s);


// Display a string of no more than noChars.  If more, the insert noTabs and no more than noChars until
// string exhausted.  returns number of lines output

//int   dsplyWrap(TCchar* p, int noChars, int noTabs);
