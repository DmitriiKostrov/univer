; три одинаковых последовательных элемента
text segment public
	extrn test_three:NEAR
 	assume CS:text, DS:data

begin: 	mov AX,data
	mov DS,AX ; в DS адрес сегмента данных
	mov DX,offset Mass
	push DX
	push DS
	call test_three
	mov AX,4C00h
	int 21h	

data segment
     	Mass dw 12,1,1,28,28,28,123,6,12
data ends
stack segment stack
	db 256 dup(0)
stack ends
end begin