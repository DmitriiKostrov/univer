; �ணࠬ�� 㤠����� 䠩��.
; �ᯮ������� �㭪樨 ��� � ������������ 䫠� ��७��.
;����� 7.1 �� �����
text	 segment
assume 	CS:text, DS:data
begin:  mov AX,data
	mov DS,AX
	mov AH,41h
	mov DX,offset fname
	int 21h              
	jc error 	     ;���室 �᫨ �訡��
	mov AH,09h           ;�뢮� ᮮ�饭��
	mov DX,offset msgok  ;�� 㤠�����
	int 21h              ;�맮� ���
fin:	mov AX,4C00h         ;�����襭�� �ணࠬ��
	int 21h              ;�맮� ���
error:	mov AH,09h           ;�뢮� ᮮ�饭��
	mov DX,offset msgerr ;�� �訡��
	int 21h              ;�맮� ���
	jmp fin              ;���室 �� �����襭��
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
	
	