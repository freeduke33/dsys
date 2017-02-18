@echo off
echo Erase old files ...
del ww\*.wbk 
del menu\*.pbk
del menu\*.err
del *.bak
arj a -u dsys_I ww\*.ww arc.bat menu\*.c *.h *.cpp *.hpp *.mak dsys.prj dirinfo