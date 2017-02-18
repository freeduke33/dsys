
#include <tcxlwin.h>

#include "copyrite.h"
#include "string.h"
#include "param.hpp"


#define noname_str "NONAME"

LCL CfgT DefCfg={
   {"DSYS config file " _CFG_VER_,0},"","","","","",   // ID, dir's
   {1.0,0.0,0.0, 1.0,0.0,0.0},                         // easy zveno
   {SIN,{1.0,27.7,0.0,0.0}},                           // easy gen
   {-1,{0,0},noname_str},                              // dif zveno
   {DSYS,{-1,{0,0},noname_str}},                       // dif gen

   {50.0,100.0,EASY_GEN,{SIN,{1.0,27.7,0.0,0.0}}},     // global

   {1.0,27.7,0.0,0.0},                                 // sin
   {{9.0,3.0,1.0},{27.7,13.3,3.1},{0.0,0.0,0.0},0.0},  // psin
   {1.0,27.7,0.0},                                     // meandr
   {1.0,20.0},                                         // one
   {1.0,20.0},                                         // volume

   {200,10,"",inSCREEN,WAIT_KEY,NOSAVE_MSG},             // compile
   {200,10,"",HIDDEN,NOWAIT_KEY,NOSAVE_MSG},             // archive
   {200,10,"",inSCREEN,WAIT_KEY,NOSAVE_MSG},             // perform
   
};

RetVal _param::CheckCfg(NOARG)
{
 InitDir((char *)GetDirResult());
 InitDir((char *)GetDirInclude());
 InitDir((char *)GetDirTmp());
 InitDir((char *)GetDirProject());
 InitDir((char *)GetDirWork());

 return SUCCESS;
}

ParamP _param::DefParam(BlockT typ)
{
 switch(buf.Blk=typ)
   {
   case EASY_ZVENO:
      memcpy(&buf.U.EasyZveno,&CurCfg.EasyZveno,sizeof(EasyZvenoT));
      break;
   case EASY_GEN:
      memcpy(&buf.U.EasyGen,&CurCfg.EasyGen,sizeof(EasyGenT));
      break;
   case DIF_ZVENO:
      memcpy(&buf.U.DifZveno,&CurCfg.DifZveno,sizeof(DifZvenoT));
      break;
   case DIF_GEN:
      memcpy(&buf.U.DifGen,&CurCfg.DifGen,sizeof(DifGenT));
      break;
   }
 return &buf;
}

_param::_param()
{
 memcpy(&CurCfg,&DefCfg,sizeof(DefCfg));
 return;
}

VOID _param::InitDir(char *dir)
{
 int i;
 
 for(i=0;dir[i];i++) if(dir[i]==' ') { dir[i]=0;break; }
 if(dir[0] && dir[strlen(dir)-1]!='\\') strcat(dir,"\\");
 return;
}

// ----------------------------------------------------------------------

_cfg::_cfg(NOARG)
{
 SetFullName((DirP)"",(NameP)"DSYS",".INI",&def_file);
 return;
}

RetVal _cfg::ReadCfg(FileP file)
{
 RetVal val;
 FhandleT f;
 Word CRC,tmp,i;

 val=OpenFile(file,&f);
 if(val!=SUCCESS) return val;
 val=ReadFile(f,&TmpCfg,sizeof(CfgT));
 CloseFile(f);
 if(val!=SUCCESS) return val;
 if(strcmp(TmpCfg.ID.String,DefCfg.ID.String)) return ERROR;
 CRC=TmpCfg.ID.CRC;
 TmpCfg.ID.CRC=0;
 for(i=tmp=0;i<sizeof(CfgT);i++) tmp+=((Byte *)&TmpCfg)[i];
 if(tmp!=CRC) return ERROR;
 memcpy(GetCfg(),&TmpCfg,sizeof(CfgT));
 return SUCCESS;
}

RetVal _cfg::WriteCfg(FileP file)
{
 RetVal val;
 FhandleT f;
 Word CRC,i;
 CfgP cfg=GetCfg();

 val=NewFile(file,&f);
 if(val!=SUCCESS) return val;
 strcpy(cfg->ID.String,DefCfg.ID.String);
 cfg->ID.CRC=0;

 for(i=CRC=0;i<sizeof(CfgT);i++) CRC+=((Byte *)cfg)[i];
 cfg->ID.CRC=CRC;
 val=WriteFile(f,cfg,sizeof(CfgT));
 CloseFile(f);
 if(val!=SUCCESS) return val;
 return SUCCESS;
}


RetVal _cfg::LoadCfg(int typ)
{
 FileT file;
 RetVal val;

 memcpy(&file,&def_file,sizeof(FileT));

 val=FindFile(&file,DEFAULT_ERROR);
 if(val==SUCCESS)
   {
   memcpy(def_file,file,sizeof(FileT));
   val=ReadCfg(&file);
   if(val!=SUCCESS) Wperror(" Не могу прочитать или неверный файл конфигурации ");
   }
 else if(!typ) Wperror(" Не могу найти файл конфигурации ");
 return SUCCESS;
}

RetVal _cfg::SaveCfg(NOARG)
{
 FileT file;
 RetVal val;

 memcpy(&file,&def_file,sizeof(FileT));

 val=FindFile(&file,DEFAULT_OK);
 if(val==SUCCESS)
   {
   memcpy(def_file,file,sizeof(FileT));
   val=WriteCfg(&file);
   if(val!=SUCCESS) Wperror(" Ошибка записи файла конфигурации ");
   }
 return SUCCESS;
}


