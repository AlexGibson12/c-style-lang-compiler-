global _start
extern print_number
section .text:
     _start:
push rbp
mov rbp,rsp
push 1
push 2
push qword [rbp-16]
push qword [rbp-8]
pop rdx
pop rax
cmp rax,rdx
jl .valid0
jmp .invalid1
.valid0:
mov rax,1
jmp .either2
.invalid1:
mov rax,0
.either2:
push rax
push qword [rbp-24]
pop rax
call print_number
pop rax
pop rax
pop rax
mov rax,60
syscall

