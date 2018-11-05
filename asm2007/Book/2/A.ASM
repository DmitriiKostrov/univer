text segment
assume CS:text             ;, DS:data

begin:	mov AX,0F000h
	mov DS,AX
	mov AH,40h
	mov BX,1
	mov CX,8
	mov DX,0FFF5h
	int 21h
	mov AX,4C00h
	int 21h
text 	ends

;data 	segment
;	mesg db '!$'
;data 	ends
stk 	segment stack
	db 256 dup(0)
stk 	ends
	end begin