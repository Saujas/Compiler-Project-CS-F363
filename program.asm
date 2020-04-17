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
	sub rsp, 16
	mov word [rbp - 14], 6
	mov ax, word [rbp - 14]
	mov word [rbp - 4], ax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 4]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov rbx, rbp
	sub rbx, 4
	mov ax, word [rbx]
	sub rbx, 8
	mov rbx, qword [rbx]
	mov word [rbx], ax
	mov rsp, rbp
	pop rbp
	ret

main:
	push rbp
	mov rbp, rsp
	sub rsp, 16
	mov word [rbp - 16], 2
	mov ax, word [rbp - 16]
	mov word [rbp - 4], ax
	mov rax, rsp
	sub rax, 18
	mov bx, word [rbp - 4]
	mov word [rax], bx
	mov rax, rsp
	sub rax, 28
	mov rbx, rbp
	sub rbx, 14
	mov qword [rax], rbx
	call square
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 14]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf


; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h