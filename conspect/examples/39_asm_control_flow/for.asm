global asm_for_count
section .text

; int asm_for_count(int n)
; int c = 0; for (int i = 0; i < n; ++i) { c++; } return c;
asm_for_count:
  xor eax, eax        ; c = 0
  xor ecx, ecx        ; i = 0
.loop:
  cmp ecx, edi
  jge .done
  inc eax             ; c++
  inc ecx             ; i++
  jmp .loop
.done:
  ret

