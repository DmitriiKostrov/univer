;
;y= sqrt(x) , x>=0
;y = x , x<0

text segment
	assume CS:text, DS:data

start:
	mov AX,data
	mov DS,AX
	
	mov AH,0 ;функция установки графического режима
	mov AL,10h ; 640*350
	int 10h
	mov CX,400 ;число повторений цикла
	
;цикл вычисления координат и вывода точек на экран
; от -100 до 300   = итого 400 итераций
cont:   mov AX,x
	cmp AX,0  	 ;каждый раз в цикле проверяем x< 0
			 ;т.к. имеется знак, то смотрим OF SF ZF
	jge lineAbove    ;меньше

lineLess:	push CX
		fild x   ;  загрузили x = -100 в ячейку ST
		fistp y  ;  ST -> y
		mov AH,0Ch      ;функция вывода пиксела
	        mov AL,4	;цвет 4
		mov BH,0        ;видеостраница
		mov CX,x
		mov DX,0
		sub DX,y
		
	        int 10h
		inc x
		pop CX
	        loop cont


lineAbove:push CX ;сохраним CX, т.к. CX используется при выводе на экран графика
	fild x  ;зашлём x в ST
	fsqrt   ;корень из ST, результат там же сохранится
	fistp y ;содержимое ST идёт в y
	
	mov AH,0Ch ;функция вывода пиксела
	mov AL,4   ;цвет делаем
	mov BH,0   ;видеостраница 0

	push x

	add x,257  ;подстраиваем координаты (чтоб рисунок более менее выглядел)
	mov CX,x   ;номер столбца
	mov DX,100
	sub DX,y   ; номер строки

	pop x

	int 10h
	inc x
	pop CX
	loop cont



	mov AX,4C00h
	int 21h
text ends

data segment
        forcolor db 4 ; цвет
	x dw -100
	y dw ?
data ends
end start