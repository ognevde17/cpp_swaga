global asm_if_abs
section .text

; int asm_if_abs(int x)
; if (x < 0) return -x; else return x;
asm_if_abs:
  mov eax, edi        ; eax = x
  cmp edi, 0
  jge .ret            ; if (x >= 0) goto ret
  neg eax             ; eax = -eax
.ret:
  ret

