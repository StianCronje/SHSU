	org 100h

section .data	
message db	"Hello, my name is Christiaan Cronje",13,10,'$'
prompt	db	"Please enter a character:  ",'$'
crlf	db	13,10,'$'

section	.text
; print greeting message
	mov	ah,9		; display string function
	mov	dx,message	; load dx with address of greeting
	int	21h		; display greeting
; prompt user for input
	mov	ah,9		; display string fcn
	mov	dx,prompt	; dx has addr of string
	int	21h		; display it
; get the char from the user
	mov	ah, 1		; read char fcn
	int	21h		; read it
; go to the next line
	mov	ah, 9		; display string fcn
	mov	dx,crlf		; cr/lf pair
	int	21h
; echo the char entered
	mov	dl,al		; move char into dl
	mov	ah, 2		; display char fcn
	int	21h		; display it
; exit to DOS
	mov	ah,4Ch		; DOS exit fcn
	mov	al,0		; normal termination
	int	21h		; we're done