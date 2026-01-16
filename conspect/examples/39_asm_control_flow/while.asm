global asm_while_sum
section .text

; int asm_while_sum(int n)
; int s = 0; while (n > 0) { s += n; n--; } return s;
asm_while_sum:
  xor eax, eax        ; s = 0
  mov ecx, edi        ; ecx = n
.loop:
  cmp ecx, 0
  jle .done
  add eax, ecx        ; s += n
  dec ecx             ; n--
  jmp .loop
.done:
  ret

