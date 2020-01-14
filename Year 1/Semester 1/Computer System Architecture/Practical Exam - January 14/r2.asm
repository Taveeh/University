bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern scanf, fopen, fprintf, fread, fclose, fscanf
import scanf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll 
import fscanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
	formatCitire DD '%s %c %d', 0
	space DD ' ', 0
	count DD 0
	fisierInput times 20 DD 0
	formatString DD '%s', 0
	formatChar DD '%c', 0
	formatDecimal DD '%d', 0
	number DD 0
	character DD 0
	readMode DD 'r', 0
	writeMode DD 'w', 0
	output DD 'output.txt', 0
	descriptorInput DD 0
	descriptorOutput DD 0
	cuvant DD 0

; our code starts here
segment code use32 class=code
	editWord:
		mov ESI, cuvant
		mov ECX, 0
		bucla:
			xor EAX, EAX
			lodsb
			inc ECX
			cmp ECX, [number]
			jg finalCuv
			push ECX
			push EAX
			push formatChar
			push dword[descriptorOutput]
			call [fprintf]
			add ESP, 4 * 3
			pop ECX
			cmp byte[ESI], 0
			jne bucla
			mov EDI, ESI
			mov EAX, [character]
			stosb
			jmp bucla
		finalCuv:
		push ECX
		push dword[space]
		push formatChar
		push dword[descriptorOutput]
		call [fprintf]
		add ESP, 4 * 3
		pop ECX
		dec ECX
		mov EDI, cuvant
		buclaCuv:
			mov EAX, 0
			stosb
		loop buclaCuv
			
		ret
	
    start:
        ; Read a the name of an input file, a special character(s) and a number(n). The file read contains words separated through spaces. Write in 'output.txt' the first n characters of each word. If the words has less than n characters, fill it with s
		;Read file name
		;push fisierInput
		;push formatString
		;call [scanf]
		;add ESP, 4 * 2
		
		; Read character
		;push character
		;push formatChar
		;call [scanf]
		;add ESP, 4 * 2
		
		; Read number
		;push number
	;	push formatDecimal
	;	call [scanf]
	;	add ESP, 4 * 2
		
		push number
		push character
		push fisierInput
		push formatCitire 
		call [scanf]
		add ESP, 4 * 4
		
		; Open input file
		push readMode
		push fisierInput
		call [fopen]
		add ESP, 4 * 2
		cmp EAX, 0
		je final
		mov [descriptorInput], EAX
		
		; Open output file
		push writeMode
		push output
		call [fopen]
		add ESP, 4 * 2
		cmp EAX, 0
		je final
		mov [descriptorOutput], EAX
		
		; Read from file
		mov dword[count], 0
		reading:
			push cuvant
			push formatString
			push dword[descriptorInput]
			call [fscanf]
			add ESP, 4 * 3
			cmp EAX, -1
			je final
			call editWord
			jmp reading
		final:
		
		push dword[descriptorInput]
		call [fclose]
		
		push dword[descriptorOutput]
		call [fclose]
		
		; Read from keyboard
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
