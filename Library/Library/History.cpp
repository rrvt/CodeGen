// A little history class for real time data collection


#include "pch.h"
#include "History.h"
#include "FileIO.h"
#include "PathDlg.h"


void History::saveData() {
PathDlg   dlg(_T("History"), _T("History"), _T("txt"), _T("Text"), _T("*.txt"));
String    path;
FileIO    file;
HistIter  iter(*this);
HistData* h;

  if (!dlg.saveFileAs(path)) return;

  if (!file.open(path, FileIO::Write | FileIO::Create)) return;

  for (h = iter(); h; h = iter++) h->output(file);
  }


void HistData::output(FileIO& file) {
String s;

  s.format(_T("ID: %03i"), id);                 file.write(s);
  s.format(_T("   Flags:  0x%08x"), flags);     file.write(s);
  file.crlf();
  }

