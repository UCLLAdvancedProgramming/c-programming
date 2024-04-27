// Adapted from: https://en.cppreference.com/w/c/language/asm

#include <stdio.h>
 
extern int func(void);
// the definition of func is written in assembly language
__asm__(".globl func\n\t"
        ".type func, @function\n\t"
        "func:\n\t"
        ".cfi_startproc\n\t"
        "movl $7, %eax\n\t"
        "ret\n\t"
        ".cfi_endproc");
 
int main(void)
{
    int n = func();
    // gcc's extended inline assembly
    __asm__ ("imull $5, %0"
           : "=r" (n)
           : "0" (n));
    printf("7*5 = %d\n", n);
    fflush(stdout);
 
    // standard inline assembly in C++
    __asm__ ("movq $60, %rax\n\t" // the exit syscall number on Linux
             "movq $2,  %rdi\n\t" // this program returns 2
             "syscall");
}
