#include <stdio.h>

int main(int argc, char **argv) {
  char *msg = "Hello, World!\n";
  long msg_len = 14;

  asm volatile (
    ".intel_syntax noprefix;"
    "mov rax, 1;"
    "mov rdi, 1;"
    "mov rsi, %0;"
    "mov rdx, %1;"
    "syscall;"
    ".att_syntax prefix;"
    :
    : "r"(msg), "r"(msg_len)
    : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory"
  );

  return 0;
}
