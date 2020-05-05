extern printf, scanf

section .data
	fmt_integer: db '%d', 10, 0
	fmt_integer_no_line_break: db '%d ', 0
	fmt_float: db '%f', 10, 0
	fmt_float_no_line_break: db '%f ', 0
	fmt_string: db '%s', 10, 0
	fmt_string_no_line_break: db '%s', 0
	fmt_ip_integer: db '%d', 0
	fmt_ip_float: db '%lf', 0
	message_true: db 'true ', 0
	message_false: db 'false ', 0
	message_lb: db 10, 0
	message_ip_integer: db 'Input: Enter an integer value: ', 0
	message_ip_real: db 'Input: Enter a real value: ', 0
	message_ip_boolean: db 'Input: Enter a boolean value: ', 0
	message_output: db 'Output: ', 0
	buffer_integer: dd 0

section .bss

section .text
global main

main:
	push rbp
	mov rbp, rsp
	sub rsp, 16
	mov rsi, message_ip_integer
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 2], ax
	mov rsi, message_ip_integer
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 4], ax
	mov ax, word [rbp - 2]
	add ax, word [rbp - 4]
	mov word [rbp - 8], ax
	mov ax, word [rbp - 8]
	mov word [rbp - 6], ax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 6]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf

;exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
