extern printf

section .data
	fmt_integer: db '%d', 10, 0
	fmt_float: db '%f', 10, 0
	fmt_string: db '%s', 10, 0

section .bss
	mem_main resb 27
section .text
global main

main:
	mov rbp, mem_main
	push rbp
	mov rbp, rsp
	finit
	sub rsp, 128
	mov rax, __float64__(2.3)
	mov [rsp], rax
	fld qword [rsp]
	 add rsp, 64
	mov rax, __float64__(1.2)
	mov [rsp], rax
	fadd qword [rsp]
	fstp qword [rbp + 19]
	mov rax, qword [rbp + 19]
	mov qword [rbp + 3], rax
	mov rax, qword[rbp + 3]
	mov rdi, fmt_float
	movq xmm0, rax
	mov eax, 1
	call printf


; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
