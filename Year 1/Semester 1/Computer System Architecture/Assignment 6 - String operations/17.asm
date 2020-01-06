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
	sir DD 12345678h, 1256ABCDh, 12AB4344h
	len equ ($ - sir) / 4
	rez1 times len DW 0
	rez2 times len DD 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
		cld
		mov ESI, sir
		mov ECX, len
		mov EDI, rez1
		bucla:
			lodsw
			stosw
			lodsw
		loop bucla
		mov EDX, len
		mov ESI, rez1
		sort1:
			mov ECX, len
			mov AX, [ESI]
			sort2:
				cmp AX, [ESI + 2]
				ja ok
				xchg AX, [ESI + 2]
				mov [ESI], AX
				ok:
					add ESI, 2
					loop sort2
				dec EDX
				jnz sort1
		mov ESI, rez1
		mov ECX, len
		mov EDI, rez2
		mov EDX, 0
		final:
			lodsw
			stosw
			mov AX, word[sir + EDX + 2]
			mov [EDI], AX
			add EDI, 2
			add EDX, 4
			loop final
				
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
