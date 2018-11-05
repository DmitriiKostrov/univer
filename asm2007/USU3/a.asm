text segment public
	extrn pr:NEAR
	assume CS:text,DS:data
start:
	mov AX,data
	mov DS,AX
	mov r_fact,1
	mov AX,4
	push AX
	call fact
	mov AX,4C00h
	int 21h

fact proc
	push bp
	mov bp,sp
	mov cx,[bp+4]
	mov ax,cx
	mul r_fact
	mov r_fact,ax
	dec cx
	jz end_p
	push cx
	call fact
end_p:  mov sp,bp
	pop bp
	ret 
fact endp

text ends
	
data segment
	n db 4
	r_fact dw 0
data ends

end start