global _start
extern print_number
section .text:
     _start:
push rbp
mov rbp,rsp
push 10
push qword [rbp-8]
push qword [rbp-8]
pop rax
pop rdx
add rax,rdx
push rax
push qword [rbp-8]
push qword [rbp-16]
pop rax
pop rdx
add rax,rdx
push rax
pop rax
call print_number
mov rax,60
syscall

