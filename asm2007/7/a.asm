cseg segment
assume cs:cseg, ds:cseg, ss:cseg
	org 100h
beg:	jmp short bb
	a dw 231
	b dw 240
	c dw ?
	t db '      ',13,10,'$'

bb:	mov bx,b 
	mov ax,a

nod:	cmp ax,bx 	   ; ax= bx ?
	je nod2 	   ; ax= bx --> exit
	ja nod1		   ; ax>bx -->nod1
	xchg ax,bx         ; ���� ���⠬� ��������
	
nod1:	sub ax,bx          ;���⠥� ��� :-)
	jmp nod		   ;

nod2:   mov c,ax
	mov bx,10               ;���� �� ����⭮ �� �� ⠪��
	mov cx,6 		;��⠭����� �᫮ ���権 ���
	mov di,offset t
	
c1:	mov byte ptr [di],' '   ;��������� ������⭮ ��祬 ��ﬨ ���
	inc di                  ;di 㢥��稢��� 6 ࠧ
	loop c1
	
c2:	dec di                  ;⥯��� ������ ���६���
	mov dx,0                ;(0)->dx
	div bx                  ;��宦� �ந������ ������� �� 10
	add dl,'0'
	mov byte ptr [di],dl
	cmp ax,0
	jne c2
	mov dx,offset t
	mov ah,9h
	int 21h

	mov ax,4C00h
	int 21h
cseg ends
end beg     	