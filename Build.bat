@echo off

if exist "Bin" (
    RD /S /Q "Bin"
)
MD "Bin"
clang -o Bin\Set_Data_Structure.exe Test\*.c Src\*.c Singly_Linked_List\Src\*.c -IInclude -I Singly_Linked_List\Include\Singly_Linked_List.h
Bin\Set_Data_Structure.exe