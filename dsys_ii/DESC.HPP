#ifndef __DESC__HPP__
#define __DESC__HPP__

#include <stdlib.h>
#include "io.hpp"
#include "mainsys.h"
#include "file.h"

typedef struct _DescLst DescLst,*DescLstP;

struct _DescLst {
 Word Group;
 char far *Text;
 DescLstP next,prev;
};

class _desc
{
 private:
    DescLstP Lst;

 public:
   inline _desc(NOARG)   { Lst=NULL;    }
   inline ~_desc(NOARG)  { ClearDesc(); }

   RetVal ClearDesc(NOARG);
   RetVal ReadDesc(FhandleT handle,FileHeaderP Hdr);
   RetVal WriteDesc(FhandleT handle,FileHeaderP Hdr);

   RetVal GetDesc(Word Group,Word MaxLen,char *Desc);
   RetVal SetDesc(Word Group,char *Desc);
   Word   GetDescLen(Word Group);
};

#endif
