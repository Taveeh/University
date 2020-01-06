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
	a DB 2, 1, 3, 3, 4, 2, 6
	len1 equ $ - a
	b DB 4, 5, 7, 6, 2, 1
	len2 equ $ - b
	len equ len1 + len2
	r times len DB 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
		mov ESI, b + len2 - 1 ; ESI = b
		mov ECX, len2
		mov EDI, r
		wow:
			std
			lodsb
			cld
			stosb
		loop wow
		cld
		mov ESI, a
		mov ECX, len1
		woow:
			lodsb
			test AL, 1
			jnz endd
			stosb
			endd:
		loop woow
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
