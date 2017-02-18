#ifndef __param_II_
#define __param_II_

#include "dsys.h"
#include "io.hpp"

class _param
{
 private:

   CfgT CurCfg;
   ParamT buf;

   VOID InitDir(char *dir);
 public:

   _param();

   RetVal CheckCfg(NOARG);
   ParamP DefParam(BlockT Blk);

   inline CfgP GetCfg(NOARG)        { return &CurCfg; }
   inline DirP GetDirTmp(NOARG)     { return &CurCfg.dir_tmp;     }
   inline DirP GetDirProject(NOARG) { return &CurCfg.dir_project; }
   inline DirP GetDirResult(NOARG)  { return &CurCfg.dir_result;  }
   inline DirP GetDirInclude(NOARG) { return &CurCfg.dir_include; }
   inline DirP GetDirWork(NOARG)    { return &CurCfg.dir_work;    }
};

class _cfg:virtual public _param,virtual _io
{
 private:
   FileT  def_file;
   CfgT   TmpCfg;

   RetVal ReadCfg(FileP name);
   RetVal WriteCfg(FileP name);

 public:

   _cfg(NOARG);

   RetVal LoadCfg(int typ=0);
   RetVal SaveCfg(NOARG);
};

#endif

