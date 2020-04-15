extern printf

section .data
	fmt_integer: db '%d', 10, 0
	fmt_float: db '%f', 10, 0
	fmt_string: db '%s', 10, 0
	message_true: db 'true', 0
	message_false: db 'false', 0

section .bss
	mem_main resb 63

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
	finit
	fld qword [rbp + 19]
	sub rsp, 64
	mov rax, __float64__(-1.0)
	mov [rsp], rax
	fmul qword [rsp]
	add rsp, 64
	fstp qword [rbp + 27]
	mov rax, qword [rbp + 27]
	mov qword [rbp + 3], rax
	mov rax, qword[rbp + 3]
	mov rdi, fmt_float
	movq xmm0, rax
	mov eax, 1
	call printf
	mov ax, 2
	imul ax, -1
	mov word [rbp + 35], ax
	mov ax, word [rbp + 35]
	mov word [rbp + 0], ax
	mov rax, 0
	mov ax, [rbp + 0]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	finit
	sub rsp, 128
	mov rax, __float64__(5.2)
	mov [rsp], rax
	fld qword [rsp]
	add rsp, 64
	mov rax, __float64__(-1.0)
	mov [rsp], rax
	fmul qword [rsp]
	fstp qword [rbp + 37]
	mov rax, qword [rbp + 37]
	mov qword [rbp + 3], rax
	mov rax, qword[rbp + 3]
	mov rdi, fmt_float
	movq xmm0, rax
	mov eax, 1
	call printf
	finit
	sub rsp, 64
	mov rax, __float64__(2.2)
	mov [rsp], rax
	fld qword [rsp]
	add rsp, 64
	fld qword [rbp + 3]
	fcomi
	jge __L0__
	MOV byte [rbp + 45], 1
	JMP __L1__
__L0__:
	MOV byte [rbp + 45], 0
__L1__:		mov al, byte [rbp + 45]
	mov byte [rbp + 2], al
	finit
	fld qword [rbp + 3]
	sub rsp, 64
	mov rax, __float64__(5.1)
	mov [rsp], rax
	fadd qword [rsp]
	add rsp, 64
	fstp qword [rbp + 46]
	mov rax, qword [rbp + 46]
	mov qword [rbp + 11], rax
	mov rax, qword[rbp + 11]
	mov rdi, fmt_float
	movq xmm0, rax
	mov eax, 1
	call printf
	finit
	fld qword [rbp + 3]
	sub rsp, 64
	mov rax, __float64__(5.1)
	mov [rsp], rax
	fadd qword [rsp]
	add rsp, 64
	fstp qword [rbp + 54]
	finit
	sub rsp, 64
	mov rax, __float64__(2.2)
	mov [rsp], rax
	fld qword [rsp]
	add rsp, 64
	fld qword [rbp + 54]
	fcomi
	jle __L2__
	MOV byte [rbp + 62], 1
	JMP __L3__
__L2__:
	MOV byte [rbp + 62], 0
__L3__:		mov al, byte [rbp + 62]
	mov byte [rbp + 2], al
	cmp byte [rbp + 2], 1
	jz __L4__
	mov rax, message_false
	jmp __L5__
__L4__:
	mov rax, message_true
__L5__:
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf


; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
