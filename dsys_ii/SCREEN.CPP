#include <stdlib.h>
#include <time.h>
#include "screen.hpp"


// распределяет новый вектор и добавляет его к списку векторов
//
_LstHdr::_LstHdr(Word size,LstHdrP *first,LstHdrP *last)
{
 Word i;

  Size=size;
  if(size==0) raise(SIG_ERRARG);

  dat=new _block[size];
  if(!dat)    raise(SIG_NOMEM);

  for(i=0;i<Size;i++) dat[i].Forget();  //делаем все новые блоки удаленными

  if(*last) (*last)->Next(this);
  if(*first==NULL) *first=this;
  prev=*last;
  next=NULL;
  *last=this;

  _last =last;
  _first=first;

 return;
}

// Удаляет вектор из списка векторов,
// модифицирует указатели нач. и кон. списка
_LstHdr::~_LstHdr()
{
 if(next) next->Prev(prev);
 else *_last=prev;

 if(prev) prev->Next(next);
 else *_first=next;

 delete[Size] dat;

 return;
}


// Дает адрес первого активного элемента списка
//
BlkPtr _LstHdr::FirstBlk(NOARG)
{
  return &dat[num=0];
}

// Дает адрес следующего активного элемента списка
//
BlkPtr _LstHdr::NextBlk(NOARG)
{
 if(num+1>=Size) return NULL;
 else            return &dat[++num];
}

//===========================================================================//

_screen::_screen()
{
 Size=32;
 Group=1;
 first=last=NULL;
 return;
}

_screen::~_screen()
{
 while(first) delete last;   // удаляем все вектора
 return;
}


RetVal _screen::Find(CurT x,CurT y,BlkPtr *blk)
{
 RetVal val=SUCCESS;
 LstHdrP cur;

 cur=first;
 while(cur)    // по всем векторам
    {
    *blk=cur->FirstBlk();
    while(*blk)   // по всем блокам вектора
	 {
	 if((*blk)->GetAct()  &&
	    (*blk)->GetGroup()==Group && 
	    (*blk)->GetX()==x &&
	    (*blk)->GetY()==y  )  goto found; // нашли блок
	 *blk=cur->NextBlk();
	 }
    cur=cur->Next();
    }

 val=ERROR;  // нет такого блока
 found:
 return val;
}

RetVal _screen::NextBlock(BlkPtr *blk)
{
 RetVal val=SUCCESS;

 if(cur)
    {
    cur_blk=cur->NextBlk();
    while((cur_blk==NULL || cur_blk->GetAct()==0) && val==SUCCESS)
      {
      if(cur_blk==NULL) 
        {
        cur=cur->Next();
        if(cur!=NULL) cur_blk=cur->FirstBlk();
        else          val=ERROR;
        }
      else cur_blk=cur->NextBlk();   
      }
    }
 else val=ERROR;  // нет больше блоков
 *blk=cur_blk;
 return val;
}

RetVal _screen::FirstBlock(BlkPtr *blk)
{
 RetVal val=SUCCESS;
 
   cur=first;
   if(cur)
     {
     cur_blk=cur->FirstBlk();
     if(cur_blk==NULL || cur_blk->GetAct()==0) val=NextBlock(blk);
     else *blk=cur_blk;
     }
   else val=ERROR;

 return val;
}

RetVal _screen::NewArea(BlkPtr *blk)
{
 last=new _LstHdr(Size,&first,&last);
 *blk=last->FirstBlk();
 return SUCCESS;
}

RetVal _screen::DelArea(NOARG)
{
 delete last;
 return SUCCESS;
}

RetVal _screen::DelBlk(BlkPtr blk)
{
 blk->Forget();
 return SUCCESS;
}

RetVal _screen::NewBlk(BlkPtr *blk)
{
 RetVal val=SUCCESS;
 LstHdrP cur;

 // ищем среди удаленных
   cur=first;
   while(cur)
      {
      *blk=cur->FirstBlk();
      while(*blk)
	 {
	 if((*blk)->GetAct()==0) goto found;
	 *blk=cur->NextBlk();
	 }
      cur=cur->Next();
      }

  // удаленных нет, распределяем новый вектор
  val=NewArea(blk);

found:

 return val;
}


RetVal _screen::PutBlock(CurT x,CurT y,BlockT typ)
{
 BlkPtr blk;
 RetVal val;

 if(Find(x,y,&blk)==SUCCESS)
   {
   if(blk->GetType()==typ) return SUCCESS;
   DelBlk(blk);
   }
 if(typ!=BLK_NONE)
   {
   val=NewBlk(&blk);
   if(val==SUCCESS) blk->Init(x,y,Group,typ,DefParam(typ));
   }
 else val=SUCCESS;

 return val;
}


RetVal _screen::GetBlock(CurT x,CurT y,BlockP typ)
{
 BlkPtr blk;
 RetVal val;

 if(Find(x,y,&blk)==SUCCESS)
   {
   *typ=blk->GetType();
   val=SUCCESS;
   }
 else
   {
   *typ=BLK_NONE;
   val=ERROR;
   }

 return val;
}

RetVal _screen::GetParam(CurT x,CurT y,ParamP par)
{
 BlkPtr blk;
 RetVal val;

 if(Find(x,y,&blk)==SUCCESS)
   {
   blk->GetParam(par);
   val=SUCCESS;
   }
 else val=ERROR;

 return val;
}

RetVal _screen::SetParam(CurT x,CurT y,ParamP par)
{
 BlkPtr blk;
 RetVal val=SUCCESS;

 if(Find(x,y,&blk)==SUCCESS)  blk->SetParam(par);
 else   val=ERROR;

 return val;
}


Word _screen::BlkSize(BlockT Blk)
{
  Word len;

     switch(Blk)
	      {
	      case EASY_ZVENO:  len=sizeof(EasyZvenoT); break;
	      case EASY_GEN:    len=sizeof(EasyGenT);   break;
	      case DIF_ZVENO:   len=sizeof(DifZvenoT);  break;
	      case DIF_GEN:     len=sizeof(DifGenT);    break;
	      default:          len=0;                  break;
	      }
  return len;
}



RetVal _screen::UnkGroup(Word *Group)
{
 RetVal val=ERROR;
 LstHdrP cur;
 BlkPtr blk;
 Word num=0,tmp;
 

 while(val==ERROR && ++num)
   {
   tmp=(Word)rand()%(Word)65530U;
   val=SUCCESS;
   cur=first;
   while(cur)    // по всем векторам
      {
      blk=cur->FirstBlk();
      while(blk)   // по всем блокам вектора
	 {
	 if(blk->GetGroup()==tmp) { val=ERROR; goto nextval; }
	 blk=cur->NextBlk();
	 }
      cur=cur->Next();
      }
   nextval:   ;
   }
 if(val==SUCCESS) *Group=tmp;
 return val;
}
