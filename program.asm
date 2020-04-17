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

main:
	push rbp
	mov rbp, rsp
	sub rsp, 144
	mov word [rbp - 24], 1
	mov ax, word [rbp - 24]
	mov word [rbp - 4], ax
	mov word [rbp - 26], 3
	mov ax, word [rbp - 26]
	mov word [rbp - 6], ax
	mov word [rbp - 28], 3
	mov ax, word [rbp - 28]
	mov word [rbp - 2], ax
	mov ax, word [rbp - 4]
	mov word [rbp - 32], ax
	mov ax, word [rbp - 6]
	mov word [rbp - 34], ax
	mov ax, word [rbp - 6]
	sub ax, word [rbp - 4]
	mov word [rbp - 30], ax
	mov ax, word [rbp - 30]
	add ax, 1
	mov word [rbp - 30], ax
	mov ax, word [rbp - 30]
	imul ax, 2
	mov word [rbp - 30], ax
	xor dx, dx
	mov ax, word [rbp - 30]
	mov cx, 16
	idiv cx
	mov word [rbp - 30], ax
	mov ax, word [rbp - 30]
	add ax, 1
	mov word [rbp - 30], ax
	mov ax, word [rbp - 30]
	imul ax, 16
	mov word [rbp - 30], ax
	mov ax, word [rbp - 30]
	movsx rax, ax
	sub rsp, rax
	mov qword [rbp - 14], rsp
	mov ax, word [rbp - 2]
	mov word [rbp - 38], ax
	mov word [rbp - 40], 6
	mov word [rbp - 36], 6
	mov ax, word [rbp - 36]
	sub ax, word [rbp - 2]
	mov word [rbp - 36], ax
	mov ax, word [rbp - 36]
	add ax, 1
	mov word [rbp - 36], ax
	mov ax, word [rbp - 36]
	imul ax, 8
	mov word [rbp - 36], ax
	xor dx, dx
	mov ax, word [rbp - 36]
	mov cx, 16
	idiv cx
	mov word [rbp - 36], ax
	mov ax, word [rbp - 36]
	add ax, 1
	mov word [rbp - 36], ax
	mov ax, word [rbp - 36]
	imul ax, 16
	mov word [rbp - 36], ax
	mov ax, word [rbp - 36]
	movsx rax, ax
	sub rsp, rax
	mov qword [rbp - 22], rsp
	mov ax, 1
	sub ax, word [rbp - 32]
	mov word [rbp - 42], ax
	mov ax, word [rbp - 42]
	imul ax, 2
	mov word [rbp - 44], ax
	mov rax, qword [rbp - 14]
	mov bx, word [rbp - 44]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 52], rax
	mov word [rbp - 54], 2
	mov rbx, qword [rbp - 52]
	mov ax, word [rbp - 54]
	mov word [rbx], ax
	mov ax, 2
	sub ax, word [rbp - 32]
	mov word [rbp - 56], ax
	mov ax, word [rbp - 56]
	imul ax, 2
	mov word [rbp - 58], ax
	mov rax, qword [rbp - 14]
	mov bx, word [rbp - 58]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 66], rax
	mov word [rbp - 68], 4
	mov rbx, qword [rbp - 66]
	mov ax, word [rbp - 68]
	mov word [rbx], ax
	mov ax, 3
	sub ax, word [rbp - 32]
	mov word [rbp - 70], ax
	mov ax, word [rbp - 70]
	imul ax, 2
	mov word [rbp - 72], ax
	mov rax, qword [rbp - 14]
	mov bx, word [rbp - 72]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 80], rax
	mov word [rbp - 82], 4
	mov rbx, qword [rbp - 80]
	mov ax, word [rbp - 82]
	mov word [rbx], ax
	mov word [rbp - 2], 3
__L0__:
	mov ax, word [rbp - 2]
	cmp ax, 6
	jg __LL9__
	mov byte [rbp - 83], 1
	jmp __LL10__
__LL9__:
	mov byte [rbp - 83], 0
__LL10__:
	mov al, byte [rbp - 83]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp - 83]
	cmp al, 0
	jz __L2__
__L1__:
	mov ax, word [rbp - 2]
	sub ax, word [rbp - 38]
	mov word [rbp - 85], ax
	mov ax, word [rbp - 85]
	imul ax, 8
	mov word [rbp - 87], ax
	mov rax, qword [rbp - 22]
	mov bx, word [rbp - 87]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 95], rax
	mov rax, __float64__(5.6)
	mov qword [rbp - 103], rax
	mov rbx, qword [rbp - 95]
	mov rax, qword [rbp - 103]
	mov qword [rbx], rax
	mov ax, word [rbp - 2]
	add ax, 1
	mov word [rbp - 105], ax
	mov ax, word [rbp - 105]
	mov word [rbp - 2], ax
	jmp __L0__
__L2__:
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
	mov ax, word [rbp - 32]
	mov word [rbp - 107], ax
__L3__:
	mov ax, word [rbp - 107]
	cmp ax, word [rbp - 34]
	jg __LL11__
	mov byte [rbp - 108], 1
	jmp __LL12__
__LL11__:
	mov byte [rbp - 108], 0
__LL12__:
	mov al, byte [rbp - 108]
	cmp al, 1
	jz __L4__
	mov al, byte [rbp - 108]
	cmp al, 0
	jz __L5__
__L4__:
	mov ax, word [rbp - 107]
	sub ax, word [rbp - 32]
	mov word [rbp - 110], ax
	mov ax, word [rbp - 110]
	imul ax, 2
	mov word [rbp - 112], ax
	mov rax, qword [rbp - 14]
	mov bx, word [rbp - 112]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 120], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 120]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 107]
	add ax, 1
	mov word [rbp - 122], ax
	mov ax, word [rbp - 122]
	mov word [rbp - 107], ax
	jmp __L3__
__L5__:
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
	mov ax, word [rbp - 38]
	mov word [rbp - 124], ax
__L6__:
	mov ax, word [rbp - 124]
	cmp ax, 6
	jg __LL13__
	mov byte [rbp - 125], 1
	jmp __LL14__
__LL13__:
	mov byte [rbp - 125], 0
__LL14__:
	mov al, byte [rbp - 125]
	cmp al, 1
	jz __L7__
	mov al, byte [rbp - 125]
	cmp al, 0
	jz __L8__
__L7__:
	mov ax, word [rbp - 124]
	sub ax, word [rbp - 38]
	mov word [rbp - 127], ax
	mov ax, word [rbp - 127]
	imul ax, 8
	mov word [rbp - 129], ax
	mov rax, qword [rbp - 22]
	mov bx, word [rbp - 129]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 137], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 137]
	mov rax, qword [rbx]
	mov rdi, fmt_float
	movq xmm0, rax
	mov eax, 1
	call printf
	mov ax, word [rbp - 124]
	add ax, 1
	mov word [rbp - 139], ax
	mov ax, word [rbp - 139]
	mov word [rbp - 124], ax
	jmp __L6__
__L8__:


; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
