// TestAppDoc.cpp : implementation of the TestAppDoc class


#include "stdafx.h"
#include "TestAppDoc.h"
#include "BookDlg.h"
#include "EraseBookDlg.h"
#include "GetPathDlg.h"
#include "MapDataDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "PersonDlg.h"
#include "TableDscrs.h"
#include "TestApp.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// TestAppDoc

IMPLEMENT_DYNCREATE(TestAppDoc, CDocument)

BEGIN_MESSAGE_MAP(TestAppDoc, CDocument)
  ON_COMMAND(ID_Test,       &TestAppDoc::OnTest)
  ON_COMMAND(ID_Add,        &TestAppDoc::OnAdd)
  ON_COMMAND(ID_Erase,      &TestAppDoc::OnErase)
  ON_COMMAND(ID_FILE_SAVE,  &TestAppDoc::OnFileSave)
END_MESSAGE_MAP()


// TestAppDoc construction/destruction

TestAppDoc::TestAppDoc() noexcept { }

TestAppDoc::~TestAppDoc() { }


void TestAppDoc::OnTest() {
MapDataDlg dlg;
int        i;
TableDsc*  p;

  notePad.close();

  dlg.title = _T("Display Records in Selected Table");

  if (dlg.DoModal() == IDOK) {
    for (p = tableDscrs.startLoop(), i = 0; p; p = tableDscrs.nextEntry(), i++) {

      if (i) notePad << nCrlf;

      if (p->selected) {
        notePad << p->name << _T(" Table") << nCrlf;
        if (p->name == _T("Book"))   {dspBooks(  (BookTbl*)   p->mapTable); continue;}
        if (p->name == _T("Person")) {dspPersons((PersonTbl*) p->mapTable); continue;}
        }
      }
    }

  invalidate();
  }



void TestAppDoc::dspBooks(  BookTbl* books) {
BookRecord*  rcd;
PersonRecord* person;

  if (!books) return;

  notePad << nClrTabs << nSetRTab(3) << nSetTab(5) << nSetTab(30) << nSetTab(60);
  notePad << nTab << _T("ID") << nTab << _T("Title") << nTab << _T("Author") << nTab << _T("Protagonist");
  notePad << nCrlf;

  for (rcd = books->startLoop(); rcd; rcd = books->nextRecord()) {
    notePad << nTab << rcd->ID;
    notePad << nTab << rcd->Title;
    person = personTable.find(rcd->AuthorID);
    if (person) {
      notePad << nTab << person->FirstName << _T(" ") << person->LastName;
      }
    person = personTable.find(rcd->ProtagID);
    if (person) {
      notePad << nTab << person->FirstName << _T(" ") << person->LastName;
      }
    notePad << nCrlf;
    }
  }


void TestAppDoc::dspPersons(PersonTbl* persons) {
PersonRecord* rcd;
String        s;

  if (!persons) return;

  notePad << nClrTabs << nSetRTab(3) << nSetTab(5) << nSetTab(30);
  notePad << nTab << _T("ID") << nTab << _T("Person") << nTab << _T("Is Author") << nCrlf;

  for (rcd = persons->startLoop(); rcd; rcd = persons->nextRecord()) {
    notePad << nTab << rcd->ID << nTab << rcd->FirstName << _T(" ") << rcd->LastName;
    s = rcd->Author ? _T("Yes") : _T("No");
    notePad << nTab << s << nCrlf;
    }
  }


void TestAppDoc::OnAdd() {
MapDataDlg dlg;
int        i;
TableDsc*  p;

  notePad.close();

  dlg.title = _T("Add Record To Selected Table");

  if (dlg.DoModal() == IDOK) {
    for (p = tableDscrs.startLoop(), i = 0; p; p = tableDscrs.nextEntry(), i++) {

      if (p->selected) {
        if (p->name == _T("Book"))   {addBook(  (BookTbl*)   p->mapTable); continue;}
        if (p->name == _T("Person")) {addPerson((PersonTbl*) p->mapTable); continue;}
        }
      }
    }

  personTable.toDatabase();    // Updates marked records
  bookTable.toDatabase();

  invalidate();
  }


