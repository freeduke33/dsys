#ifndef __menu_II_
#define __menu_II_

#include "tcxldef.h"
#include "dsys.h"

#ifdef __cplusplus
  extern "C" {
#endif


#ifndef __Struct_WDEF_
#define __Struct_WDEF_

       struct _WDEF
         {
         IntT BegC,BegR,EndC,EndR;   /* положение окна    */
         IntT MniC,MniR,MaxC,MaxR;   /* возможные размеры */
         BytT FrmT;                  /* тип бордюра       */
         AtrT FrmA;                  /* атрибуты бордюра  */
         AtrT Dat;                   /* атрибуты текста   */
         BytT Shadow;                /* тень              */
         AtrT Sat;                   /* цвет тени         */
         };

#endif

// линии соединения
extern struct _WDEF WDEF_Hor,WDEF_Ver,WDEF_Left,WDEF_Right,
                    WDEF_Point,WDEF_None;
// арифметические узлы
extern struct _WDEF WDEF_Add,WDEF_Sub,WDEF_Mul,WDEF_Div;

// звенья д. системы
extern struct _WDEF WDEF_EasyZveno,WDEF_EasyGen,WDEF_DifZveno,WDEF_DifGen,
                    WDEF_BegSys,WDEF_EndSys;

 // вызовы внутри системы меню

 VOID CTYP CFG_DIR(NOARG);
 VOID CTYP CFG_MOD(NOARG);
 VOID CTYP CFG_RES(NOARG);

 VOID CTYP MOD_GLB (NOARG);
 VOID CTYP MOD_TEST(NOARG);
 VOID CTYP MOD_PROC(NOARG);

 VOID CTYP EDT_INFO(NOARG);
 VOID CTYP EDT_LOAD(NOARG);
 VOID CTYP EDT_LINE(NOARG);
 VOID CTYP EDT_POIN(NOARG);
 VOID CTYP EDT_ZVEN(NOARG);
 VOID CTYP SAVE_YN(NOARG);
 VOID CTYP EDT_SAVE(NOARG);
 VOID CTYP EDT_NEW(NOARG);
 VOID CTYP ZVENO_Z(NOARG);
 VOID CTYP ZVENO_P(NOARG);
 VOID CTYP ZVENO_D(NOARG);
 VOID CTYP GEN_E(NOARG);
 VOID CTYP GEN_D(NOARG);
 VOID CTYP NEW_ZD(NOARG);
 VOID CTYP NEW_GD(NOARG);

 VOID CTYP EdtLoad(char *name);

// функции рисования отдельных блоков
 VOID CTYP _EasyZveno_WRITE(NOARG);
 VOID CTYP _EasyGen_WRITE(NOARG);
 VOID CTYP _DifZveno_WRITE(NOARG);
 VOID CTYP _DifGen_WRITE(NOARG);
 VOID CTYP _BegSys_WRITE(NOARG);
 VOID CTYP _EndSys_WRITE(NOARG);
 VOID CTYP _Add_WRITE(NOARG);
 VOID CTYP _Sub_WRITE(NOARG);
 VOID CTYP _Mul_WRITE(NOARG);
 VOID CTYP _Div_WRITE(NOARG);
 VOID CTYP _Hor_WRITE(NOARG);
 VOID CTYP _Ver_WRITE(NOARG);
 VOID CTYP _Left_WRITE(NOARG);
 VOID CTYP _Right_WRITE(NOARG);
 VOID CTYP _Point_WRITE(NOARG);
 VOID CTYP _None_WRITE(NOARG);

 VOID CTYP _INFO_SET_WRITE(NOARG);
 VOID CTYP _INFO_CLR_WRITE(NOARG);


 // вызовы п/программ работы
RetVal CTYP EdtLoop(NOARG);
RetVal CTYP EdtPutBlock(BlockT blk);
RetVal CTYP EdtGetBlock(BlockP blk);
RetVal CTYP EdtPutParam(ParamP par);
RetVal CTYP EdtGetParam(ParamP par);
RetVal CTYP EdtSetPos(CurT x,CurT y);

VOID CTYP EdtCheckCfg(NOARG);
VOID CTYP EdtNewScr(char *file);
VOID CTYP InitEasyGenParam(NOARG);
VOID CTYP StoreEasyGenParam(NOARG);
VOID CTYP SAVE_CFG(NOARG);
VOID CTYP LOAD_CFG(NOARG);
VOID CTYP EdtExit(NOARG);
VOID CTYP SHOW_RES(NOARG);
VOID CTYP ARCHIVE(NOARG);
VOID CTYP SAVE_AS(NOARG);

CfgP CTYP EdtGetCfg(NOARG);

#ifdef __cplusplus
   }
#endif


#endif
