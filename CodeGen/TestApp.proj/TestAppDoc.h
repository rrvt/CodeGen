// TestAppDoc.h : interface of the TestAppDoc class


#pragma once
#include "CDoc.h"
#include "BookTbl.h"
#include "PersonTbl.h"



class TestAppDoc : public CDoc {

protected: // create from serialization only
  TestAppDoc() noexcept;
  DECLARE_DYNCREATE(TestAppDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:

          void OnFileSave();

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~TestAppDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void dspBooks(   BookTbl*   books);
  void dspPersons( PersonTbl* persons);
  void addBook(    BookTbl*   books);
  void addPerson(  PersonTbl* persons);
  void eraseBook(  BookTbl*   books);
  void erasePerson(PersonTbl* persons);

protected:

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnTest();
  afx_msg void OnAdd();
  afx_msg void OnErase();
  };
