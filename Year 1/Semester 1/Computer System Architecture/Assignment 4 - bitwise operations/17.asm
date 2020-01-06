bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
;
; word A, byte B -> doubleword C
; C(0 - 3) = 1
; C(4 - 7) = A(0 - 3)
; C(8 - 13) = 0
; C(14 - 23) = A(4 - 13)
; C(24 - 29) = B(2 - 7)
; C(30 - 31) = 1
segment data use32 class=data
    ; ...
	a DW 0001010010100110b
	b DB 10010101b
	c DD 0
; c = 11100101010100101000000001101111b = E552806Fh
; our code starts here
segment code use32 class=code
    start:
        ; ...
		add dword[c], 1111b ; c = 0..01111b
		mov AX, [a] ; AX = 0001010010100110b
		and AX, 0000000000001111b ; AX = 0000000000000110b
		shl AX, 4 ; AX = 0000000001100000b
		add [c], AX ; c = 0..001101111b
		mov AX, [a] ; AX = 0001010010100110b
		and AX, 0011111111110000b
		mov DX, 0
		push DX
		push AX
		pop EAX
		shl EAX, 10
		add [c], EAX ; c = 0000000001010010100000000110111b
		mov AL, [b]
		and AL, 11111100b
		mov AH, 0
		mov DX, 0
		push DX
		push AX
		pop EAX
		shl EAX, 22
		add [c], EAX
		or dword[c], 11000000000000000000000000000000b
		
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
