bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ... signed
	a DB 180
	b DB 7
	c DW 5
	e DD 12
	x DQ 1800
	y DD 0
; (100 + a + b * c) / (a - 100) + e + x / a
; our code starts here
segment code use32 class=code
    start:
        ; ...
		mov AL, byte[a] ; AL = 180
		mov AH, 0
		add AL, 100 ; AL = 100 + 180 = 280
		adc AH, 0 ; just to be sure
		mov BX, AX ; BX = 280
		mov AL, byte[b] ; AL = 7
		mov AH, 0
		mul word[c] ; DX:AX = 7 * 5 = 35
		; AX = 100 + a + b * c = 315
		add AX, BX
		adc DX, 0
		mov CL, byte[a] ; CL = 180
		mov CH, 0
		sub CL, 100 ; CL = 180 - 100 = 80
		div CX
		mov DX, 0 ; DX = 0, AX = (100 + a + b * c) / (a - 100) = 315 / 80 = 3
		push DX
		push AX
		pop EAX
		add EAX, dword[e] ; EAX = (100 + a + b * c) / (a - 100) + e = 15
		mov [y], EAX ; y = 15
		mov BL, byte[a]
		mov BH, 0
		mov CX, 0
		push CX
		push BX
		pop EBX
		mov EAX, dword[x]
		mov EDX, dword[x + 4]
		div EBX ; EAX = 10
		add EAX, [y] ; EAX = 15 + 10 = 25
		adc EDX, 0
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
