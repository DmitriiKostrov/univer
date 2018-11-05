
text segment public
PUBLIC test_three 
	assume CS:text, DS:data
;-----------------
test_three proc NEAR
	pop DL
	mov AL,DL
	mov CX,7
	mov BX,1
cont:	cmp AL,Mass[BX]
	je next
	mov AL,Mass[BX]
	inc BX
	loop cont
	jmp text_no
next:	inc BX
	dec CX
	cmp AL,Mass[BX]
	je text_yes
	mov AL,Mass[BX]
	inc BX
	loop cont
	jmp text_no
	ret

text_yes:mov DX,offset textOk 
         mov BX,1; указатель того, что есть три послед-х числа.
	 jmp write

text_no:mov DX,offset textNo
	jmp write		

write: 	mov AH,09h
	int 21h
	mov CX,1
	cmp CX,BX
	je write_num
	jmp ok
write_num:
	mov DX,offset AX
	mov AH,40h
	mov BX,1
	mov CX,1
	int 21h 
ok: 	ret
test_three endp
;-----------------
text ends
end