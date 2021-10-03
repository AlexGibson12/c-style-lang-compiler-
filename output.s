global _start
extern print_number
section .text:
     _start:
push rbp
mov rbp,rsp
push 0
.while1:
push qword [rbp-8]
push 1000
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
push 2
pop rdx
pop rax
push rcx
mov rcx,rdx
xor rdx,rdx
div rcx
pop rcx
mov rax,rdx
push rax
push 0
pop rdx
pop rax
cmp rax,rdx
je .valid6
jmp .invalid7
.valid6:
mov rax,1
jmp .either8
.invalid7:
mov rax,0
.either8:
push rax
pop rax
cmp rax,0
jne .ifstat6
jmp .done9
.ifstat6:
push qword [rbp-8]
pop rax
call print_number
.done9:
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
pop rax
mov rax,60
syscall

