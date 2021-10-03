global _start
extern print_number
section .text:
     _start:
push rbp
mov rbp,rsp
push 1
.while1:
push qword [rbp-8]
push 100
pop rdx
pop rax
cmp rax,rdx
jl .valid1
jmp .invalid2
.valid1:
mov rax,1
jmp .either3
.invalid2:
mov rax,0
.either3:
push rax
pop rax
cmp rax,0
je .pastwhile5
push qword [rbp-8]
pop rax
call print_number
push qword [rbp-8]
push 1
pop rdx
pop rax
add rax,rdx
push rax
pop rax
mov [rbp-8], rax
jmp .while1
.pastwhile5:
mov rax,60
syscall

