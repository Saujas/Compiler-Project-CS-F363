extern printf, scanf

section .data
	fmt_integer: db '%d', 10, 0
	fmt_float: db '%f', 10, 0
	fmt_string: db '%s', 10, 0
	fmt_ip_integer: db '%d', 0
	fmt_ip_float: db '%lf', 0
	message_true: db 'true', 0
	message_false: db 'false', 0
	message_ip_integer: db 'Enter an integer value: ', 0
	message_ip_real: db 'Enter a real value: ', 0
	message_ip_boolean: db 'Enter a boolean value: ', 0
	buffer_integer: dd 0

section .bss
	mem_main resb 53

section .text
global main

main:
	mov rbp, mem_main
	push rbp
	mov rbp, [rsp]
	mov word [rbp + 19], 1
__L0__:
	cmp word [rbp + 19], 4
	jg __LL6__
	MOV byte [rbp + 21], 1
	JMP __LL7__
__LL6__:
	MOV byte [rbp + 21], 0
__LL7__:
	mov al, byte [rbp + 21]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp + 21]
	cmp al, 0
	jz __L2__
__L1__:
	mov ax, word [rbp + 19]
	sub ax, 1
	mov word [rbp + 22], ax
	mov ax, word [rbp + 22]
	imul ax, 2
	mov word [rbp + 24], ax
	mov rax, rbp
	add rax, 9
	xor rbx, rbx
	mov bx, word [rbp + 24]
	add rax, rbx
	mov qword [rbp + 26], rax
	mov rbx, qword [rbp + 26]
	mov rsi, message_ip_integer
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbx], ax
	mov ax, word [rbp + 19]
	add ax, 1
	mov word [rbp + 34], ax
	mov ax, word [rbp + 34]
	mov word [rbp + 19], ax
	jmp __L0__
__L2__:
	mov word [rbp + 36], 1
__L3__:
	cmp word [rbp + 36], 4
	jg __LL8__
	MOV byte [rbp + 38], 1
	JMP __LL9__
__LL8__:
	MOV byte [rbp + 38], 0
__LL9__:
	mov al, byte [rbp + 38]
	cmp al, 1
	jz __L4__
	mov al, byte [rbp + 38]
	cmp al, 0
	jz __L5__
__L4__:
	mov ax, word [rbp + 36]
	sub ax, 1
	mov word [rbp + 39], ax
	mov ax, word [rbp + 39]
	imul ax, 2
	mov word [rbp + 41], ax
	mov rax, rbp
	add rax, 9
	xor rbx, rbx
	mov bx, word [rbp + 41]
	add rax, rbx
	mov qword [rbp + 43], rax
	mov rbx, qword [rbp + 43]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp + 36]
	add ax, 1
	mov word [rbp + 51], ax
	mov ax, word [rbp + 51]
	mov word [rbp + 36], ax
	jmp __L3__
__L5__:


; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
