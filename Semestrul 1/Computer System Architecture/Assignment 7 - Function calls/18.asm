bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern scanf
import scanf msvcrt.dll
extern printf
import printf msvcrt.dll
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
	n dd 0
	m dd 0
	a DD '%d', 0
	b DD '%x', 0
	c DD 0
	x DD '%d', 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
		push n
		push a
		call [scanf]
		add ESP, 2 * 4
		push m
		push b
		call [scanf]
		add ESP, 1 * 4
		mov EAX, dword[n]
		add EAX, dword[m]
		mov ECX, 32
		bucla:
			test EAX, 1
			jz final
			inc byte[c]
			final:
			shr EAX, 1
			loop bucla
		push dword[c]
		push x
		call [printf]
		
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
