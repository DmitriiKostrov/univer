; �८�ࠧ������ ����筮�� �᫠ � 16-���� ᨬ������ ���


text segment
 	assume CS:text, DS:data
begin: 	mov AX,16385
	mov SI,offset string
	call wrd_asc
	mov AH,09h
	mov DX, offset string
	int 21h

wrd_asc proc
	push AX ;��࠭塞 ��室��� �᫮ � �⥪�
	and AX,0F000h ; �뤥��� �⢥�� ��⮢
	mov CL,12;ᤢ���� �� �� 12 ���
	shr AX,CL
	call bin_asc

	mov byte ptr [SI],AL ; ��ࠢ�� � ��ப� १����
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