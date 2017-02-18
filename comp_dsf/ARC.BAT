@echo off
del *.bak
pkzip -u comp_dsf *.cpp *.hpp *.h ..\file.h ..\mainsys.h dirinfo arc.bat
