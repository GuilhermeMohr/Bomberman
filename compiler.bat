@echo off

cd c:\mingw\bin
g++ %~dp0*.cpp %~dp0*.hpp -o %~dp0bomberman.exe

copy libgcc_s_dw2-1.dll %~dp0
copy "libstdc++-6.dll" %~dp0
cd "%~dp0"

@echo pressione qualquer tecla para finalizar
pause