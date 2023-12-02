@echo off
CD ../src

FOR /R %%f IN (*.cpp, *.cxx, *.c, *.h, *.hpp) DO (
    clang-format -i %%f
    echo %%f
)