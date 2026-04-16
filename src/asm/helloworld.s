.intel_syntax noprefix

.section .data
  msg:
    .ascii "Hello, Wolrd!\n"
  msg_len = . - msg # Subtract the start of msg from where we are now.

.section .text
  .global _start

_start:
  mov rax, 1
  mov rdi, 1
  lea rsi, [rip + msg] # Find msg relative to the next instruction address in memory.
  mov rdx, msg_len
  syscall
  mov rax, 60
  mov rdi, 0
  syscall

# NOTE: mov rsi, offset msg doesn't always work due to ASRL.
