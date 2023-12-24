#!/bin/bash

code="$PWD"
opts=-g
cd w:\clox_project\build > /dev/null
g++ $opts $code/code/main.c -o clox.exe
cd $code > /dev/null
