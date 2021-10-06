section .text
extern print_number
global _start
     _start:
push rbp
mov rbp,rsp
push 2
pop rax
call print_number
mov rax,60
syscall

