#include "string.h"
#include "path.hpp"


RetVal _path::SetFullName(DirP _dir,NameP name,char *tag,FileP _file)
{
 int i;
 char *dir=(char *)_dir,*file=(char *)_file;

 strcpy(file,"");
 if(dir[0])
   {
   strcat(file,dir);
   if(file[strlen(file)]!='\\') strcat(file,"\\");
   }

 strcat(file,(char *)name);
 for(i=strlen(file);i>=0 && file[i]!='\\';i--) if(file[i]=='.') file[i]=0;
 strcat(file,tag);

 return SUCCESS;
}

RetVal _path::InsMacro(CmdLineP file,char *macro,char *str)
{
 RetVal val;
 char *ptr;
 CmdLineT tmp;

 ptr=strstr((char *)file,macro);
 if(ptr)
   {
   strncpy((char *)tmp,ptr,sizeof(CmdLineT));
   ptr[0]=0;
   strncat((char *)file,str,sizeof(CmdLineT));
   ((char *)&file)[sizeof(CmdLineT)]=0;
   strncat((char *)file,&((char *)ptr)[strlen(macro)-1],sizeof(CmdLineT));
   ((char *)&file)[sizeof(CmdLineT)]=0;
   val=SUCCESS;
   }
 else val=ERROR;
 return val;
}


RetVal _path::GrabDir(FileP file,DirP path)
{
 int i;
 char *dir=(char *)path;

 memcpy(path,file,sizeof(DirT));
 for(i=strlen(dir);i>=0;i--) { if(dir[i]=='\\' ) break; }

 dir[i]=0;
 return SUCCESS;
}

RetVal _path::GrabName(FileP file,NameP name)
{
 int i;

 for(i=strlen((char *)file);i>=0;i--) if(((char *)file)[i]=='\\') break;
 strcpy((char *)name,&((char *)file)[i]);
 return SUCCESS;
}

RetVal _path::GrabTag(FileP file,char *tag)
{
 int i;
 
 for(i=strlen((char *)file);i>=0;i--) 
   {
   switch(((char *)file)[i]) 
      {
      case '\\': i=0;break;
      case '.':  strcpy(tag,&((char *)file)[i]);
                 return SUCCESS;
      }
   }
 strcpy(tag,".");
 return ERROR;  
}

