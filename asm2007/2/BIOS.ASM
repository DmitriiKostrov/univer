model tiny
.code
org 100h
start:
jmp begin; jump to start execution
s1 db ' $'
s2 db 13,10,'$'
begin:
xor cx,cx  ;mov cx, 0 no correct more OZY
f1:
  mov s1,cl; send lower cx to s1
  mov AH,0Eh
  mov AL,cl
  mov BL, 07h
  mov BH, 0
  push cx
  int 10h
  pop cx
  inc cx
  test cl,1111b; no cratno 16
  jnz cont1
    mov AH,9
    mov dx,offset s2
    push cx
    int 21h
    pop cx
cont1:
  ;chech boolean
  ;cmp cl,0
  test cl,cl; logical and ne portiachee operator
;1 if =
;0 !=
  jnz f1; jump if no 0
ret
end start
