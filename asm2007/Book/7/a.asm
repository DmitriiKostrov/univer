;организуется демонстрационнаый цикл из 10 шагов, которые будут
;выполнятся с задержкой прядка нескольких секунд
text segment
	assume CS:text,DS:data
begin:	mov CX,10 ;число шагов цикла
circle: push CX   ; сохранение счетчика в стеке
;выведем на экран контрольную строку из трёх символов
	mov AH,09h
	mov DX, offset string
	int 21h
;организуем программную задержку
	mov CX,10000
outer:	push CX
	mov CX,65535
inner:  loop inner
	pop CX
	loop outer
	pop CX
	loop circle
	mov AX,4C00h
	int 21h
text ends
data  segment
	string db '<> $'
data ends
stack segment stack
	db 256 dup(0)
stack ends
	end begin