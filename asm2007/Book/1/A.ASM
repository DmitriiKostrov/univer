text segment
assume CS:text, DS:data

begin:	mov AX,data
	mov DS,AX
	mov AH,09h
	mov DX,num
	int 21h
	mov AH,4Ch
	mov AL,0
	int 21h
text 	ends

data 	segment
	num dw 123,'$'
data 	ends
stk 	segment stack
	db 256 dup(0)
stk 	ends
	end begin