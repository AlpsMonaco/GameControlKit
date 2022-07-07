@echo off
cd /d project
clang-format.exe --style=file *.h *.cpp -i
cd ..