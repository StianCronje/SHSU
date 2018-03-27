    org 100h

CR  equ 13
section .bss
str1    resb 80 ;strs to compare
str2    resb 80
len1    resw 1  ; lenghts of strings
len2    resw 1

section .data
prompt  db "Enter a string: ", '$'
out1    db "String 1 is smaller", '$'
out2    db "String 2 is smaller", '$'

section .code
; print prompt
    mov dx, prompt
    mov ah, 9       ; print string func
    int 21h         ; print prompt
; read first string
    xor cx, cx      ; cx = 0
    mov di, str1    ; set di to address of str 1
    cld             ; store char left to right
    mov ah, 1
    int 21h         ; read char into al
top1:
    cmp al, CR      ; if return, exit
    je exit1
    inc cx
    stosb           ; store string in str1
    int 21h         ; read char
    jmp top1
exit1:
    mov [len1], cx  ; mov char count to length
; read second string
    xor cx, cx      ; cx = 0
    mov di, str2    ; set di to address of str 1
    cld             ; store char left to right
    mov ah, 1
    int 21h         ; read char into al
top2:
    cmp al, CR      ; if return, exit
    je exit2
    inc cx
    stosb           ; store string in str1
    int 21h         ; read char
    jmp top2
exit2:
    mov [len2], cx  ; mov char count to length

; start comparison
    mov si, str1    ; set address of string 1
    mov di, str2    ; set address of string 2

    cmp cx, [len1]  ; compare string lenghts
    jle skip        ; str2 is already shorter
    mov cx, len1    ; make shortest string the counter
skip:
    repe cmpsb      ; repeat while equal, compare string bytes
    jl str1Smaller
    jg str2Smaller
; string are equal, check length
    mov cx, [len2]
    cmp cx, [len1]
    jl str1Smaller
    jg str2Smaller
str1Smaller:
    mov dx, out1
    jmp display
str2Smaller:
    mov dx, out2
display:
    mov ah, 4Ch
    mov al, 0
    int 21h