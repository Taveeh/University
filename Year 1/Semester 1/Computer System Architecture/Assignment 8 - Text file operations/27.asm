bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fread, fclose, fopen, printf, fprintf
               ; tell nasm that exit exists even if we won't be defining it
import fread msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll

import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
	fisier DB "date.txt", 0
	d_f resd 1
	how DB "r+", 0
	nr DB 0
	aux DD 0
	f DD '%d', 0
	formatnew DD '%c', 0
	maxi DD 0FFFFh
	zece DD 10	
	newline DD 10

; our code starts here
segment code use32 class=code
    start:
        ; ...
		push how
		push fisier
		call [fopen]
		add ESP, 2 * 4
		cmp EAX, 0
		je final
		mov [d_f], EAX
		mov EBX, 0
		mov EAX, 0
		bucla:
			push dword[d_f]
			push 1
			push 1
			push nr
			call [fread]
			add ESP, 4 * 4
			cmp AX, 0
			je final
			add ESP, 2 * 4
			mov AX, BX
			cmp byte[nr], ' '
			jne nuspatiu
			cmp BX, word[maxi]
			ja numaxi
			mov dword[maxi], EAX
			mov EAX, 0
			mov EBX, 0
			mov word[nr], '0'
			jmp numaxi
			nuspatiu:
				sub dword[nr], '0'
				mul dword[zece]
				add EAX, dword[nr]
				mov EBX, EAX
			numaxi:
			jmp bucla
		final:
		cmp BX, word[maxi]
		ja numaxi2
		mov [maxi], BX
		numaxi2:
		push dword[newline]
		push formatnew
		push dword[d_f]
		call [fprintf]
		add ESP, 2 * 4
		push dword[maxi]
		push f
		push dword[d_f]
		call [fprintf]
		add ESP, 2 * 4
		
		push dword[d_f]
		call [fclose]
		
			
		
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
