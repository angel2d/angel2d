@echo off
REM simple build file for the FreeImageNET.dll assembly

csc /target:library /out:FreeImageNET.dll *.cs
