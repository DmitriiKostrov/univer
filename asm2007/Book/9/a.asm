;Пример дальнего вызова
text1 segment
	assume cs:text1, ds:data
main proc
	mov AX, data
	mov DS, AX
	mov CX,10
cycle: 	mov AX,200
        call far ptr delay