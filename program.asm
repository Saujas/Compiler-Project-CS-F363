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
	mem_main resb 53

section .text
global main

main:
	mov rbp, mem_main
	push rbp
	mov rbp, [rsp]
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	sub rsp, 24
	mov rax, 'Enter el'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'ements o'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'f arrayo'
	mov qword [rsp], rax
	add rsp, 7
	mov byte [rsp], 0
	sub rsp, 23
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 24
	mov word [rbp + 19], 1
__L0__:
	cmp word [rbp + 19], 4
	jg __LL6__
	mov byte [rbp + 21], 1
	jmp __LL7__
__LL6__:
	mov byte [rbp + 21], 0
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
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	sub rsp, 35
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
	add rsp, 35
	mov word [rbp + 36], 1
__L3__:
	cmp word [rbp + 36], 4
	jg __LL8__
	mov byte [rbp + 38], 1
	jmp __LL9__
__LL8__:
	mov byte [rbp + 38], 0
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
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
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
