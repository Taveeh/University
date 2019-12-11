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
    a DB 5
    b DB 7
    c DB 12
    d DW 63
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov AX, [d] ; AX = d = 63
        add AX, 10 ; AX = d + 10 = 73
        mov CX, AX ; CX = AX = 73
        mov BL, [a] ; BL = a = 5
        mov AL, [a] ; AL = a = 5
        mul BL ; AX = AL * BL = 25
        mov BX, AX ; BX = AX = 25
        mov AL, 2 ; AL = 2
        mul BYTE[b] ; AX = AL * b = 2 * b = 14
        sub BX, AX ; BX = BX - AX = 25 - 14 = 11
        mov AX, CX ; AX = CX = 73
        sub AX, BX ; AX = Ax - BX = 73 - 11 = 62
        div BYTE[c] ; AL = AX / c = 62 / 12 = 5 , AH = AX % c = 62 % 12 = 2
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
