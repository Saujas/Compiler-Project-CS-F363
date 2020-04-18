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

arraySum:
	push rbp
	mov rbp, rsp
	sub rsp, 96
	mov rax, __float64__(0.0)
	mov qword [rbp - 37], rax
	mov rax, qword [rbp - 37]
	mov qword [rbp - 18], rax
	mov word [rbp - 28], 1
__L0__:
	mov ax, word [rbp - 28]
	cmp ax, 15
	jg __LL9__
	mov byte [rbp - 38], 1
	jmp __LL10__
__LL9__:
	mov byte [rbp - 38], 0
__LL10__:
	mov al, byte [rbp - 38]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp - 38]
	cmp al, 0
	jz __L2__
__L1__:
	mov ax, word [rbp - 28]
	cmp ax, word [rbp - 10]
	jg __LL11__
	mov byte [rbp - 39], 1
	jmp __LL12__
__LL11__:
	mov byte [rbp - 39], 0
__LL12__:
	mov al, byte [rbp - 39]
	mov byte [rbp - 29], al
	mov ax, byte [rbp - 29]
	cmp ax, 1
	jnz __LL13__
	mov byte [rbp - 40], 1
	jmp __LL14__
__LL13__:
	mov byte [rbp - 40], 0
__LL14__:
	mov al, byte [rbp - 40]
	cmp al, 1
	jz __L4__
	mov al, byte [rbp - 40]
	cmp al, 0
	jz __L5__
__L4__:
	mov ax, word [rbp - 28]
	sub ax, 1
	mov word [rbp - 42], ax
	mov ax, word [rbp - 42]
	imul ax, 8
	mov word [rbp - 44], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 44]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 52], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 52]
	mov rax, qword [rbx]
	mov rdi, fmt_float
	movq xmm0, rax
	mov eax, 1
	call printf
	mov ax, word [rbp - 28]
	sub ax, 1
	mov word [rbp - 54], ax
	mov ax, word [rbp - 54]
	imul ax, 8
	mov word [rbp - 56], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 56]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 64], rax
	mov rbx, qword [rbp - 64]
	mov rax, qword [rbx]
	mov qword [rbp - 72], rax
	finit
	fld qword [rbp - 18]
	fld qword [rbp - 72]
	fadd
	fstp qword [rbp - 80]
	mov rax, qword [rbp - 80]
	mov qword [rbp - 18], rax
	jmp __L3__
__L5__:
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, qword [rbp - 18]
	mov rdi, fmt_float
	movq xmm0, rax
	mov eax, 1
	call printf
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 28]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
__L3__:
	mov ax, word [rbp - 28]
	add ax, 1
	mov word [rbp - 82], ax
	mov ax, word [rbp - 82]
	mov word [rbp - 28], ax
	jmp __L0__
__L2__:
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, qword [rbp - 18]
	mov rdi, fmt_float
	movq xmm0, rax
	mov eax, 1
	call printf
	mov rbx, rbp
	sub rbx, 18
	mov rax, qword [rbx]
	sub rbx, 8
	mov rbx, qword [rbx]
	mov qword [rbx], rax
	mov rsp, rbp
	pop rbp
	ret

main:
	push rbp
	mov rbp, rsp
	sub rsp, 144
	mov rsi, message_ip_integer
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 122], ax
	mov rax, rsp
	sub rax, 24
	mov rbx, rbp
	sub rbx, 120
	mov qword [rax], rbx
	mov rax, rsp
	sub rax, 138
	mov bx, word [rbp - 122]
	mov word [rax], bx
	call readArr
	mov rax, rsp
	sub rax, 24
	mov rbx, rbp
	sub rbx, 120
	mov qword [rax], rbx
	mov rax, rsp
	sub rax, 138
	mov bx, word [rbp - 122]
	mov word [rax], bx
	mov rax, rsp
	sub rax, 154
	mov rbx, rbp
	sub rbx, 130
	mov qword [rax], rbx
	call arraySum
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, qword [rbp - 130]
	mov rdi, fmt_float
	movq xmm0, rax
	mov eax, 1
	call printf
readArr:
	push rbp
	mov rbp, rsp
	sub rsp, 48
	mov word [rbp - 22], 1
	mov ax, word [rbp - 22]
	mov word [rbp - 20], ax
__L6__:
	mov ax, word [rbp - 20]
	cmp ax, word [rbp - 10]
	jg __LL15__
	mov byte [rbp - 23], 1
	jmp __LL16__
__LL15__:
	mov byte [rbp - 23], 0
__LL16__:
	mov al, byte [rbp - 23]
	cmp al, 1
	jz __L7__
	mov al, byte [rbp - 23]
	cmp al, 0
	jz __L8__
__L7__:
	mov rsi, message_ip_real
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, rbp
	sub rsi, 18
	mov rdi, fmt_ip_float
	mov al, 0
	call scanf
	mov ax, word [rbp - 20]
	sub ax, 1
	mov word [rbp - 25], ax
	mov ax, word [rbp - 25]
	imul ax, 8
	mov word [rbp - 27], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 27]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 35], rax
	mov rax, qword [rbp - 18]
	mov qword [rbp - 43], rax
	mov rbx, qword [rbp - 35]
	mov rax, qword [rbp - 43]
	mov qword [rbx], rax
	mov ax, word [rbp - 20]
	add ax, 1
	mov word [rbp - 45], ax
	mov ax, word [rbp - 45]
	mov word [rbp - 20], ax
	jmp __L6__
__L8__:
	mov rsp, rbp
	pop rbp
	ret



; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
