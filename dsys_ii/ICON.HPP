#ifndef __icon_II_
#define __icon_II_


#include "dsys.h"
#include "file.h"
#include "io.hpp"
#include "desc.hpp"


class _icon: virtual public  _io,public _desc
{
  private:

    void *buf;

  public:
    inline  _icon(NOARG) { buf=NULL;    }
    inline ~_icon(NOARG) { ClearIcon(); }
 
    RetVal WriteIcon(FhandleT handle,FileHeaderP Hdr);
    RetVal ReadIcon(FhandleT handle,FileHeaderP Hdr);
    RetVal ClearIcon(NOARG);

};

#endif

