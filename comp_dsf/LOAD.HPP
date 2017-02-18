#ifndef __LOAD_HPP__
#define __LOAD_HPP__


#include <files.hpp>
#include "blok.hpp"
#include "file.h"

class DSF:files
{
 private:
   void *Icon;
   FileHeaderT FH;
   int mode,err;
   BlkPtr BlkLst;

   inline int IsUnknown(NOARG) { return(mode==0) ? 1:0; }
   inline int IsOpen(NOARG)    { return(mode==1) ? 1:0; }
   inline int IsClose(NOARG)   { return(mode==2) ? 1:0; }

   inline void SetUnknown(NOARG) { mode=0; }
   inline void SetOpen(NOARG)    { mode=1; }
   inline void SetClose(NOARG)   { mode=2; }

   int CalcCRC(NOARG);

   RetVal LoadHdr(NOARG);
   RetVal LoadIcon(NOARG);
   RetVal LoadSCR(NOARG);

   RetVal BeginSave(NOARG);     // preserve space for header
   RetVal SaveHdr(NOARG);       // mast be last operation
   RetVal SaveIcon(NOARG);
   RetVal SaveSCR(NOARG);
   RetVal SaveBLK(NOARG);
   inline RetVal EndSave(NOARG)  { return SaveHdr(); }

   inline int IsCRCValid(NOARG) { return(CalcCRC()==OrgCRC) ? 1:0; }
   inline void SetError(int code) { err=code; }

 public:
   inline DSF() { mode=err=0; BlkLst=NULL; }
   ~DSF();

   RetVal NameDSF(char *name);
   RetVal ReadDSF(NOARG);
   RetVal WriteDSF(NOARG);
   RetVal GetSCR(DefBlkP *Lst);

   inline int GetErrorDSF(NOARG) { return err; }
};

#endif