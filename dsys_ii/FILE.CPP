// ========================[ работа с файлами ]========================
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "conio.h"
#include "errno.h"

#include "copyrite.h"
#include "edit.hpp"
#include "file.h"
#include "menu.h"

#include "tcxlwin.h"
#include "tcxlvid.h"
#include "tcxlcur.h"
#include "tcxlinp.h"


static FileHeaderT DefHdr={{"DSYS model file " _DSF_VER_,0},NULL,0,0};



VOID CTYP _edit::InitNew(FileP name)
{
    strcpy((char *)SCR.name,(char *)name);     // новое имя
    EdtNewPos(1,1);            // позиция курсора
    SetUpdate(CUR_OFF);        // индикатор изменений
    SetGroup(1);               // основная группа
    Refresh();                 // дисплей
  return;
}

RetVal _edit::NewScr(NameP name)
{
 RetVal val;
 FileT file;
 BlkPtr blk;

 SetFullName(GetDirWork(),name,".DSF",&file);
 val=FindFile(&file,DEFAULT_OK);
 if(val==SUCCESS) val=Update(ASK_CONFIRM);
 else             val=SUCCESS;
 
 ClearIcon();
 if(val==SUCCESS)
    {
    val=FirstBlock(&blk);
    while(val==SUCCESS) 
       {
       _screen::PutBlock(blk->GetX(),blk->GetY(),BLK_NONE);
       val=NextBlock(&blk);
       }
    val=SUCCESS;
    InitNew(&file);
    }
 return val;
}




RetVal _edit::LoadScr(FileP filename)
{
 RetVal val;
 FhandleT f=-1;
 FileHeaderT Hdr;
 BlockDefT buf;
 Word len,i;
 ParamT par;
 Ptr tmp;
 BlkPtr blk;

 val=Update(ASK_CONFIRM); if(val==ERROR) goto cancel;

 
 val=OpenFile(filename,&f);
 if(val==SUCCESS)
   {
   val=ReadFile(f,&Hdr,sizeof(FileHeaderT)); if(val==ERROR)  goto cancel;
   if(!strcmp(Hdr.ID.String,DefHdr.ID.String))
       {
       val=CheckCRC(&Hdr); if(val==ERROR) goto cancel;
       val=ReadIcon(f,&Hdr); if(val==ERROR) goto cancel;
       val=SeekFile(f,SEEK_SET,Hdr.Scr,&tmp); if(val==ERROR) goto cancel;

       // очистить поле под новую д. систему
       val=FirstBlock(&blk);
       while(val==SUCCESS)
           {
           _screen::PutBlock(blk->GetX(),blk->GetY(),BLK_NONE);
           val=NextBlock(&blk);
           }
      val=SUCCESS;

       for(i=0;i<Hdr.ScrNum;i++)
	  {
	  val=ReadFile(f,&buf,sizeof(BlockDefT)); if(val==ERROR) break;
          SetGroup(buf.Group);
	  _screen::PutBlock(buf.x,buf.y,buf.Blk);
	  len=BlkSize(buf.Blk);
          par.Blk=buf.Blk;
          par.Group=buf.Group;
	  val=ReadFile(f,&par.U,len); if(val==ERROR) break;
	  _screen::SetParam(buf.x,buf.y,&par);
	  }
       CloseFile(f);
       if(val==ERROR) NewScr();
       else           InitNew(filename);
       }
   else
       {
       Wperror("Неверный заголовок файла схемы");
       val=ERROR;
       goto cancel;
       }
   }
 cancel:
 return val;
}

RetVal _edit::SaveScr(FileP filename)
{
 RetVal val;
 FhandleT f=-1;
 FileHeaderT Hdr;
 Word  len;
 BlockDefT buf;
 BlkPtr blk;
 ParamT par;

 memcpy(&Hdr,&DefHdr,sizeof(FileHeaderT));
 val=NewFile(filename,&f);
 if(val==SUCCESS)
   {
   val=SkipHeader(f);
   if(val==ERROR) goto erase;

   Hdr.ScrSize=Hdr.ScrNum=0;
   val=FirstBlock(&blk);
   while(val==SUCCESS)
        {
        if(blk->GetType()!=BLK_NONE)
            {
	    len=BlkSize(blk->GetType());
	    Hdr.ScrSize+=len+sizeof(BlockDefT);
	    Hdr.ScrNum++;
            buf.x=blk->GetX();
            buf.y=blk->GetY();
            buf.Group=blk->GetGroup();
            buf.Blk=blk->GetType();
	    val=WriteFile(f,&buf,sizeof(buf));
	    if(val==ERROR) goto erase;
            blk->GetParam(&par);
	    val=WriteFile(f,&par.U,len);
	    if(val==ERROR) goto erase;
            }
        val=NextBlock(&blk);
        }
   Hdr.Scr=sizeof(FileHeaderT);

   val=WriteIcon(f,&Hdr);   if(val==ERROR) goto erase;
   val=WriteHeader(f,&Hdr); if(val==ERROR) goto erase;
   val=CloseFile(f);
   SetUpdate(CUR_OFF);
   }
 else
   {
   erase:
   if(f!=-1) CloseFile(f);
   unlink((char *)filename);
   }
 return val;
}

RetVal _edit::Update(AskType ask)
{
 RetVal val=SUCCESS;

 if(update)
   {
   switch(ask)
     {
     case ASK_CONFIRM:
           SAVE_YN();             // confirm about save current screen
           switch(trigger)
             {
             case CONTINUE:  val=SUCCESS;            break;
             case CANCEL:    val=ERROR;              break;
             case SAVE:      val=SaveScr(&SCR.name); break;
             default:        val=ERROR;              break;
             }
           break;
     case DEFAULT_OK:
           val=SUCCESS;
           break;
     case DEFAULT_ERROR:
           Wperror("Схема не сохранена на внешнем носителе");
           val=ERROR;
           break;
     }
   }
 return val;
}



