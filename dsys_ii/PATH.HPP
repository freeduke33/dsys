#ifndef __path_II_
#define __path_II_

#include "mainsys.h"

class _path
{
 public:

   RetVal InsMacro(CmdLineP file,char *macro,char *str);
   RetVal SetFullName(DirP dir,NameP name,char *tag,FileP file);
   RetVal GrabDir(FileP file,DirP dir);
   RetVal GrabName(FileP file,NameP name);
   RetVal GrabTag(FileP file,char *tag);
};

#endif
