;�ணࠬ�� ���᪨���� �������訩 ����� ���ᨢ� � ��� �����
;model tiny
;.code

text segment
       	assume CS:text, DS:text
	org 100h
start:
	;mov AX,data
	;mov DS,AX
	
      	mov DX,Mass
	mov CX,8;���稪
	mov BX,2;����� ����� ���ᨢ�
        mov AX,1; ����� ᨬ����
cont:   cmp DX,Mass[BX] ; �᫨ ���� ���࠭� �����, 祬 ��ன
	jl next        ;��, 
	mov DX,Mass[BX] ;���,� DX ����ᨬ ᫥���騩 ����
	mov AX,BX
next:	inc BX
	inc BX
	loop cont
	
	shr AX,1 ;����� �� 2
	inc Ax
	push DX
write:	;mov AX,DX
	mov BX,10
	mov SI,0 ;����稪 ��� ��ப�
loop1:	div bl
	add AH,'0'
	mov dl,ah
	mov answ[SI],DL
	inc SI
	mov ah,2h
	mov cl,al  ;��࠭塞 al �.�. int 21h ������ ���
	int 21h    ;������ AL
	mov al,cl
	mov ah,0
	cmp ax,0
	jg loop1

	pop DX
	mov AX,DX
	mov BX,10
	mov SI,0 ;����稪 ��� ��ப�
loop2:	div bl
	add AH,'0'
	mov dl,ah
	mov answ[SI],DL
	inc SI
	mov ah,2h
	mov cl,al  ;��࠭塞 al �.�. int 21h ������ ���
	int 21h    ;������ AL
	mov al,cl
	mov ah,0
	cmp ax,0
	jg loop2
    mov AX,4C00h
	int 21h
	Mass dw 123,4,12,23,25,1,17,123,123;
	answ db 3 dup('*'),'$'

;data segment
;	Mass dw 123,4,12,23,25,1,17,123,123;
;	answ db 3 dup('*'),'$'
;	;x db ?
;data ends

;stack segment stack
;	db 256 dup(0)
;stack ends
text ends 
        end start
	
	