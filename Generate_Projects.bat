@echo off

echo ===============================================
echo ===============================================
echo ========REMORSE ENGINE SETUP  =================
echo ===============================================

call Tools\premake\premake5.exe --file=Make/premake5.lua vs2022

pause