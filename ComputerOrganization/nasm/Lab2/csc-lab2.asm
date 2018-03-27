; Christiaan Cronje
; COSC 2329.01
; 3/3/17

	org 100h

section .data	
prompt1 db	"Please enter a character: ",'$'
prompt2	db	"Please enter a digit 0-9: ",'$'
crlf	db	13,10,'$'

section .bss
char1	resw 1
num1	resw 1

section	.text
; print first prompt
	mov	ah,9		; display string function
	mov	dx,prompt1	; load dx with address of prompt1
	int	21h			; display
; get the char from the user
	mov	ah, 1		; read char fcn
	int	21h			; read it
	mov [char1], al
; go to the next line
	mov	ah, 9		; display string fcn
	mov	dx,crlf		; cr/lf pair
	int	21h
; echo the char entered
	mov	dl,[char1]		; move char into dl
	mov	ah, 2		; display char fcn
	int	21h			; display it

digitPrompt:
; go to the next line
	mov	ah, 9		; display string fcn
	mov	dx,crlf		; cr/lf pair
	int	21h
; print second prompt
	mov	ah,9		; display string function
	mov	dx,prompt2	; load dx with address of prompt2
	int	21h			; display
; get the char from the user
	mov	ah, 1		; read char fcn
	int	21h			; read it

; check if between 1 and 9
	cmp al,31h
	jl digitPrompt
	cmp al,39h
	jg digitPrompt
	mov [num1], al	; save in memory
; go to the next line
	mov	ah, 9		; display string fcn
	mov	dx,crlf		; cr/lf pair
	int	21h
; convert from digit to numeric val
	sub [num1], word 30h
	movzx cx, [num1]	; set counter

	mov ah, 2
	mov dl, [char1]		; mov char to dl
	int 21h				; print char to screen
print:
	inc word [char1]	; increase char1 by 1
	mov dl, [char1]		; mov char to dl
	int 21h				; print to screen
	loop print 			; repeat for counter length

; exit to DOS
	mov	ah,4Ch		; DOS exit fcn
	mov	al,0		; normal termination
	int	21h			; we're done
