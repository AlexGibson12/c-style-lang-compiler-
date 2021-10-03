global _start
extern print_number
section .text:
     _start:
push rbp
mov rbp,rsp
push 0
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
push 1
pop rdx
pop rax
add rax,rdx
push rax
pop rax
mov [rbp-8], rax
push qword [rbp-8]
push 50
pop rdx
pop rax
cmp rax,rdx
jl .valid5
jmp .invalid6
.valid5:
mov rax,1
jmp .either7
.invalid6:
mov rax,0
.either7:
push rax
pop rax
cmp rax,0
jne .ifstat5
jmp .elsestat9
.ifstat5:
push qword [rbp-8]
pop rax
call print_number
jmp .done10
.elsestat9:
push qword [rbp-8]
push qword [rbp-8]
pop rdx
pop rax
add rax,rdx
push rax
pop rax
call print_number
.done10:
jmp .while1
.pastwhile5:
mov rax,60
syscall

