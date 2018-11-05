text segment public
EXTRN PutChar:NEAR
     assume CS:text;, DS: data
start:
        call PutChar
	mov AX,4C00h
	int 21h
;stk segment stack
;	db 256 dup(0)
;stk ends

;data segment 
;	Mass dw 123,3,1,4
;data ends
                      	
text ends
end start