// Table Names


#include "stdafx.h"
#include "TableNames.h"
#include "DescTable.h"
#include "IniFile.h"
#include "Utilities.h"


TableNames::TableNames(TCchar* tblName, TCchar* abbr, FieldDesc* fldDesc) :
                                                                name(tblName), abbr(abbr), keyIndex(0) {
  fillInNames();

  if (fldDesc) {
    keyName  = fldDesc->name;
    keyType  = getDbCppType(fldDesc->x);
    keyIndex = fldDesc->fieldIndex;
    }

  save();  loaded = true;
  }


static TCchar* SectionSffx = _T("Sect");
static TCchar* NameKey     = _T("TableName");
static TCchar* AbbrKey     = _T("Abbr");
static TCchar* KeyTypeKey  = _T("KeyType");
static TCchar* KeyNameKey  = _T("KeyName");
static TCchar* KeyIndexKey = _T("KeyIndex");


void TableNames::save() {
String sect = name + SectionSffx;

  iniFile.writeString(sect, NameKey,     name);
  iniFile.writeString(sect, AbbrKey,     abbr);
  iniFile.writeString(sect, KeyTypeKey,  keyType);
  iniFile.writeString(sect, KeyNameKey,  keyName);
  iniFile.writeInt(sect,    KeyIndexKey, keyIndex);
  }


bool TableNames::load(TCchar* tblName) {
String sect = tblName;  sect += SectionSffx;

  if (!iniFile.readString(sect, NameKey, name)) return false;
  iniFile.readString(sect, AbbrKey,     abbr);
  iniFile.readString(sect, KeyTypeKey,  keyType);
  iniFile.readString(sect, KeyNameKey,  keyName);
  keyIndex = iniFile.readInt(sect, KeyIndexKey, 0);

  fillInNames();   return true;
  }


void TableNames::fillInNames() {
  fileName   = name + _T("Map");
  cls        = name + _T("Table");
  tblCls     = name + _T("Tbl");
  rcd        = name + _T("Record");
  rcdObj     = objName(rcd);
  map        = name + _T("Map");
  myDB       = name + _T("DB");
  entry      = name + _T("Entry");
  rslt       = name + _T("Rslt");
  iter       = abbr + _T("Iter");
  obj        = objName(cls);                        //cls; obj[0] += _T('a') - _T('A');
  }

