;�࣠������� ��������樮���� 横� �� 10 蠣��, ����� ����
;�믮������ � ����প�� ��浪� ��᪮�쪨� ᥪ㭤
text segment
	assume CS:text,DS:data
begin:	mov CX,10 ;�᫮ 蠣�� 横��
circle: push CX   ; ��࠭���� ���稪� � �⥪�
;�뢥��� �� �࠭ ����஫��� ��ப� �� ���� ᨬ�����
	mov AH,09h
	mov DX, offset string
	int 21h
;�࣠���㥬 �ணࠬ���� ����প�
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