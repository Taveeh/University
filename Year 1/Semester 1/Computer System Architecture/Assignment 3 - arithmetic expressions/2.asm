bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
	a DB 95
	b DB 7
	c DW 5
	e DD 17
	x DQ 1800
	y DQ 0
; signed
; (100 + a + b * c) / (a - 100) + e + x / a
; our code starts here
segment code use32 class=code
    start:
        ; ...
		mov AL, byte[a]
		cbw
		add AL, 100 
		adc AH, 0 ; AX = 95 + 100 = 195
		mov BX, AX ; BX = 195
		mov AL, byte[b]  ; AL = 7
		cbw
		imul word[c] ; DX:AX = 35
		add AX, BX ; AX = 35 + 195 = 230
		adc DX, 0
		mov CX, AX
		mov AL, byte[a] ; AL = 95
		cbw
		sub AX, 100 ; AX = -5
		mov BX, AX
		mov AX, CX
		idiv BX
		; AX = -46
		cwde
		add EAX, dword[e] ; EBX = -46 + 17 = -29
		adc EDX, 0
		cdq
		mov dword[y], EAX
		mov dword[y + 4], EDX
		; y = -29
		mov AL, byte[a]
		cbw
		cwde
		mov EBX, EAX ; EBX = 95
		mov EAX, dword[x]
		mov EDX, dword[x + 4]
		; EDX:EAX = x = 1800
		idiv EBX
		;EAX = 1800 / 95 = 18
		cdq
		add EAX, dword[y]
		adc EDX, dword[y + 4]
		; EDX:EAX = -29 + 18 = -11
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
