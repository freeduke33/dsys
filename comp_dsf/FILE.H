#ifndef __file_II_
#define __file_II_


#include "mainsys.h"

typedef DWord Ptr;
typedef struct _FileHeader FileHeaderT, *FileHeaderP;
typedef struct _BlockDef   BlockDefT,   *BlockDefP;

struct _FileHeader
{
 FileID  ID;

 Ptr   Scr;     // образ схемы д. системы
 Word  ScrNum;
 DWord ScrSize;
 Ptr   Icon;    // иконка обозначения д. системы
 Word  IconSize;
 Ptr   Blk;     // рабочая структура д. системы
 Word  BlkNum;
 DWord BlkSize;
 // ================================================================
 Ptr   _addBlk; // добавочная структура д. системы (после ???????)
 Word  _addBlkNum;
 DWord _addBlkSize;

 Ptr   GroupDesc;     // дескрипторы групп
 Word  GroupNum;
 DWord GroupDescSize; 
};


struct _BlockDef
{
  CurT x,y;      // позиция блока на экране
  Word Group;    // принадлежность к группе 
  BlockT Blk;    // тип блока
};

#endif
