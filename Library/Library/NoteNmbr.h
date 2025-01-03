// A Little Class to hold the details of a number (int, uint, double) width and precision (double only).


#pragma once
//class TxtOut;

enum NoteNmbrTyp {NilNmbrTyp = 0, IntNmbrTyp, UIntNmbrTyp, DblNmbTyp};


struct NoteNmbr {
NoteNmbrTyp typ;
union {
  long   longVal;
  ulong  uLongVal;
  double dblVal;
  };
int  width;                 // Width of Integer or floating point field  >0 right adj, <0 left adj
int  prec;                  // Precision for floating point display (digits after period)
bool hex;                   // ulong output as hex value, e.g. 0xabcd1

            NoteNmbr() : typ(NilNmbrTyp), dblVal(0), width(0), prec(0), hex(false) { }
            NoteNmbr(NoteNmbr& nn) {copy(nn);}
           ~NoteNmbr() { }

  void      clear() {typ = NilNmbrTyp; longVal = 0; width = 0; prec = 0; hex = false;}

  bool      isEmpty() {return !typ;}

  NoteNmbr& operator= (NoteNmbr& nn) {copy(nn); return *this;}

  String&   operator() ();

  String&   stg();

private:

  void      copy(NoteNmbr& nn);
  void      addSpcs(int n);
  };

