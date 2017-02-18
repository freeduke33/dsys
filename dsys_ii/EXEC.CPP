#include <dos.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <errno.h>
#include <process.h>

#include <tcxlwin.h>
#include <tcxlinp.h>
#include <tcxlcur.h>
#include <tcxlstr.h>

#include "edit.hpp"
#include "file.h"
#include "swap.h"

// int __stklen=3000;

RetVal _edit::Compile(NOARG)
{
 RetVal val;
 
 if((val=Update(ASK_CONFIRM))==SUCCESS)
  {
  val=Exec(&GetCfg()->Compile,1);
  }
 return val;
}

RetVal _edit::Perform(NOARG)
{
 RetVal val;

 if((val=Update(ASK_CONFIRM))==SUCCESS)
   {
   val=Exec(&GetCfg()->Perform,0);
   }
 return val;
}

RetVal _edit::Archive(int mode)
{
 RetVal val;

 if((val=Update(ASK_CONFIRM))==SUCCESS)
   {
   val=Exec(&GetCfg()->Archive,mode);
   }
 return val;
}


RetVal _edit::Exec(ExecP use,int mode)
{
 static char key_str[]=" <Нажмите любую клавишу> ";
 static char time_str[]=" <Ожидание конца паузы> ";
 CmdLineT  cmd;
 RetVal val;
 FileT buf,tmp,tmp1;
 VcelP sav;
 FILE* f;
 CfgP cfg;
 int ff;

  cfg=GetCfg();
  strcpy((char *)&tmp,cfg->dir_tmp);
  close(creattemp((char *)&tmp,FA_ARCH));
  
  strcpy((char *)&tmp1,cfg->dir_tmp);
  ff=creattemp((char *)&tmp1,FA_ARCH);
  write(ff,cfg,sizeof(*cfg));
  close(ff);
  
  f=fopen((char *)&tmp,"w+t");
  if(f==NULL)
    {
    Wperror("Не могу создать файл параметров");
    unlink((char *)&tmp);
    unlink((char *)&tmp1);
    return ERROR;
    }
  else
    {
    switch(mode) 
       {
       case 0: fprintf(f,"PERFORM\n"); break;
       case 1: fprintf(f,"COMPILE\n"); break;
       case 2: fprintf(f,"ARCHIVE\n"); break;
       case 3: fprintf(f,"SHOW\n");    break;
       } 
       
    fprintf(f,"SCRFILE=%s\n",SCR.name);
    fprintf(f,"CFGFILE=%s\n",tmp1);
    fprintf(f,"SELFILE=%s\n","nil");
    fclose(f);
    }


   strcpy(cmd,use->cmd);
   strcpy(cmd,strtrim(cmd));
   sscanf(cmd,"%s",buf);
   val=InsMacro(&cmd,"$File",tmp);
   if(val!=SUCCESS)
      {
      strcat(cmd," ");
      strcat(cmd,tmp);
      }

   if(swap_iswindowon())  swap_windowoff();
   switch(use->win)
     {
     case inWINDOW:
       swap_windowon();
       swap_window(2,5,75,15);
       Wopen(4,0,21,78,BOX_DBL|BOX_EXP,_BLUE|WHITE,_BLUE|LGREY);
       Wtitle(cmd,TTL_CNT,_BLUE|WHITE);
       Wshadow(_BLACK|DGREY);
       break;
     case HIDDEN:
       swap_windowon(); 
       swap_window(0,24,78,1);
       Wopen(24,0,24,78,BOX_SPA,_BLUE|WHITE,_BLUE|LGREY);
     case inSCREEN:
       sav=Vsave();
       if(sav==NULL)
	  {
	  Wperror(" Нет свободной памяти для запуска компилятора ");
	  return ERROR;
	  }
	if(use->win==inSCREEN) clrscr();
	break;
     default:
        Wperror(" Internal: exec mode for child process is corrupted ");
        return ERROR;
     }
     
  if(!swap_ison()) swap_on();
  if(!swap_isfreeparagraphson()) swap_freeparagraphson();
  
  if(use->FreeMem) swap_freeparagraphs(use->FreeMem*64);
  else             swap_freeparagraphsoff(); 

  CurPush(CUR_SHO,CUR_NOR,0,0);
  MouHide();
  val= ? spawnlp(P_WAIT,buf,"",&cmd[strlen(buf)],NULL) ERROR : SUCCESS;
  MouShow();

  if(val==ERROR) 
    {
    switch(errno)
       {
       case ENOPATH:Wperror("Неверный каталог");                  break;
       case ENOENT: Wperror("Неверное имя файла или каталога");   break;
       case EACCES: Wperror("Доступ к файлу отвергнут");          break;
       case E2BIG:  Wperror("Слишком длинный список аргументов"); break;
       default:     Wperror("Не могу запустить подчиненный процесс");
       }
    }
  else switch(use->wait)
    {
    case WAIT_KEY:
       switch(use->win)
          { 
          case inWINDOW: Wmessage(key_str,BRD_BOT,5,_BLINK|_BLUE|WHITE); break;
          case inSCREEN: printf(key_str); break;
          case HIDDEN:   goto restore;
          }
       KeyWait();
       break;
    case NOWAIT_KEY:
       break;
    case WAIT_TIME:
       switch(use->win)
          { 
          case inWINDOW: Wmessage(time_str,BRD_BOT,5,_BLINK|_BLUE|WHITE); break;
          case inSCREEN: printf(time_str); break;
          case HIDDEN:   goto restore;
          }
       KeyTime(use->wtime);
       break;
    }
  restore:  
  switch(use->win)
     {
     case inWINDOW:
	Wclose();
	break;
     case HIDDEN:
	Vrestore(sav);
        Wclose();
        break;
     case inSCREEN:
	Vrestore(sav);
	break;
     }
 CurPop();

 unlink((char *)&tmp);
 unlink((char *)&tmp1);
 return val;
}
