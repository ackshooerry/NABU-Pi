@echo off

echo.
echo ****************************************************************************

 zcc +z80 -mz80 -startup 0 -zorg 0x140D --no-crt -O3 --opt-code-speed -lm main.c -o "D:\NABU_Segments\000001.nabu"

:: zcc +z80 -mz80 -startup 0 -zorg 0x140D --no-crt -D__SDCC_ENABLE_FASTCALL --no-peep -lm main.c -o "C:\NABU Segments\000001.nabu"

:: zcc +z80 -mz80 -startup 0 -zorg 0x140D --no-crt -D__z88dk_fastcall --no-peep -lm main.c -o "C:\NABU Segments\000001.nabu"

:: zcc +z80 -mz80 -startup 0 -zorg 0x140D --no-crt -D__z88dk_fastcall --no-peep -lm main.c -o "C:\NABU Segments\000001.nabu"

:: zcc +z80 -mz80 -startup 0 -zorg 0x140D --no-crt -O3 --no-peep -lm main.c -o "C:\NABU Segments\000001.nabu"

echo ****************************************************************************

del "D:\NABU_Segments\000001.nabu"

move "D:\NABU_Segments\000001_code_compiler.bin" "D:\NABU_Segments\000001.nabu"

dir "D:\NABU_Segments"

