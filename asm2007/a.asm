text segment
	assume CS:text, DS:data
myproc proc
	mov AX,data
	mov DS,AX
	fild x
	fild y
	fadd 
	fistp z
	mov AX,4C00h
	int 21h
myproc endp
text ends

data segment
	x dw 1
	y dw 2
	z dw ?
data ends
end myproc