text segment
	assume CS:text, DS:data
start:
	mov AH,3Ch ;функция создания файла
	mov CX,0   ;без атрибутов
	mov DX,offset fname ; Адрес имени файла
	int 21h
	mov handle,AX ;сохраним дескриптов файла
;запишем в файл данные
	mov AX,40h  ;функция записи в файл
	mov BX,handle ;дескриптор
	mov CX,7;buflen ; число записываемых байт
	mov DX, offset bufout ; адрес данных
	int 21h
;закроем файл 
	mov AH, 3Eh ; функция закрытия файла
	mov BX,handle 
	int 21h
	mov AX,4C00h


text ends


data segment
	bufout db 'Миру МИР'
	buflen = $ - bufout
	handle dw 0         ;ячейка для дескрипта
	fname db 'FILE.001',0;имя файла в формате ASCIIZ
data ends

end start