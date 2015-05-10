@echo off

SET ASM=S:\ASM

cd src
%ASM%\RC JANE.RC
%ASM%\tasm32 /m /ml /n JANE, JANE, ..\JANE.lst
%ASM%\tlink32 -Tpe -aa -x -c JANE,..\JANE.exe,,,, JANE.res
del *.obj
del *.res
cd ..
pause