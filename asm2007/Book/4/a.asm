;Программа удаления файла с анализом возможных
;системных сбоев
text segment
assume cs:text,ds:data
begin:
	mov AX,data
	mov DS,AX
	mov AH,41h
	mov DX,offset fname
	int 21h
	jc error
	mov AH,09h
	mov DX,offset msgok
	int 21h
fin:	mov AX,4C00h
	int 21h
error:	cmp AX,02h
	je notfound
	cmp AX,03h
	je wrongdir
	cmp AX,04h
	je noaccess
	jmp fin

notfound:mov DX,offset msg1
	jmp write
wrongdir:mov DX,offset msg2
	jmp write
noaccess:mov DX,offset msg3

write:	mov AH,09h
	int 21h
	jmp fin

text ends
data segment
	fname db 'f:\namme.001',0
	msgok db 'File del$'
	msg1  db 'File is not found$'
	msg2  db 'dir error$'
	msg3  db 'Access bad$'
data ends

stk segment stack
	db 256 dup(0)
stk  ends
	end begin