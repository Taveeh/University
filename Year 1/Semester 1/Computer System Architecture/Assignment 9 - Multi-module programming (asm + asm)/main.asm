bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
%include "CircularPermutation.asm"
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
extern printf
import printf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
	numar DD 12345678h
	format DD '%x'
	endline DD 10
	char DD '%c'

; our code starts here
segment code use32 class=code
    start:
        ; ...
		mov ECX, 8
		roteste:
			pushad
			push dword[numar]
			push format
			call [printf]
			add ESP, 4 * 2
			push dword[endline]
			push char
			call [printf]
			add ESP, 4 * 2
			push numar
			call permutare
			add ESP, 4
			popad
		loop roteste
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
