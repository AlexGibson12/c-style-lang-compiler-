

section .text
	global print_number
	printnewline:
                push rdi
                push rax
                push rdx
                push rsi
                mov rdi,1
                mov rax,1
                mov rdx,10
                sub rsp,1
                mov [rsp],dl
                mov rsi,rsp
                mov rdx,1
                syscall
                add rsp,1
                           
                pop rsi
                pop rdx  
                pop rax   
                pop rdi
                ret

	print_number:
		push rax
		push r10
		push r11
		push r12
		push rdx
		mov r10,10
		mov r11,1
		mov r12,rsp
		main_loop:
			xor rdx,rdx
			div r10
			add rdx,48
			sub rsp,1
			mov [rsp],dl
			add r11,1
			cmp rax,0
			jne main_loop
		mov rax,1          
		mov rdi,1   
		sub r11,1
		mov rsi,rsp 
		mov rdx,r11
		syscall     
		call printnewline
		pop_stack:  
			add rsp,1
			cmp rsp,r12
			jne pop_stack
		pop rdx
		pop r12
		pop r11
		pop r10
		pop rax
		ret

