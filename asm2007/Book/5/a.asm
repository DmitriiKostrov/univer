;横��
text segment
assume CS:text, DS: data
begin:
	mov AX,data
	mov DS,AX
;����� ��� �࣠����樨 横��
	mov CX,223   ;�᫮ 蠣�� � 横��
	mov SI,0     ;������ ����� � ������塞�� ���ᨢ�
	mov AL,32    ;��� ��ࢮ�� ᨬ���� �஡���
;横� � 4�� ���������
fill:	mov symbols[SI],Al
	inc AL
	inc SI
	loop fill
;�뢮� ���ᨢ� �� �࠭
	mov AH,40h
	mov BX,1
	mov CX,223
	mov DX,offset symbols
	int 21h
	
;end of prog
	mov AX,4C00h
	int 21h
text ends

data segment
	symbols db 223 dup('*')
data ends

stk segment stack
	db 256 dup(0)
stk ends
	end begin
