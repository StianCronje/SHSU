; Christiaan Cronje
; COSC 2329.01
; 3/26/17

	org 100h

section .data	
prompt1 db	"Enter a Key (0-31): ",'$'
prompt2	db	"Enter a Message: ",'$'
crlf	db	13,10,'$'

section .bss
keyTemp	resw 1
num1	resw 1
char	resw 1

section	.text
; print first prompt
tooBigSmall:
	mov	ah,9		; display string function
	mov	dx,prompt1	; load dx with address of prompt
	int	21h			; display
	xor bx, bx	;store key in bx, fill 0
while1:
; get the char from the user
	mov	ah, 1		; read char fcn
	int	21h			; read it
	cmp al,30h		; is digit?
	jl done1		; jump is less than 0
	cmp al,39h
	jg done1		; jump if greater than 9
	mov ah, 0
	sub al, 30h		; convert char to number
	mov [keyTemp], ax	; store ax
	mov ax, bx		; mov to ax for mul
	mov cl, 10		; mul by 10
	mul cl
	mov bx, ax		; mov multiplied val to key
	add bx, word [keyTemp]	; add new digit
	jmp while1		; repeat while in range
done1:
	cmp bx, 0		; is within allowed range
	jl tooBigSmall 	; is less than 0
	cmp bx, 31
	jg tooBigSmall 	; is greater than 31

	mov cx, 0		; initialize counter to 0
; prompt user to enter the message
	mov	ah,9		; display string function
	mov	dx,prompt2	; load dx with address of prompt
	int	21h			; display
dowhile:
; read a character from the keyboard
	mov	ah, 1		; read char fcn
	int	21h			; read it
	cmp al, 13
	je endwhile		; while character is not the CR 

	xor ah, ah		;clear ah
	xor ax, bx		; char <-- char XOR key
	push ax			; push char on the stack
	inc cx			; increment the counter
	jmp dowhile
endwhile:
; go to the next line
	mov	ah, 9		; display string fcn
	mov	dx,crlf		; cr/lf pair
	int	21h

displayLoop:
	mov ah, 2		; prep to display char
	pop dx			; pop char off the stack
	int 21h			; display char
	loop displayLoop

; exit to DOS
	mov	ah,4Ch		; DOS exit fcn
	mov	al,0		; normal termination
	int	21h			; we're done
