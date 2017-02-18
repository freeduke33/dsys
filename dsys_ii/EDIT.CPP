#include <tcxlwin.h>
#include <tcxlinp.h>
#include <tcxlcur.h>

#include <stdlib.h>
#include <stdio.h>
#include <values.h>
#include <alloc.h>

#include "edit.hpp"
#include "menu.h"


_edit::_edit()
{
 SCR.CurX=1;
 SCR.CurY=1;
 RangeX=11;
 RangeY=7;
 MaxRange=0x7F;
 MinRange=0x00;
 ActCur=0;
 update=0;
 return;
}

_edit::~_edit()
{
 return;
}



RetVal _edit::EdtCursor(CurF f)
{
 IntT x,y,i;
 static VcelT buf[3][10];

 GetCurPos(&x,&y,SCR.CurX,SCR.CurY);
 for(i=0;i<3;i++)
   {
   switch(f)
     {
     case CUR_OFF:
	Vprintb(y+i,x,(VcelP)&buf[i],7);
        ActCur=0;
        break;
     case CUR_ON:
        Vgetb(y+i,x,(VcelP)&buf[i],7);
        Vgotoxy(y+i,x);
        VatrSet(_WHITE|BLACK|_BLINK,7);
        ActCur=1;
        break;
     }
  }
 return SUCCESS;
}

RetVal _edit::GetCurPos(IntP x,IntP y,CurT CurX,CurT CurY)
{
 WdfP win;
 RetVal val;

 win=WinLoc(Whandle());
 if(win)
   {
   *x=WdfBegC(win)+(CurX-1-SCR.BegX)*7+1;
   *y=WdfBegR(win)+(CurY-1-SCR.BegY)*3+2;
   val=SUCCESS;
   }
 else val=ERROR;

 return val;
}

RetVal _edit::EdtSetPos(IntT x,IntT y)
{
 ShortT dX=0,dY=0;
 char buf[128];

 if(x<=MinRange || x>MaxRange ||
    y<=MinRange || y>MaxRange  )
       {
       Sound(10000,3);
       KeyClear();
       }
       
 if(x<=MinRange)  x=MinRange+1;
 if(y<=MinRange)  y=MinRange+1;
 if(x> MaxRange)  x=MaxRange;
 if(y> MaxRange)  y=MaxRange;
 
 if(x<=SCR.BegX)  { dX=x-SCR.BegX-1; }
 if(y<=SCR.BegY)  { dY=y-SCR.BegY-1; }
 if(x>SCR.BegX+RangeX)  { dX=x-SCR.BegX-RangeX; }
 if(y>SCR.BegY+RangeY)  { dY=y-SCR.BegY-RangeY; }

       
 if(dX || dY)  // смещаем координаты и перерисовываем изображение
       {
       SCR.BegX+=dX;
       SCR.BegY+=dY;
       Refresh();
       }
   
 SCR.CurX=x;   // изменяем положение курсора
 SCR.CurY=y;
   
 // рисуем координаты и линейку
 sprintf(buf,"╡%3d,%3d╞",SCR.CurX,SCR.CurY);
 Vprints(23,9,_CYAN|WHITE,buf);
 return SUCCESS;
}

RetVal _edit::Refresh(NOARG)
{
 BlockT blk;
 RetVal val;
 CurT   x,y;
 int    dx,dy;
 Byte   tmp;
 Word   num,rx,ry,bx,by;

 MouPush(MOU_NONE);
 tmp=ActCur;
 if(tmp) EdtCursor(CUR_OFF);

 x=SCR.BegX;y=SCR.BegY+1;
 bx=x+1;by=y;
 rx=RangeX+SCR.BegX;ry=RangeY+SCR.BegY;
 dx=1;dy=0;
 for(num=0;num<RangeX*RangeY;num++)
      {
      if(x==rx && dx== 1) {dx= 0;dy= 1;by++;}
      if(x==bx && dx==-1) {dx= 0;dy=-1;ry--;}
      if(y==ry && dy== 1) {dx=-1;dy= 0;rx--;}
      if(y==by && dy==-1) {dx= 1;dy= 0;bx++;}

      x+=dx;
      y+=dy;

      val=_screen::GetBlock(x,y,&blk);
      if(val==SUCCESS) DrawBlock(x,y,blk);
      else             DrawBlock(x,y,BLK_NONE);
      }

 WriteInfo();
 CurrFile();
 if(tmp) EdtCursor(CUR_ON);
 MouPop();

 return SUCCESS;
}

// ========================[ работа с блоками ]========================
struct _array
  {
   BlockT Blk;
   struct _WDEF* win;
   VOID (CTYP *Func)(NOARG);
  };


RetVal _edit::PutBlock(BlockT blk)
{
 RetVal val;

 val=DefBlock(blk);                                      // определяем
 if(val==SUCCESS) val=DrawBlock(SCR.CurX,SCR.CurY,blk);  // рисуем

 SetUpdate(CUR_ON);

 return val;
}

