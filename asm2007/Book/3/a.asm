; программа удаления файла.
; используются функции ДОС и анализируется флаг переноса.
;задача 7.1 из книги
text	 segment
assume 	CS:text, DS:data
begin:  mov AX,data
	mov DS,AX
	mov AH,41h
	mov DX,offset fname
	int 21h              
	jc error 	     ;переход если ошибка
	mov AH,09h           ;вывод сообщения
	mov DX,offset msgok  ;об удалении
	int 21h              ;вызов ДОС
fin:	mov AX,4C00h         ;завершение программы
	int 21h              ;вызов ДОС
error:	mov AH,09h           ;вывод сообщения
	mov DX,offset msgerr ;об ошибке
	int 21h              ;вызов ДОС
	jmp fin              ;переход на завершение
text ends

data segment
	fname db 'f:\testfile.001',0
	msgok db 'File delete$'
	msgerr db 'File is not found$'
data ends

stk segment stack
	db 256 dup(0)
stk ends
	end begin
	
	