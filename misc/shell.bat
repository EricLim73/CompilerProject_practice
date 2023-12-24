@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
set path = w:\clox_project;w:\clox_project\misc;%path%
call W:\clox_project\4ed.bat
cls