void TestAppDoc::addBook(BookTbl* books) {
BookDlg       dlg;
BookRecord*   rcd;
String        title;
String        first;
String        last;
PersonRecord* perRcd;

  if (dlg.DoModal()) {
    title = dlg.title;
    rcd = books->get(title);
    if (!rcd) {messageBox(_T("Unable to add Book record")); return;}

    first = dlg.authorFirstName; last = dlg.authorLastName;
    if (!first.isEmpty() || !last.isEmpty()) {
      perRcd = personTable.get(first, last, true);
      if (!perRcd) {messageBox(_T("Unable to add Author record")); return;}

      rcd->AuthorID = perRcd->ID;   rcd->mark();
      }

    first = dlg.protagFirstName; last = dlg.protagLastName;
    if (!first.isEmpty() || !last.isEmpty()) {
      perRcd = personTable.get(first, last, false);
      if (!perRcd) {messageBox(_T("Unable to add Protagonist record")); return;}

      rcd->ProtagID = perRcd->ID;   rcd->mark();
      }
    }
  }


void TestAppDoc::addPerson(PersonTbl* persons) {
PersonDlg     dlg;
PersonRecord* rcd;

  if (dlg.DoModal()) {
    String first = dlg.firstName;
    String last  = dlg.lastName;

    rcd = persons->get(first, last, dlg.isAuthor);
    if (!rcd) {messageBox(_T("Unable to add record")); return;}
    }
  }


void TestAppDoc::OnErase() {
MapDataDlg dlg;
TableDsc*  p;

  notePad.close();

  dlg.title = _T("Erase Record From Selected Table");

  if (dlg.DoModal() == IDOK) {
    for (p = tableDscrs.startLoop(); p; p = tableDscrs.nextEntry()) {

      if (p->selected) {
        if (p->name == _T("Book"))   {eraseBook(  (BookTbl*)   p->mapTable); continue;}
        if (p->name == _T("Person")) {erasePerson((PersonTbl*) p->mapTable); continue;}
        }
      }
    }

  personTable.toDatabase();    // Updates marked records
  bookTable.toDatabase();

  invalidate();
  }


void TestAppDoc::eraseBook(BookTbl* books) {
EraseBookDlg dlg;
BookRecord*  rcd;

  notePad.close();

  if (dlg.DoModal() == IDOK) {
    String title = dlg.title;

    rcd = books->get(title);
    if (!rcd) {messageBox(_T("Unable to find book record")); return;}

    rcd->del();
    }
  }


void TestAppDoc::erasePerson(PersonTbl* persons) {
PersonDlg     dlg;
PersonRecord* rcd;

  if (dlg.DoModal()) {
    String first = dlg.firstName;
    String last  = dlg.lastName;

    rcd = persons->get(first, last, dlg.isAuthor);
    if (!rcd) {messageBox(_T("Unable to add record")); return;}

    rcd->del();
    }
  }


// TestAppDoc commands


void TestAppDoc::OnFileSave() {
String path;

  if (!getSaveAsPathDlg(_T("Test App"), _T("*.txt"), _T("txt"), _T("txt"), path)) return;

  OnSaveDocument(path);
  }


// TestAppDoc serialization

void TestAppDoc::serialize(Archive& ar) {
  if (ar.isStoring()) {notePad.archive(ar); return;}

  Tchar  ch;
  String s;

  while (ar.read(ch)) {
    if (ch == _T('\n'))
      {notePad << s << nCrlf;  s.clear(); continue;}
    if (ch == _T('\r'))
      continue;
    s += ch;
    }

  if (!s.isEmpty()) notePad << s << nCrlf;

  invalidate();
  }


// TestAppDoc diagnostics

#ifdef _DEBUG
void TestAppDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void TestAppDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG
