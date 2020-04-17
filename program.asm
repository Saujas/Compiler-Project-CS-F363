extern printf, scanf

section .data
	fmt_integer: db '%d', 10, 0
	fmt_float: db '%f', 10, 0
	fmt_string: db '%s', 10, 0
	fmt_string_no_line_break: db '%s', 0
	fmt_ip_integer: db '%d', 0
	fmt_ip_float: db '%lf', 0
	message_true: db 'true', 0
	message_false: db 'false', 0
	message_ip_integer: db 'Input: Enter an integer value: ', 0
	message_ip_real: db 'Input: Enter a real value: ', 0
	message_ip_boolean: db 'Input: Enter a boolean value: ', 0
	message_output: db 'Output: ', 0
	buffer_integer: dd 0

section .bss

section .text
global main

square:
	push rbp
	mov rbp, rsp
	sub rsp, 48
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	sub rsp, 48
	mov rax, 'Printing'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, ' array e'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'lements '
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'one-by-o'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'nee-by-o'
	mov qword [rsp], rax
	add rsp, 2
	mov byte [rsp], 0
	sub rsp, 34
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 48
	mov word [rbp - 10], 2
__L0__:
	mov ax, word [rbp - 10]
	cmp ax, 4
	jg __LL6__
	mov byte [rbp - 11], 1
	jmp __LL7__
__LL6__:
	mov byte [rbp - 11], 0
__LL7__:
	mov al, byte [rbp - 11]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp - 11]
	cmp al, 0
	jz __L2__
__L1__:
	mov ax, word [rbp - 10]
	sub ax, 2
	mov word [rbp - 13], ax
	mov ax, word [rbp - 13]
	imul ax, 2
	mov word [rbp - 15], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 15]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 23], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 23]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 10]
	add ax, 1
	mov word [rbp - 25], ax
	mov ax, word [rbp - 25]
	mov word [rbp - 10], ax
	jmp __L0__
__L2__:
	mov ax, 2
	sub ax, 2
	mov word [rbp - 27], ax
	mov ax, word [rbp - 27]
	imul ax, 2
	mov word [rbp - 29], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 29]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 37], rax
	mov word [rbp - 39], 100
	mov rbx, qword [rbp - 37]
	mov ax, word [rbp - 39]
	mov word [rbx], ax
	mov rsp, rbp
	pop rbp
	ret

main:
	push rbp
	mov rbp, rsp
	sub rsp, 80
	mov ax, 2
	sub ax, 2
	mov word [rbp - 10], ax
	mov ax, word [rbp - 10]
	imul ax, 2
	mov word [rbp - 12], ax
	mov rax, rbp
	sub rax, 8
	xor rbx, rbx
	mov bx, word [rbp - 12]
	add rax, rbx
	mov qword [rbp - 20], rax
	mov word [rbp - 22], 2
	mov rbx, qword [rbp - 20]
	mov ax, word [rbp - 22]
	mov word [rbx], ax
	mov ax, 3
	sub ax, 2
	mov word [rbp - 24], ax
	mov ax, word [rbp - 24]
	imul ax, 2
	mov word [rbp - 26], ax
	mov rax, rbp
	sub rax, 8
	xor rbx, rbx
	mov bx, word [rbp - 26]
	add rax, rbx
	mov qword [rbp - 34], rax
	mov word [rbp - 36], 4
	mov rbx, qword [rbp - 34]
	mov ax, word [rbp - 36]
	mov word [rbx], ax
	mov ax, 4
	sub ax, 2
	mov word [rbp - 38], ax
	mov ax, word [rbp - 38]
	imul ax, 2
	mov word [rbp - 40], ax
	mov rax, rbp
	sub rax, 8
	xor rbx, rbx
	mov bx, word [rbp - 40]
	add rax, rbx
	mov qword [rbp - 48], rax
	mov word [rbp - 50], 6
	mov rbx, qword [rbp - 48]
	mov ax, word [rbp - 50]
	mov word [rbx], ax
	mov rax, rsp
	sub rax, 24
	mov rbx, rbp
	sub rbx, 8
	mov qword [rax], rbx
	call square
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	sub rsp, 48
	mov rax, 'Printing'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, ' array e'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'lements '
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'one-by-o'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'nee-by-o'
	mov qword [rsp], rax
	add rsp, 2
	mov byte [rsp], 0
	sub rsp, 34
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 48
	mov word [rbp - 52], 2
__L3__:
	mov ax, word [rbp - 52]
	cmp ax, 4
	jg __LL8__
	mov byte [rbp - 53], 1
	jmp __LL9__
__LL8__:
	mov byte [rbp - 53], 0
__LL9__:
	mov al, byte [rbp - 53]
	cmp al, 1
	jz __L4__
	mov al, byte [rbp - 53]
	cmp al, 0
	jz __L5__
__L4__:
	mov ax, word [rbp - 52]
	sub ax, 2
	mov word [rbp - 55], ax
	mov ax, word [rbp - 55]
	imul ax, 2
	mov word [rbp - 57], ax
	mov rax, rbp
	sub rax, 8
	xor rbx, rbx
	mov bx, word [rbp - 57]
	add rax, rbx
	mov qword [rbp - 65], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 65]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 52]
	add ax, 1
	mov word [rbp - 67], ax
	mov ax, word [rbp - 67]
	mov word [rbp - 52], ax
	jmp __L3__
__L5__:


; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
