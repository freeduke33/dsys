#include <stdio.h>
#include <process.h>
#include <stdarg.h>
#include <string.h>

#include "dsys.h"
#include "menu.h"


#include "edit.hpp"

static _edit Edt;

TrigType trigger;

ParamT ParBuf;

extern "C"
{

RetVal CTYP EdtLoop(NOARG)          { return Edt.EdtPerform();  }
RetVal CTYP EdtPutBlock(BlockT blk) { return Edt.DefBlock(blk); }
RetVal CTYP EdtGetBlock(BlockP blk) { return Edt.GetBlock(blk); }
RetVal CTYP EdtSetParam(ParamP par) { return Edt.SetParam(par); }
RetVal CTYP EdtGetParam(ParamP par) { return Edt.GetParam(par); }
RetVal CTYP EdtParam(NOARG)         { return Edt.Param();       }
CfgP   CTYP EdtGetCfg(NOARG)        { return Edt.GetCfg();      }
VOID   CTYP EdtCheckCfg(NOARG)      { Edt.CheckCfg();return;    }
VOID   CTYP LOAD_CFG(NOARG)         { Edt.LoadCfg(); return;    }
VOID   CTYP SAVE_CFG(NOARG)         { Edt.SaveCfg(); return;    }
VOID   CTYP EdtExit(NOARG)          { Edt.EdtExit(); return;    }

VOID CTYP EdtNewScr(char *file)
{
  Edt.NewScr((NameP)file);
return;
}

VOID CTYP EDT_SAVE(NOARG)
{
 Edt.SaveScr();
 return;
}

VOID CTYP EdtSaveAs(char *name)
{
 FileT file;
 Edt.SetFullName(Edt.GetDirWork(),(NameP)name,".DSF",&file);
 Edt.SaveScr(&file);
 EdtLoad(name);
 return;
}

VOID CTYP EdtLoad(char *name)
{
 FileT file;
 int i;

 for(i=strlen(name);i>0 && name[i]!='\\';i--); i++;
 Edt.SetFullName(Edt.GetDirWork(),(NameP)&name[i],".DSF",&file);
 Edt.LoadScr(&file);
 return;
}

VOID CTYP InitEasyGenParam(NOARG)
{
 extern EasyGenT GenBuf[];
 extern GenT UseGen;
 CfgP cfg;

 cfg=Edt.GetCfg();
 
 UseGen=SIN;
 memcpy(&GenBuf[SIN]   .U.Sin   ,&cfg->Sin   ,sizeof(SinT   ));
 memcpy(&GenBuf[PSIN]  .U.PSin  ,&cfg->PSin  ,sizeof(PSinT  ));
 memcpy(&GenBuf[MEANDR].U.Meandr,&cfg->Meandr,sizeof(MeandrT));
 memcpy(&GenBuf[ONE]   .U.One   ,&cfg->One   ,sizeof(OneT   ));
 memcpy(&GenBuf[VOLUME].U.Volume,&cfg->Volume,sizeof(VolumeT));
 
 return; 
}

VOID CTYP StoreEasyGenParam(NOARG)
{
 extern EasyGenT GenBuf[];
 CfgP cfg;

 cfg=Edt.GetCfg();
  
 memcpy(&cfg->Sin   ,&GenBuf[SIN]   .U.Sin   ,sizeof(SinT   ));
 memcpy(&cfg->PSin  ,&GenBuf[PSIN]  .U.PSin  ,sizeof(PSinT  ));
 memcpy(&cfg->Meandr,&GenBuf[MEANDR].U.Meandr,sizeof(MeandrT));
 memcpy(&cfg->One   ,&GenBuf[ONE]   .U.One   ,sizeof(OneT   ));
 memcpy(&cfg->Volume,&GenBuf[VOLUME].U.Volume,sizeof(VolumeT));
 
 return; 
}

VOID CTYP MOD_PROC(NOARG) { Edt.Perform(); return; }


VOID CTYP ARCHIVE(NOARG)  { Edt.Archive(2); return; }
VOID CTYP SHOW_RES(NOARG) { Edt.Archive(3); return; }

// ===================================================================== //

void ExitError(const char *str, ...)
{
 int i;
 va_list argptr;

 fprintf(stderr,"\0x07\0x07");
 for(i=1;i<30;i++) fprintf(stderr,"\n");
 fprintf(stderr,"\0x07\nDetect internal error: ");
 va_start(argptr,str);
 vfprintf(stderr,str,argptr);
 va_end(argptr);
 fprintf(stderr,"\n\0x07");
 exit(0);
}


};
