.AUTODEPEND

.PATH.obj = BIN
.PATH.c   = MENU

#		*Translator Definitions*
CC = bcc +DSYS.CFG
TASM = TASM
TLINK = tlink


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
  ..\libs\swap_l.obj \
  block.obj \
  param.obj \
  screen.obj \
  io.obj \
  common.obj \
  file.obj \
  edit.obj \
  edit2.obj \
  path.obj \
  icon.obj \
  exec.obj \
  desc.obj \
  save_as.obj \
  cfg_dir.obj \
  cfg_mod.obj \
  cfg_res.obj \
  edt_info.obj \
  edt_load.obj \
  edt_line.obj \
  edt_poin.obj \
  edt_zven.obj \
  mod_glb.obj \
  mod_test.obj \
  main_mnu.obj \
  save_yn.obj \
  edt_new.obj \
  gen_d.obj \
  gen_e.obj \
  zveno_d.obj \
  zveno_z.obj \
  new_gd.obj \
  new_zd.obj \
  d:\bc\tcxl\_tcxlbcl.lib \
  d:\bc\tcxl\tcxlbcl.lib \
  ..\libs\expand_l.lib

#		*Explicit Rules*
bin\dsys.exe: dsys.cfg $(EXE_dependencies)
  $(TLINK) /yx/v/x/i/c/C/LD:\BC\LIB;D:\BC\TCXL;..\LIBS @&&|
c0l.obj+
..\libs\swap_l.obj+
bin\block.obj+
bin\param.obj+
bin\screen.obj+
bin\io.obj+
bin\common.obj+
bin\file.obj+
bin\edit.obj+
bin\edit2.obj+
bin\path.obj+
bin\icon.obj+
bin\exec.obj+
bin\desc.obj+
bin\save_as.obj+
bin\cfg_dir.obj+
bin\cfg_mod.obj+
bin\cfg_res.obj+
bin\edt_info.obj+
bin\edt_load.obj+
bin\edt_line.obj+
bin\edt_poin.obj+
bin\edt_zven.obj+
bin\mod_glb.obj+
bin\mod_test.obj+
bin\main_mnu.obj+
bin\save_yn.obj+
bin\edt_new.obj+
bin\gen_d.obj+
bin\gen_e.obj+
bin\zveno_d.obj+
bin\zveno_z.obj+
bin\new_gd.obj+
bin\new_zd.obj
bin\dsys
		# no map file
d:\bc\tcxl\_tcxlbcl.lib+
d:\bc\tcxl\tcxlbcl.lib+
..\libs\expand_l.lib+
fp87.lib+
mathl.lib+
cl.lib
|


#		*Individual File Dependencies*
block.obj: block.cpp 

param.obj: param.cpp 

screen.obj: screen.cpp 

io.obj: io.cpp 

common.obj: common.cpp 

file.obj: file.cpp 

edit.obj: edit.cpp 

edit2.obj: edit2.cpp 

path.obj: path.cpp 

icon.obj: icon.cpp 

exec.obj: exec.cpp 

desc.obj: desc.cpp 

save_as.obj: menu\save_as.c 
#	$(CC) -c menu\save_as.c

cfg_dir.obj: menu\cfg_dir.c 
#	$(CC) -c menu\cfg_dir.c

cfg_mod.obj: menu\cfg_mod.c 
#	$(CC) -c menu\cfg_mod.c

cfg_res.obj: menu\cfg_res.c 
#	$(CC) -c menu\cfg_res.c

edt_info.obj: menu\edt_info.c 
#	$(CC) -c menu\edt_info.c

edt_load.obj: menu\edt_load.c 
#	$(CC) -c menu\edt_load.c

edt_line.obj: menu\edt_line.c 
#	$(CC) -c menu\edt_line.c

edt_poin.obj: menu\edt_poin.c 
#	$(CC) -c menu\edt_poin.c

edt_zven.obj: menu\edt_zven.c 
#	$(CC) -c menu\edt_zven.c

mod_glb.obj: menu\mod_glb.c 
#	$(CC) -c menu\mod_glb.c

mod_test.obj: menu\mod_test.c 
#	$(CC) -c menu\mod_test.c

main_mnu.obj: menu\main_mnu.c 
#	$(CC) -c menu\main_mnu.c

save_yn.obj: menu\save_yn.c 
#	$(CC) -c menu\save_yn.c

edt_new.obj: menu\edt_new.c 
#	$(CC) -c menu\edt_new.c

gen_d.obj: menu\gen_d.c 
#	$(CC) -c menu\gen_d.c

gen_e.obj: menu\gen_e.c 
#	$(CC) -c menu\gen_e.c

zveno_d.obj: menu\zveno_d.c 
#	$(CC) -c menu\zveno_d.c

zveno_z.obj: menu\zveno_z.c 
#	$(CC) -c menu\zveno_z.c

new_gd.obj: menu\new_gd.c 
#	$(CC) -c menu\new_gd.c

new_zd.obj: menu\new_zd.c 
#	$(CC) -c menu\new_zd.c

#		*Compiler Configuration File*
dsys.cfg: dsys.mak
  copy &&|
-ml
-2
-f287
-v
-y
-G
-O
-Z
-d
-h
-H=DSYS.SYM
-Fc
-wpin
-wamb
-wamp
-wasm
-wpro
-wcln
-wdef
-wsig
-wnod
-wstv
-wucp
-wuse
-nBIN
-ID:\BC\INCLUDE;D:\BC\TCXL\INC;..\LIBS
-LD:\BC\LIB;D:\BC\TCXL;..\LIBS
-Ff
-Qx
| dsys.cfg


