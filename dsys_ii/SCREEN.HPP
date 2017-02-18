#ifndef __screen_II_
#define __screen_II_

#include "dsys.h"
#include "block.hpp"
#include "param.hpp"

typedef class _LstHdr LstHdrT, *LstHdrP;

class _LstHdr
{
 private:

    LstHdrP next,prev;       // соседние списки
    LstHdrP *_last,*_first;  // ссылки на концы списка
    BlkPtr  dat;             // вектор
    Word    Size,num;        // размер,тек. положение


 public:
    _LstHdr(Word size,LstHdrP *first,LstHdrP *last);
   ~_LstHdr();

    BlkPtr FirstBlk(NOARG);
    BlkPtr NextBlk(NOARG);

    inline VOID Next(LstHdrP dat) { next=dat; }
    inline VOID Prev(LstHdrP dat) { prev=dat; }

    inline LstHdrP Next(NOARG) { return next; }
    inline LstHdrP Prev(NOARG) { return prev; }
};

class _screen:virtual public _param
{
 private:

  Word Size,Group;
  LstHdrP first,last,cur;
  BlkPtr cur_blk;

  RetVal NewArea(BlkPtr *blk);
  RetVal NewBlk(BlkPtr *blk);

  RetVal DelArea(NOARG);
  RetVal DelBlk(BlkPtr blk);

  RetVal Find(CurT x,CurT y,BlkPtr *blk);

 public:

   _screen();
  ~_screen();

  RetVal PutBlock(CurT x,CurT y,BlockT Blk);
  RetVal GetBlock(CurT x,CurT y,BlockP Blk);

  RetVal GetParam(CurT x,CurT y,ParamP Par);
  RetVal SetParam(CurT x,CurT y,ParamP Par);

  RetVal FirstBlock(BlkPtr *blk);
  RetVal NextBlock(BlkPtr *blk);

  RetVal MoveBlk(Short x,Short y);

  inline RetVal GetGroup(Word *group) { *group=Group; return SUCCESS; }
  inline RetVal SetGroup(Word group)  { Group=group;  return SUCCESS; }
  RetVal UnkGroup(Word *group);

  Word BlkSize(BlockT Blk);
};


#endif
