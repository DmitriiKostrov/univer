; преобразование двоичного числа в 16-ричную символьную форму


text segment
 	assume CS:text, DS:data
begin: 	mov AX,16385
	mov SI,offset string
	call wrd_asc
	mov AH,09h
	mov DX, offset string
	int 21h

wrd_asc proc
	push AX ;сохраняем исходное число в стеке
	and AX,0F000h ; выделим четверку битов
	mov CL,12;сдвинем её на 12 бит
	shr AX,CL
	call bin_asc

	mov byte ptr [SI],AL ; отправим в строку результата
	pop AX
	push AX
	and AX,0F00h
	mov CL,8              
	shr AX,CL
	inc SI
	call bin_asc

	mov byte ptr [SI],AL
	pop AX
	push AX
	and AX,0F0h
	mov CL,4
	shr AX,CL
	inc SI
	call bin_asc
	
	mov byte ptr [SI],AL
	pop AX
	push AX
	and AX,0Fh
	inc SI
	call bin_asc

	mov byte ptr [SI],AL
	pop AX
	ret
wrd_asc endp

bin_asc proc
	cmp AL,9
	ja lettr
	add AL,30h
	jmp ok
lettr: 	add AL,37h
ok:	ret
bin_asc endp
	text ends

data segment
     	string db 4 dup('?'),'h$'
data ends

stack segment stack
	db 256 dup(0)
stack ends

end begin