text segment public
public PutChar
     assume CS:text, DS: data

	
PutChar proc near
	push DS
	mov AX,data
	mov DS,AX
	mov AH,09h
	mov DX, offset String
	int 21h
	pop DS
	ret
PutChar endp   

stk segment stack
	db 256 dup(0)
stk ends

data segment 
	;Mass dw 123,3,1,4
	String db 'Vasay $'
data ends

text ends
end