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
	sub rsp, 64
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
	mov ax, word [rbp - 10]
	mov word [rbp - 14], ax
__L0__:
	mov ax, word [rbp - 14]
	cmp ax, word [rbp - 12]
	jg __LL9__
	mov byte [rbp - 15], 1
	jmp __LL10__
__LL9__:
	mov byte [rbp - 15], 0
__LL10__:
	mov al, byte [rbp - 15]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp - 15]
	cmp al, 0
	jz __L2__
__L1__:
	mov ax, word [rbp - 14]
	sub ax, word [rbp - 10]
	mov word [rbp - 17], ax
	mov ax, word [rbp - 17]
	imul ax, 2
	mov word [rbp - 19], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 19]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 27], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 27]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 14]
	add ax, 1
	mov word [rbp - 29], ax
	mov ax, word [rbp - 29]
	mov word [rbp - 14], ax
	jmp __L0__
__L2__:
	mov ax, 2
	sub ax, word [rbp - 10]
	mov word [rbp - 31], ax
	mov ax, word [rbp - 31]
	imul ax, 2
	mov word [rbp - 33], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 33]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 41], rax
	mov word [rbp - 43], 100
	mov rbx, qword [rbp - 41]
	mov ax, word [rbp - 43]
	mov word [rbx], ax
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
	mov ax, word [rbp - 10]
	mov word [rbp - 45], ax
__L3__:
	mov ax, word [rbp - 45]
	cmp ax, word [rbp - 12]
	jg __LL11__
	mov byte [rbp - 46], 1
	jmp __LL12__
__LL11__:
	mov byte [rbp - 46], 0
__LL12__:
	mov al, byte [rbp - 46]
	cmp al, 1
	jz __L4__
	mov al, byte [rbp - 46]
	cmp al, 0
	jz __L5__
__L4__:
	mov ax, word [rbp - 45]
	sub ax, word [rbp - 10]
	mov word [rbp - 48], ax
	mov ax, word [rbp - 48]
	imul ax, 2
	mov word [rbp - 50], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 50]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 58], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 58]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 45]
	add ax, 1
	mov word [rbp - 60], ax
	mov ax, word [rbp - 60]
	mov word [rbp - 45], ax
	jmp __L3__
__L5__:
	mov rsp, rbp
	pop rbp
	ret

main:
	push rbp
	mov rbp, rsp
	sub rsp, 96
	mov word [rbp - 16], 2
	mov ax, word [rbp - 16]
	mov word [rbp - 4], ax
	mov word [rbp - 18], 4
	mov ax, word [rbp - 18]
	mov word [rbp - 6], ax
	mov ax, word [rbp - 4]
	mov word [rbp - 22], ax
	mov ax, word [rbp - 6]
	mov word [rbp - 24], ax
	mov ax, word [rbp - 6]
	sub ax, word [rbp - 4]
	mov word [rbp - 20], ax
	mov ax, word [rbp - 20]
	add ax, 1
	mov word [rbp - 20], ax
	mov ax, word [rbp - 20]
	imul ax, 2
	mov word [rbp - 20], ax
	xor dx, dx
	mov ax, word [rbp - 20]
	mov cx, 16
	idiv cx
	mov word [rbp - 20], ax
	mov ax, word [rbp - 20]
	add ax, 1
	mov word [rbp - 20], ax
	mov ax, word [rbp - 20]
	imul ax, 16
	mov word [rbp - 20], ax
	mov ax, word [rbp - 20]
	movsx rax, ax
	sub rsp, rax
	mov qword [rbp - 14], rsp
	mov ax, 2
	sub ax, word [rbp - 22]
	mov word [rbp - 26], ax
	mov ax, word [rbp - 26]
	imul ax, 2
	mov word [rbp - 28], ax
	mov rax, qword [rbp - 14]
	mov bx, word [rbp - 28]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 36], rax
	mov word [rbp - 38], 2
	mov rbx, qword [rbp - 36]
	mov ax, word [rbp - 38]
	mov word [rbx], ax
	mov ax, 3
	sub ax, word [rbp - 22]
	mov word [rbp - 40], ax
	mov ax, word [rbp - 40]
	imul ax, 2
	mov word [rbp - 42], ax
	mov rax, qword [rbp - 14]
	mov bx, word [rbp - 42]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 50], rax
	mov word [rbp - 52], 4
	mov rbx, qword [rbp - 50]
	mov ax, word [rbp - 52]
	mov word [rbx], ax
	mov ax, 4
	sub ax, word [rbp - 22]
	mov word [rbp - 54], ax
	mov ax, word [rbp - 54]
	imul ax, 2
	mov word [rbp - 56], ax
	mov rax, qword [rbp - 14]
	mov bx, word [rbp - 56]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 64], rax
	mov word [rbp - 66], 6
	mov rbx, qword [rbp - 64]
	mov ax, word [rbp - 66]
	mov word [rbx], ax
	mov rax, rsp
	sub rax, 24
	mov rbx, qword [rbp - 14]
	mov qword [rax], rbx
	mov rax, rsp
	sub rax, 26
	mov bx, word [rbp - 22]
	mov word [rax], bx
	mov rax, rsp
	sub rax, 28
	mov bx, word [rbp - 24]
	mov word [rax], bx
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
	mov ax, word [rbp - 22]
	mov word [rbp - 68], ax
__L6__:
	mov ax, word [rbp - 68]
	cmp ax, word [rbp - 24]
	jg __LL13__
	mov byte [rbp - 69], 1
	jmp __LL14__
__LL13__:
	mov byte [rbp - 69], 0
__LL14__:
	mov al, byte [rbp - 69]
	cmp al, 1
	jz __L7__
	mov al, byte [rbp - 69]
	cmp al, 0
	jz __L8__
__L7__:
	mov ax, word [rbp - 68]
	sub ax, word [rbp - 22]
	mov word [rbp - 71], ax
	mov ax, word [rbp - 71]
	imul ax, 2
	mov word [rbp - 73], ax
	mov rax, qword [rbp - 14]
	mov bx, word [rbp - 73]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 81], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 81]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 68]
	add ax, 1
	mov word [rbp - 83], ax
	mov ax, word [rbp - 83]
	mov word [rbp - 68], ax
	jmp __L6__
__L8__:


; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
