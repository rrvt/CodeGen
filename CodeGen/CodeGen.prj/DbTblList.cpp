// Database Table List


#include "pch.h"
#include "DbTblList.h"
#include "Database.h"
#include "IniFileEx.h"
#include "NotePad.h"


static TCchar* AbbrKey   = _T("Abbr");
static TCchar* PrimKey   = _T("PrimKey");
static TCchar* PKTypeKey = _T("PrimType");


DbTblList dbTblList;


void DbTblList::load(TCchar* path) {
TblIter    iter(accTblDsc);
AccTblDsc* dsc;

  data.clear();

  if (!accTblDsc.open(path)) return;

  for (dsc = iter(); dsc; dsc = iter++) {
    String type = dsc->type;
    if (type == _T("TABLE")) {TblItem item;   item.load(dsc->name);   data = item;}
    }

  accTblDsc.close();
  }


void DbTblList::display() {
DbTblIter iter(*this);
TblItem*  dsc;

  for (dsc = iter(); dsc; dsc = iter++) {
    notePad << dsc->name << nCrlf;
    }
  }



void TblItem::load(TCchar* name) {this->name = name;  getAbbr(); loadPKey();}


void TblItem::loadPKey() {
String s;

  iniFile.readString(sect(s), PrimKey, primKey);
  pKeyType = (FieldType) iniFile.readInt(s, PKTypeKey, 0);
  }


void TblItem::getPKey() {
FldsIter iter(fields);
Field*   fld;

  for (fld = iter(); fld; fld = iter++) {
    if (fld->type == IdxFld) {
      setPKey(fld->name);
      setPKType(fld->type);
      break;
      }
    }
  }


void TblItem::setAbbr(TCchar* abbr)
          {String s;   this->abbr = abbr;         iniFile.writeString(sect(s), AbbrKey, abbr);}
void TblItem::setPKey(TCchar* primKey)
          {String s;  this->primKey = primKey;    iniFile.writeString(sect(s), PrimKey, primKey);}
void TblItem::setPKType(FieldType pKeyType)
          {String s;  this->pKeyType = pKeyType;  iniFile.writeInt(sect(s), PKTypeKey, pKeyType);}

void TblItem::getAbbr() {String s; iniFile.readString(sect(s), AbbrKey, abbr);}


void TblItem::copy(TblItem& ti) {
  name     = ti.name;
  abbr     = ti.abbr;
  primKey  = ti.primKey;
  pKeyType = ti.pKeyType;
  selected = ti.selected;
  }