RetVal _edit::DrawBlock(CurT x,CurT y,BlockT blk)
{
 Byte tmp;
 IntT xx,yy,i;
 struct _array *ptr;

 static struct _array array[]={
   {BLK_NONE,  &WDEF_None,     _None_WRITE     },
   {EASY_ZVENO,&WDEF_EasyZveno,_EasyZveno_WRITE}, 
   {DIF_ZVENO, &WDEF_DifZveno, _DifZveno_WRITE },
   {EASY_GEN,  &WDEF_EasyGen,  _EasyGen_WRITE  }, 
   {DIF_GEN,   &WDEF_DifGen,   _DifGen_WRITE   },
   {DSYS_BEG,  &WDEF_BegSys,   _BegSys_WRITE   }, 
   {DSYS_END,  &WDEF_EndSys,   _EndSys_WRITE   },
   
   {BLK_ADD,   &WDEF_Add,      _Add_WRITE}, 
   {BLK_SUB,   &WDEF_Sub,      _Sub_WRITE},
   {BLK_MUL,   &WDEF_Mul,      _Mul_WRITE}, 
   {BLK_DIV,   &WDEF_Div,      _Div_WRITE},
   
   {BLK_HOR,   &WDEF_Hor,      _Hor_WRITE  }, 
   {BLK_VER,   &WDEF_Ver,      _Ver_WRITE  },
   {BLK_LEFT,  &WDEF_Left,     _Left_WRITE }, 
   {BLK_RIGHT, &WDEF_Right,    _Right_WRITE},
   {BLK_NTR,   &WDEF_Point,    _Point_WRITE}, 
   
   {BLK_NONE,  NULL,           NULL}};

   ptr=&array[0];
   for(i=1;array[i].Func!=NULL;i++)
               if(array[i].Blk==blk) { ptr=&array[i]; break; }
   
   if(x<SCR.BegX || x>SCR.BegX+RangeX ||
      y<SCR.BegY || y>SCR.BegY+RangeY )  return SUCCESS;

   tmp=ActCur;                  // Убрать курсор
   if(tmp) EdtCursor(CUR_OFF);
   
   GetCurPos(&xx,&yy,x,y); // взять абсолютное положение курсора
   
   ptr->win->BegC=xx;     // изменить положение блока
   ptr->win->BegR=yy;
   ptr->win->EndC=xx+6;
   ptr->win->EndR=yy+2;
   ptr->Func();           // нарисовать блок
   
   if(tmp) EdtCursor(CUR_ON);   // Восстановить курсор

 return SUCCESS;
}


RetVal _edit::SetUpdate(CurF Flag)
{
 switch(Flag)
   {
   case CUR_ON:  update=1; break;
   case CUR_OFF: update=0; break;
   default:      ExitError("Invalid update flag");
   }
 WriteInfo();
 return SUCCESS;
}


RetVal _edit::EdtNewPos(CurT x,CurT y)
{
 Byte tmp=ActCur;

 if(tmp) EdtCursor(CUR_OFF);
 EdtSetPos(x,y);
 if(tmp) EdtCursor(CUR_ON);

 return SUCCESS;
}

VOID CTYP _edit::WriteInfo(NOARG)
{
 if(update)  _INFO_SET_WRITE();
 else        _INFO_CLR_WRITE();
 
 return;
}

VOID CTYP _edit::CurrFile(NOARG)
{

   Wopen(1,10,1,77,BOX_SPA,0,_CYAN|WHITE);
   WsetFil('═');
   Wclear();
   Wputf("╡ %s ╞",SCR.name);
   WsetFil(' ');
   Wunlink(Whandle());
   
 return;
}

RetVal _edit::Param(NOARG)
{
 BlockT blk;
 ParamT old;
 RetVal val;

 EdtGetBlock(&blk);
 GetParam(&ParBuf);
 GetParam(&old);
 switch(blk)
   {
   case EASY_ZVENO:   ZVENO_Z();     break;
   case EASY_GEN:     GEN_E();       break;
   case DIF_ZVENO:    
            switch(ParBuf.U.DifZveno.Group)  
              {
              case -1: NEW_ZD();      
                       if(ParBuf.U.DifZveno.Group==-2) 
                          {
                          val=UnkGroup(&ParBuf.U.DifZveno.Group);
                          if(val!=SUCCESS) ParBuf.U.DifZveno.Group=-1;
                          }
                       break;  // новое звено
              case  0: ZVENO_D();     break;  // звено в файле
              default: PushGroup(ParBuf.U.DifZveno.Group);  // звено в группе
              }
            break;  
   case DIF_GEN:      GEN_D();       break;
//   default:           Beep();        break;
   }
 if(memcmp(&old,&ParBuf,sizeof(old)))
   {
   SetParam(&ParBuf);
   SetUpdate(CUR_ON);
   }
 return SUCCESS;
}

VOID _edit::EdtExit(NOARG)
{
 RetVal val;

 val=Update(ASK_CONFIRM);
 if(val==SUCCESS)
   {
   WcloseAll();
   exit(0);
   }
 return;
}


RetVal _edit::PushGroup(Word Group)
{
 RetVal val;
 GroupP tmp;
 Word g;
  
 tmp=new group(&LstGroup);
 if(tmp!=NULL) 
    {
    GetGroup(&g);
    tmp->SetGroup(g,SCR.CurX,SCR.CurY);
    SetGroup(Group);
    EdtSetPos(1,1);
    Refresh();
    val=SUCCESS;
    }
 else { Wperror("Нет свободной памяти"); val=ERROR; }
 
 return val;
}


RetVal _edit::PopGroup(NOARG)
{
 RetVal val;

   if(LstGroup)
      {
      SetGroup(LstGroup->GetGroup());
      EdtSetPos(LstGroup->GetX(),LstGroup->GetY());
      delete LstGroup;
      Refresh();
      val=SUCCESS;
      }
   else {Beep(); val=ERROR;}

 return val;
}
