#include <tcxlinp.h>
#include <tcxlcod.h>
#include <tcxlmou.h>
#include <tcxlcur.h>

#include "edit.hpp"
#include "menu.h"


RetVal _edit::EdtPerform(NOARG)
{
 KeyT key;
 FileT nam;
 BlockT blk;

 MouPush(MOU_FULL);
 LoadCfg(1);
 SetFullName(GetDirWork(),(NameP)"NONAME",".DSF",&nam);
 if(FindFile(&nam,DEFAULT_ERROR)==ERROR) NewScr();
 else if(LoadScr(&nam)==ERROR) NewScr();

 for(;;)
   {
   WriteInfo();
   EdtCursor(CUR_ON);
   key=KeyGetc();
   EdtCursor(CUR_OFF);
   switch(key)
     {
     case Key_Ent:     Param();    break;
     case Key_BS:      PopGroup(); break;

     case Key_C_Q:     EdtSetPos(SCR.CurX,SCR.CurY); 
                       GetBlock(&blk);
                       DrawBlock(SCR.CurX,SCR.CurY,blk);
                       break;
     
     case Key_Lft:     EdtSetPos((IntT)SCR.CurX-1,(IntT)SCR.CurY  ); break;
     case Key_Rgt:     EdtSetPos((IntT)SCR.CurX+1,(IntT)SCR.CurY  ); break;
     case Key_Up:      EdtSetPos((IntT)SCR.CurX  ,(IntT)SCR.CurY-1); break;
     case Key_Dwn:     EdtSetPos((IntT)SCR.CurX  ,(IntT)SCR.CurY+1); break;

     case Key_C_Lft:   EdtSetPos((IntT)SCR.CurX-RangeX,(IntT)SCR.CurY       ); break;
     case Key_C_Rgt:   EdtSetPos((IntT)SCR.CurX+RangeX,(IntT)SCR.CurY       ); break;
     case Key_C_Up:    EdtSetPos((IntT)SCR.CurX       ,(IntT)SCR.CurY-RangeY); break;
     case Key_C_Dwn:   EdtSetPos((IntT)SCR.CurX       ,(IntT)SCR.CurY+RangeY); break;
     
     case Key_Home:    EdtSetPos((IntT)SCR.BegX+1     ,(IntT)SCR.CurY       ); break;
     case Key_End:     EdtSetPos((IntT)SCR.BegX+RangeX,(IntT)SCR.CurY       ); break;
     case Key_PgUp:    EdtSetPos((IntT)SCR.CurX       ,(IntT)SCR.BegY+1     ); break;
     case Key_PgDn:    EdtSetPos((IntT)SCR.CurX       ,(IntT)SCR.BegY+RangeY); break;

     case Key_C_Home:  EdtSetPos((IntT)MinRange+1,(IntT)SCR.CurY  ); break;
     case Key_C_End:   EdtSetPos((IntT)MaxRange  ,(IntT)SCR.CurY  ); break;
     case Key_C_PgUp:  EdtSetPos((IntT)SCR.CurX  ,(IntT)MinRange+1); break;
     case Key_C_PgDn:  EdtSetPos((IntT)SCR.CurX  ,(IntT)MaxRange  ); break;
     
     case Key_S_F3:    EDT_NEW();     break;
     case Key_S_F2:    SAVE_AS();     break;
     case Key_F2:      SaveScr();     break;
     case Key_F3:      EDT_LOAD();    break;
     case Key_F4:      Perform();     break;    // моделирование + графика
     case Key_F5:                     break;    // сценарий
     case Key_F7:      SHOW_RES();    break;    // графика
     case Key_F9:      Compile();     break;    // компиляция

     case Key_C_L:     EDT_LINE(); KquePut(Key_C_Q); break;
     case Key_C_A:     EDT_POIN(); KquePut(Key_C_Q); break;
     case Key_C_Z:     EDT_ZVEN(); KquePut(Key_C_Q); break;

     case Key_A_Z:     PutBlock(EASY_ZVENO); break;
     case Key_A_W:     PutBlock(DIF_ZVENO);  break;
     case Key_A_G:     PutBlock(EASY_GEN);   break;
     case Key_A_F:     PutBlock(DIF_GEN);    break;
     case Key_A_B:     PutBlock(DSYS_BEG);   break;
     case Key_A_E:     PutBlock(DSYS_END);   break;
     case Key_A_A:     PutBlock(BLK_ADD);    break;
     case Key_A_S:     PutBlock(BLK_SUB);    break;
     case Key_A_D:     PutBlock(BLK_DIV);    break;
     case Key_A_M:     PutBlock(BLK_MUL);    break;
     case Key_A_H:     PutBlock(BLK_HOR);    break;
     case Key_A_V:     PutBlock(BLK_VER);    break;
     case Key_A_L:     PutBlock(BLK_LEFT);   break;
     case Key_A_R:     PutBlock(BLK_RIGHT);  break;
     case Key_A_P:     PutBlock(BLK_NTR);    break;
     case Key_A_N:     PutBlock(BLK_NONE);   break;

     case Key_M_ClkR:
     case Key_M_DClkR:
     case Key_M_PrsR:
     case Key_M_RelR:  KquePut(Key_BS);break;

     case Key_M_ClkL:
     case Key_M_RelL:
     case Key_M_PrsL:
     case Key_M_DClkL:
		switch(MouRowS)
		  {
		  case 0:	//      выход в главное меню
		    KquePut(Key_M_ClkL);
		    KquePut(Key_F10);
		    break;
		  case 24:	//      hot-keys
		    if(MouColS<10) {KquePut(Key_F1); break;}
		    if(MouColS<23) {KquePut(Key_F2); break;}
		    if(MouColS<36) {KquePut(Key_F3); break;}
		    if(MouColS<53) {KquePut(Key_F4); break;}
		    if(MouColS<64) {KquePut(Key_F7); break;}
		    if(MouColS<73) {KquePut(Key_F10);break;}
		    break;
		  case 1:       //  move up
		    KquePut(Key_Up);
		    break;
		  case 23:	//  move down
		    KquePut(Key_Dwn);
		    break;
		  default:
		    if(MouColS<1)  // move left
		      {
		      KquePut(Key_Lft);
		      break;
		      }
		    if(MouColS>78) // move right
		      {
		      KquePut(Key_Rgt);
		      break;
		      }
		    if(key==Key_M_DClkL) KquePut(Key_Ent);
		    EdtSetPos((MouColS-1)/7+1,(MouRowS-2)/3+1);
		  }	
		break;
     default:          Sound(700,2);Sound(1700,2);KeyClear();break;
     }
   }
 return SUCCESS;
}
