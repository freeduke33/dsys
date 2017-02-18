#ifndef __edit_II_
#define __edit_II_

#include "io.hpp"
#include "compile.hpp"
#include "screen.hpp"
#include "icon.hpp"
#include "param.hpp"
#include "group.hpp"


typedef enum {CUR_ON, CUR_OFF} CurF;

class _edit: public _screen,_compile,_icon,virtual public _io,public _cfg
{
 private:
    Byte update;
    CurT RangeX,RangeY,MaxRange,MinRange;
    Byte ActCur;
    GroupP LstGroup;

  // ошибка
    Byte ErrX,ErrY;
    ErrT ErrNum;
  // рабочая схема
    ScrT SCR;
  // главная схема динамической системы
    ScrT BaseSCR;

    RetVal GetCurPos(IntP x,IntP y,CurT xx,CurT yy);
    RetVal EdtCursor(CurF Flag);
    RetVal Refresh(NOARG);
    RetVal DrawBlock(CurT x,CurT y,BlockT blk);
    RetVal Update(AskType ask);
    RetVal SetUpdate(CurF Flag);
    RetVal EdtNewPos(CurT x,CurT y);
    RetVal Exec(ExecP use,int mode);

    VOID CTYP WriteInfo(NOARG);
    VOID CTYP CurrFile(NOARG);
    VOID CTYP InitNew(FileP filename);

    RetVal PushGroup(Word Group);
    RetVal PopGroup(NOARG);

 public:
  // работа со всей схемой

    RetVal NewScr(NameP name);

    RetVal LoadScr(FileP filename);
    RetVal SaveScr(FileP filename);

//    inline RetVal LoadScr(DirP dir,NameP name) {return LoadScr(NewName(dir,name));}
//    inline RetVal SaveScr(DirP dir,NameP name) {return SaveScr(NewName(dir,name));}

    inline RetVal SaveScr(NOARG) { return SaveScr(&SCR.name); }
    inline RetVal NewScr(NOARG)  { return NewScr((NameP)"NONAME.DSF"); }

  // Имитационное моделирование
    RetVal Compile(NOARG);
    RetVal Perform(NOARG);
  // Работа с архивом
    RetVal Archive(int mode);

  // работа с элементами схемы
	 RetVal PutBlock(BlockT Blk);
  inline RetVal GetBlock(BlockP Blk)
			{return _screen::GetBlock(SCR.CurX,SCR.CurY,Blk);}

  // изменение параметров элемента схемы
  RetVal Param(NOARG);     //  ввод новых параметров звена

  inline RetVal SetParam(ParamP Blk)
			{return _screen::SetParam(SCR.CurX,SCR.CurY,Blk);}
  inline RetVal GetParam(ParamP Blk)
			{return _screen::GetParam(SCR.CurX,SCR.CurY,Blk);}
  inline RetVal DefBlock(BlockT Blk) 
                        {return _screen::PutBlock(SCR.CurX,SCR.CurY,Blk);}

  // редактирование схемы
    RetVal EdtPerform(NOARG);
    RetVal EdtSetPos(IntT x,IntT y);
    VOID   EdtExit(NOARG);

  //
    _edit();
   ~_edit();
};

#endif
