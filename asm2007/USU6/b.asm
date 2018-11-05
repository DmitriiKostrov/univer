text segment
	assume CS:text, DS:data
start:
;работа с клавиатурой
;выведем на экран запрос
	mov AX,data
	mov DS,AX
	mov AH,09h
	mov DX,offset msg
	int 21h
;поставим запрос на ввод
	mov AH,3Fh ; файловая функция ввода
	mov BX,0   ;дескриптор клавы
	mov CX,25  ;максимальное число символов
	mov DX,offset inbuf ;буфер ввода  !!!!!!!!!!!!!!!!!!!!!!
	int 21h


	mov AH,3Dh ;функция открытия файла
	mov AL,2   ;доступ для чтения - записи
	mov DX,offset fname
	int 21h
	mov handle,AX  ;сохранили число считанных байт(Необходимо будет при сравнении строк)
;поставим запрос на чтение 80 байт
	mov AH,3Fh ; функция чтения
	mov BX,handle
	mov CX,80
	mov DX,offset bufin; сюда
	int 21h
	mov CX,AX
	mov handle,CX
;выведем на экран прочитанное
	mov AH,40h
	mov BX,1
	mov DX,offset bufin         ; !!!!!!!!!!!!!!!!!!!!!!!!
	int 21h

;произведём сравение этих строк bufin и inbuf
        mov SI, offset inbuf
	push DS
	pop ES
	mov DI,offset bufin
	cld  ;вперёд по строке
	mov CX,handle   
repe	cmpsb
	jne no
yes:    mov AH,09h
	mov DX,offset stryes
	int 21h
	jmp exit
no:	mov AH,09h
	mov DX,offset strno
	int 21h
exit:   mov AX,4C00h
        int 21h

text ends


data segment
	msg db 'Введите строку : $'
	inbuf db 256 dup('*'),'$'
	bufin db 80 dup(' ') ;буфер
	handle dw 0         ;ячейка для дескрипта
	fname db 'FILE.001',0;имя файла в формате ASCIIZ
	stryes db ' Равны $'
	strno  db ' Не равны $'
data ends

end start