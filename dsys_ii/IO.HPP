#ifndef __io_II_
#define __io_II_


#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>

#include "mainsys.h"
#include "file.h"

#ifdef __ZTC__
  #include <share.h>
#endif

#include "path.hpp"

typedef Word FhandleT, *FhandleP;

class _io: public _path
{
 private:

   void Error(const char *Frm, ...);

 public:

   RetVal OpenFile(FileP name,FhandleP handle);
   RetVal NewFile(FileP name,FhandleP handle);
   RetVal CloseFile(FhandleT handle);
   RetVal ReadFile(FhandleT handle,void *buf,Word size);
   RetVal SeekFile(FhandleT handle,int type,Ptr pos,Ptr *new_pos);
   RetVal WriteFile(FhandleT handle,void *buf,Word size);
   RetVal WriteHeader(FhandleT handle,FileHeaderP Hdr);
   RetVal SkipHeader(FhandleT handle);
   RetVal CheckCRC(FileHeaderP Hdr);

   RetVal FindFile(FileP file,AskType ask);

};


#endif
