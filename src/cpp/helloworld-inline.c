#include <stdio.h>

int main(int argc, char **argv) {
  char *msg = "Hello, World!\n";
  long msg_len = 14;

  asm volatile(".intel_syntax noprefix;"
               /* 1. Print the contents of msg ("Hello, World!"). */
               "mov rax, 1;"
               "mov rdi, 1;"
               "mov rsi, %0;"
               "mov rdx, %1;"
               "syscall;"
               /* 2. Print using a symbol from inline. */
               "mov rax, 1;"
               "mov rdi, 1;"
               "lea rsi, [rip + .Linline];"
               "lea rdx, [.Lend - .Linline];"
               "syscall;"
               /* 3. Workaround to write data section. */
               "jmp .Lend;"
               ".Linline:"
               ".ascii \"INLINE\\n\";"
               ".Lend:"
               ".att_syntax prefix;"
               :
               : "r"(msg), "r"(msg_len)
               : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory");

  return 0;
}
