
#include "block.hpp"


VOID _block::SetParam(ParamP par)
{
 Word tmp=info.Dat->Group;
 
 memcpy(info.Dat,par,sizeof(*par));
 info.Dat->Group=tmp;

 return;
}

RetVal _block::Init(CurT x,CurT y,Word Group,BlockT Blk,ParamP par)
{
 act=1;
 info.x=x;
 info.y=y;
 info.Blk=Blk;
 info.Dat->Group=Group;
 SetParam(par);

 return SUCCESS;
}

RetVal _block::UpdatePos(Short dX,Short dY)
{
 if( (Short)info.x + dX <0 ) return ERROR;
 else info.x=(CurT) ( (Short)info.x+dX);

 if( (Short)info.y + dY <0 ) return ERROR;
 else info.y=(CurT) ( (Short)info.y+dY);

 return SUCCESS;
}



