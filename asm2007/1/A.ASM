DOSSEG
.STACK 100h
.DATA
Message db 'Privet $'
.CODE
mov ax,@Data
mov dx,ax
mov ah,9
mov dx,OFFSET Message

int 21h
END