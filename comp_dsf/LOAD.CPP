#include "load.hpp"
#include "errcode.h"

~DSF()
{
 if(IsOpen()) Close();
 return;
}


RetVal DSF::NameDSF(char *name)
{
 if(IsUnknown())
     {
     SetClose();
     return SetFile(name);
     }
 else  return ERROR;
}

RetVal DSF::ReadDSF(NOARG)
{
 RetVal val;

 if(IsClose())
   {
   val=Open((o_mode)o_RDONLY|o_BINARY); if(val!=SUCCESS) return val;
   SetOpen();
   val=LoadHdr();                       if(val!=SUCCESS) return val;
   if(!IsCRCValid()) return ERROR;
   val=LoadSCR();                       if(val!=SUCCESS) return val;
   val=LoadIcon();
   val=Close();
   SetClose();
   }
 else val=ERROR;
 return val;
}

RetVal DSF::WriteDSF(NOARG)
{
 RetVal val;

 if(IsClose())
   {
   BackUp();
   val=Open((o_mode)o_WRONLY|o_BINARY|o_TRUNC|o_CREAT);
   if(val!=SUCCESS) return val;
   SetOpen();
   val=BeginSave();  if(val!=SUCCESS) return val;
   val=SaveSCR();    if(val!=SUCCESS) return val;
   val=SaveBLK();    if(val!=SUCCESS) return val;
   val=SaveIcon();   if(val!=SUCCESS) return val;
   val=SaveHdr();    if(val!=SUCCESS) return val;
   val=Close();
   SetClose();
   }
 else val=ERROR;
 return val;
}

RetVal DSF::GetSCR(BlkDefP *Lst)
{
 if(BlkLst==NULL) return ERROR;
 else *Lst=BlkLst;

 return SUCCESS;
}

// ========================================================================


RetVal DSF::LoadHdr(NOARG)
{
 Seek(0L,g_FIRST);
 return Read(&FH,sizeof(FH));
}

RetVal DSF::LoadIcon(NOARG)
{
 RetVal val=SUCCESS;

 if(FH.IconSize)
   {
   val=Seek(FH.Icon,g_FIRST);
   Icon=new char[FH.IconSize];
   if(Icon==NULL) { val=ERROR; SetError(NOMEM); }
   else             val=Read(Icon,FH.IconSize);
   }
 else Icon=NULL;

 return val;
}

RetVal DSF::LoadSCR(NOARG)
{
 RetVal val;
 Word   i;
 BlockDefT Def;

 val=Seek(FH.Scr,g_FIRST);
 BlkLst=new _Block(0,0,BLK_NONE,NULL)[FH.ScrNum];
 if(BlkLst==NULL) { SetError(NOMEM); return val; }

 if(val==SUCCESS)
   {
   for(i=0;i<FH.ScrNum && val==SUCCESS;i++)
       {
       val=Read(&Def,sizeof(Def));
       if(val==SUCCESS)
	  {
	  val=Read(&Dat,sizeof(Dat));
	  BlkLst[i].Init(Def.x,Def.y,Def.Blk,Def.Group,&Dat);
	  }
       if(val!=SUCCESS) SetError(NOREAD);
       }
   }
 if(val!=SUCCESS) delete[FH.ScrNum] BlkLst;
 return val;
}

// ---------------------------------------------------------------------

RetVal DSF::SaveHdr(NOARG)
{
 return SUCCESS;
}

RetVal DSF::SaveIcon(NOARG)
{
 return SUCCESS;
}

RetVal DSF::SaveSCR(NOARG)
{
 return SUCCESS;
}

RetVal DSF::BeginSave(NOARG)
{
 return SUCCESS;
}

RetVal DSF::SaveBLK(NOARG)
{
 return SUCCESS;
}
