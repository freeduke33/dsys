#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include "mainsys.h"
typedef class group Group,*GroupP;

class group
{
 private:
    GroupP prev,*top;
    CurT x,y;
    Word group;
    
 public:
    inline group(GroupP *lst) { top=lst; prev=*lst; *lst=this; return; }
    inline ~group(NOARG)      { *top=prev; return; }
    
    inline CurT GetX(NOARG)     { return x; }
    inline CurT GetY(NOARG)     { return y; }
    inline Word GetGroup(NOARG) { return group; }
    inline VOID SetGroup(Word Group,CurT X,CurT Y) { group=Group;x=X;y=Y; }
};

#endif
