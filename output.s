global _start
extern print_number
section .text:
     _start:
push rbp
mov rbp,rsp
push 12
push 5
push 2
push qword [rbp-8]
pop rdx
pop rax
mul rdx
push rax
pop rdx
pop rax
add rax,rdx
push rax
pop rax
call print_number
mov rax,60
syscall

