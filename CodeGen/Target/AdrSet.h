// AdrSet Record


#pragma once
#include "AccRcdSet.h"


class AdrSet : public AccRcdSet {
bool    opened;
public:
int     addressID;
CString address1;
CString address2;

  AdrSet();
 ~AdrSet() {close();}

  bool open(TCchar* path);
  bool isOpen() {return opened;}
  void close() {AccRcdSet::close(); opened = false;}

  bool edit();
  bool addNew();
  bool update();
  bool remove();

private:

  virtual void DoFieldExchange(CFieldExchange* pFX);

  AdrSet* moveFirst() {if (!opened) return 0; MoveFirst();  return IsEOF() ? 0 : this;}
  AdrSet* moveNext()  {if (!opened) return 0; MoveNext();   return IsEOF() ? 0 : this;}
  AdrSet* moveLast()  {if (!opened) return 0; MoveLast();   return IsEOF() ? 0 : this;}
  AdrSet* movePrev()  {if (!opened) return 0; MovePrev();   return IsBOF() ? 0 : this;}
  friend class AdrSetIter;
  };


// Iterator Declaration, see IterT.h for details

class AdrSetIter {

AdrSet& rcd;

public:

enum Dir {Fwd, Rev};

  AdrSetIter(AdrSet& record) : rcd(record) { }

  AdrSet* find(int id);

  AdrSet* operator() (Dir dir = Fwd) {return dir == Fwd ? rcd.moveFirst() : rcd.moveLast();}
  AdrSet* operator++ (int)           {return rcd.moveNext();}
  AdrSet* operator-- (int)           {return rcd.movePrev();}

private:

  AdrSetIter() : rcd(*(AdrSet*)0) { }
  };
