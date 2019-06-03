IO_LED EQU P0;
ORG 0000H
LJMP MAIN
ORG 0030H
MAIN:
MOV IO_LED,#0xfe
LCALL DELAY
MOV IO_LED,#0xfd
LCALL DELAY
MOV IO_LED,#0xfb
LCALL DELAY
MOV IO_LED,#0xf7
LCALL DELAY
MOV IO_LED,#0xef
LCALL DELAY
MOV IO_LED,#0xdf
LCALL DELAY
MOV IO_LED,#0xbf
LCALL DELAY
MOV IO_LED,#0x7f
LCALL DELAY
LJMP MAIN

DELAY:MOV R3,#10
D1:MOV R4,#100
D2:MOV R5,#250
DJNZ R5,$
DJNZ R4,D2
DJNZ R3,D1
RET
END