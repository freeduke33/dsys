#ifndef __block_II_
#define __block_II_

#include "string.h"
#include "mainsys.h"


typedef class _block *BlkPtr;

class _block
{
 private:
  DefBlkT  info;
  Byte     act;
  ParamT   data;

 public:

  _block() { info.Dat=&data;act=0; }

  RetVal Init(CurT x,CurT y,Word Group,BlockT Blk,ParamP dta);
  RetVal Forget(NOARG) { act=0; return SUCCESS; }


  inline VOID GetParam(ParamP par) { memcpy(par,info.Dat,sizeof(*par)); }
  VOID SetParam(ParamP par);

  inline BlockT GetType(NOARG) { return info.Blk; }
  inline Byte   GetAct(NOARG)  { return act;      }

  inline CurT   GetX(NOARG)    { return info.x; }
  inline CurT   GetY(NOARG)    { return info.y; }

  inline Word   GetGroup(NOARG) { return info.Dat->Group; }

  RetVal UpdatePos(Short deltX,Short deltY);

};

#endif

