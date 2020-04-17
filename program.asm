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

empty:
	push rbp
	mov rbp, rsp
	sub rsp, 16
	mov rsp, rbp
	pop rbp
	ret

main:
	push rbp
	mov rbp, rsp
	sub rsp, 80
	mov ax, 2
	sub ax, 2
	mov word [rbp - 8], ax
	mov ax, word [rbp - 8]
	imul ax, 2
	mov word [rbp - 10], ax
	mov rax, rbp
	sub rax, 6
	xor rbx, rbx
	mov bx, word [rbp - 10]
	add rax, rbx
	mov qword [rbp - 18], rax
	mov word [rbp - 20], 2
	mov rbx, qword [rbp - 18]
	mov ax, word [rbp - 20]
	mov word [rbx], ax
	mov ax, 3
	sub ax, 2
	mov word [rbp - 22], ax
	mov ax, word [rbp - 22]
	imul ax, 2
	mov word [rbp - 24], ax
	mov rax, rbp
	sub rax, 6
	xor rbx, rbx
	mov bx, word [rbp - 24]
	add rax, rbx
	mov qword [rbp - 32], rax
	mov word [rbp - 34], 3
	mov rbx, qword [rbp - 32]
	mov ax, word [rbp - 34]
	mov word [rbx], ax
	mov ax, 4
	sub ax, 2
	mov word [rbp - 36], ax
	mov ax, word [rbp - 36]
	imul ax, 2
	mov word [rbp - 38], ax
	mov rax, rbp
	sub rax, 6
	xor rbx, rbx
	mov bx, word [rbp - 38]
	add rax, rbx
	mov qword [rbp - 46], rax
	mov word [rbp - 48], 4
	mov rbx, qword [rbp - 46]
	mov ax, word [rbp - 48]
	mov word [rbx], ax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	sub rsp, 16
	mov rax, '2Vå≥‚U'
	mov qword [rsp], rax
	add rsp, 1
	mov byte [rsp], 0
	sub rsp, 1
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 16
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
	mov word [rbp - 50], 2
__L0__:
	mov ax, word [rbp - 50]
	cmp ax, 4
	jg __LL3__
	mov byte [rbp - 51], 1
	jmp __LL4__
__LL3__:
	mov byte [rbp - 51], 0
__LL4__:
	mov al, byte [rbp - 51]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp - 51]
	cmp al, 0
	jz __L2__
__L1__:
	mov ax, word [rbp - 50]
	sub ax, 2
	mov word [rbp - 53], ax
	mov ax, word [rbp - 53]
	imul ax, 2
	mov word [rbp - 55], ax
	mov rax, rbp
	sub rax, 6
	xor rbx, rbx
	mov bx, word [rbp - 55]
	add rax, rbx
	mov qword [rbp - 63], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 63]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 50]
	add ax, 1
	mov word [rbp - 65], ax
	mov ax, word [rbp - 65]
	mov word [rbp - 50], ax
	jmp __L0__
__L2__:
	mov rax, rsp
	sub rax, 22
	mov rbx, qword [rbp - 6]
	mov qword [rax], rbx
	call empty


; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
