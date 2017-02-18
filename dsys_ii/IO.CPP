#include <conio.h>
#include <stdio.h>
#ifdef __TURBOC__
  #include <dir.h>
#else 
  #include <dos.h>
#endif

#include <tcxlwin.h>
#include "dsys.h"
#include "io.hpp"


RetVal _io::SkipHeader(FhandleT f)
{
 Ptr tmp;
 return SeekFile(f,SEEK_CUR,sizeof(FileHeaderT),&tmp);
}

RetVal _io::WriteHeader(FhandleT f,FileHeaderP Hdr)
{
 RetVal val;
 Word CRC,i;
 Ptr tmp,pos;

 Hdr->ID.CRC=0;
 for(CRC=i=0;i<sizeof(FileHeaderT);i++)  CRC+=((Byte *)Hdr)[i];
 Hdr->ID.CRC=CRC;

 val=SeekFile(f,SEEK_CUR,0L,&pos); if(val==ERROR) goto error;
 val=SeekFile(f,SEEK_SET,0L,&tmp); if(val==ERROR) goto error;
 val=WriteFile(f,Hdr,sizeof(*Hdr));if(val==ERROR) goto error;
 val=SeekFile(f,SEEK_SET,pos,&tmp);
 error:
 return val;
}

RetVal _io::CheckCRC(FileHeaderP Hdr)
{
  RetVal val;
  Word CRC,oldCRC,i;

 oldCRC=Hdr->ID.CRC;
 Hdr->ID.CRC=0;
 for(CRC=i=0;i<sizeof(FileHeaderT);i++)  CRC+=((Byte *)Hdr)[i];
 Hdr->ID.CRC=CRC;
 if(oldCRC==CRC) val=SUCCESS;
 else
   {
   Wperror("Заголовок файла испорчен, операция прерывается");
   val=ERROR;
   }
  return val;
}

RetVal _io::SeekFile(FhandleT f,int typ,Ptr pos,Ptr* new_pos)
{
 *new_pos=lseek(f,pos,typ);
 return SUCCESS;
}


RetVal _io::NewFile(FileP file,FhandleP handle)
{
 RetVal val=SUCCESS;

#ifdef __TURBOC__
 *handle=open((char *)file,O_WRONLY|O_BINARY|O_TRUNC|O_DENYALL|O_CREAT,S_IWRITE);
#else
 *handle=sopen((char *)file,O_WRONLY|O_BINARY|O_TRUNC|O_CREAT,SH_DENYRW,S_IWRITE);
#endif
 if(*handle==-1)
   {
   Error("Не могу создать файл %s",file);
   val=ERROR;
   }

 return val;
}

RetVal _io::OpenFile(FileP file,FhandleP handle)
{
 RetVal val=SUCCESS;

#ifdef __TURBOC__
 *handle=open((char *)file,O_BINARY|O_DENYALL|O_RDONLY);
#else
 *handle=sopen((char *)file,O_BINARY|O_RDONLY,SH_DENYRW);
#endif

 if(*handle==-1)
   {
   Error("Не могу открыть файл %s",file);
   val=ERROR;
   }

 return val;
}

RetVal _io::CloseFile(FhandleT handle)
{
 RetVal val=SUCCESS;

 if( close(handle)!=0 )
    {
    Error("Не могу закрыть файл");
    val=ERROR;
    }
 return val;
}

RetVal _io::ReadFile(FhandleT handle,void *buf,Word size)
{
 RetVal val=SUCCESS;

 if( read(handle,buf,size)==-1 )
    {
    Error("Не могу прочитать файл");
    val=ERROR;
    }
 return val;
}


RetVal _io::WriteFile(FhandleT handle,void *buf,Word size)
{
  RetVal val=SUCCESS;

 if( write(handle,buf,size)==-1 )
    {
    Error("Не могу записать в файл");
    val=SUCCESS;
    }
 return val;
}


void _io::Error(const char *fmt, ...)
{
 Word cnt;
 va_list argptr;
 static char err_buf[300];

 va_start(argptr,fmt);
 cnt=vsprintf(err_buf,fmt,argptr);
 va_end(argptr);
 if(cnt>300) ExitError(err_buf);
 Wperror(err_buf);

 return;
}

RetVal _io::FindFile(FileP file,AskType ask)
{
 int val;
#ifdef __TURBOC__
  struct ffblk ff;
  val=findfirst((char *)file,&ff,0);
#endif

#ifdef __ZTC__
  val=findfirst((char *)file,0);
#endif
  switch(ask)
   {
   case DEFAULT_OK: return SUCCESS;
   case DEFAULT_ERROR: if(!val) return SUCCESS;
                       else     return ERROR;
   case ASK_SELECT:  Wperror(" FindFile: ASK_SELECT don't supported ");
   case ASK_CONFIRM: Wperror(" FindFile: ASK_CONFIRM don't supported ");
   }
 return ERROR;
}




