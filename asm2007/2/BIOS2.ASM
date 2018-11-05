model tiny
.code
org 100h
start:
jmp begin; jump to start execution
s1 db ' $'
s2 db 13,10,'$'
begin:
	
	xor di,di               
	xor cx,cx  ;mov cx, 0 no correct more OZY
	mov ax,0B800h
	mov es,ax
	cld
f1:
	mov al,cl
	stosb  	
	mov al,7
	stosb
	inc cl
	test cl,cl
	jnz f1	
	ret
 end start
