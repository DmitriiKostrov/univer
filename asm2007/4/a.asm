;программа для вычисления суммы цифр числа 123
;ответом должно быть число 6
;однако нифига не работает


text segment
 	assume CS:text, DS:data

begin: 	mov AX,text
	mov DS,AX
	mov AX,123

	mov BX,10
	mov SI,0 ;счётчик для строки
loop1:	div bl
	add AH,'0'
	mov dl,ah
	mov answ[SI],DL
	inc SI
	mov ah,2h
	mov cl,al  ;сохраняем al т.к. int 21h ломает его
	int 21h    ;ломает AL
	mov al,cl
	mov ah,0
	cmp ax,0
	jg loop1
	



    	mov AH,40h	
	mov BX,1
	mov CX,1
	mov DX,offset answ[2]
	int 21h
	mov AH,40h
	mov BX,1
	mov CX,1	
	mov DX,offset answ[1]
	int 21h
	mov AH,40h
	mov BX,1
	mov CX,1	
	mov DX,offset answ[0]
	int 21h	
	mov AX,4C00h
	int 21h
	

text ends

data segment
	answ db ,':',3 dup('*'),'$'	
data ends

	end begin