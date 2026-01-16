global is_prime
section .text
is_prime:
  mov eax, edi
  cmp eax, 2
  jl .not_prime
  je .is_prime
  test eax, 1
  jz .not_prime
  mov ecx, 3
  mov ebx, eax
.check_loop:
  mov eax, ecx
  imul eax, ecx
  cmp eax, ebx
  jg .is_prime
  mov eax, ebx
  xor edx, edx
  div ecx
  test edx, edx
  jz .not_prime
  add ecx, 2
  jmp .check_loop
.is_prime:
  mov eax, 1
  ret
.not_prime:
  xor eax, eax
  ret

