;циклы
text segment
assume CS:text, DS: data
begin:
	mov AX,data
	mov DS,AX
;данные для организации цикла
	mov CX,223   ;число шагов в цикле
	mov SI,0     ;индекс элемента в заполняемом массиве
	mov AL,32    ;код первого символа пробела
;цикл с 4мя командами
fill:	mov symbols[SI],Al
	inc AL
	inc SI
	loop fill
;вывод массива на экран
	mov AH,40h
	mov BX,1
	mov CX,223
	mov DX,offset symbols
	int 21h
	
;end of prog
	mov AX,4C00h
	int 21h
text ends

data segment
	symbols db 223 dup('*')
data ends

stk segment stack
	db 256 dup(0)
stk ends
	end begin
