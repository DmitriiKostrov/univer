;программа отыскивает наименьший элемент массива и его номер
;model tiny
;.code

text segment
       	assume CS:text, DS:text
	org 100h
start:
	;mov AX,data
	;mov DS,AX
	
      	mov DX,Mass
	mov CX,8;счетчик
	mov BX,2;номер элемента массива
        mov AX,1; номер символа
cont:   cmp DX,Mass[BX] ; если первый операнд меньше, чем второй
	jl next        ;да, 
	mov DX,Mass[BX] ;нет,в DX заносим следующий элемен
	mov AX,BX
next:	inc BX
	inc BX
	loop cont
	
	shr AX,1 ;делит на 2
	inc Ax
	push DX
write:	;mov AX,DX
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

	pop DX
	mov AX,DX
	mov BX,10
	mov SI,0 ;счётчик для строки
loop2:	div bl
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
	jg loop2
    mov AX,4C00h
	int 21h
	Mass dw 123,4,12,23,25,1,17,123,123;
	answ db 3 dup('*'),'$'

;data segment
;	Mass dw 123,4,12,23,25,1,17,123,123;
;	answ db 3 dup('*'),'$'
;	;x db ?
;data ends

;stack segment stack
;	db 256 dup(0)
;stack ends
text ends 
        end start
	
	