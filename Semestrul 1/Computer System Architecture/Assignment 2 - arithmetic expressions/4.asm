bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; (e + g) * 2 / (a *c ) + (h - f) + b * 3
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a DB 2
    b DB 7
    c DB 5
    e DW 11
    f DW 9
    g DW 15
    h DW 12

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov AX, [e] ; AX = e = 11
        add AX, [g] ; AX = e + g = 26
        mov BX, AX ; BX = AX = 26
        mov AL, 2 ; AL = 2
        mul BX  ; DX:AX = (e + g) * 2 = 52
        push DX
        push AX
        pop EBX ; EBX = DX:AX = 52
        mov AL, BYTE[a] ; AL = a = 2
        mul BYTE[c] ; AX = a * c = 10
        mov CX, AX ; CX = AX = 10
        mov EAX, EBX ; EAX = EBX = 52
        div CX ; AX = EAX / CX = 5, DX = EAX % CX = 2
        mov BX, AX ; BX = AX = 5
        mov AX, [h] ; AX = 12
        sub AX, [f] ; AX = h - f = 12 - 9 = 3
        add BX, AX ; BX = BX + AX = 5 + 3 = 8
        mov CL, BYTE[b] ; CX = 7
        mov AL, 3
        mul CL ; AX = AL * CL = 7 * 3 = 21
        add BX, AX ; BX = BX + AX = 8 + 21 = 29
        mov AX, BX
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
