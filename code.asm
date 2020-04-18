extern printf, scanf

section .data
	fmt_integer: db '%d', 10, 0
	fmt_integer_no_line_break: db '%d', 0
	fmt_float: db '%f', 10, 0
	fmt_float_no_line_break: db '%f', 0
	fmt_string: db '%s', 10, 0
	fmt_string_no_line_break: db '%s', 0
	fmt_ip_integer: db '%d', 0
	fmt_ip_float: db '%lf', 0
	message_true: db 'true', 0
	message_false: db 'false', 0
	message_lb: db 10, 0
	message_ip_integer: db 'Input: Enter an integer value: ', 0
	message_ip_real: db 'Input: Enter a real value: ', 0
	message_ip_boolean: db 'Input: Enter a boolean value: ', 0
	message_output: db 'Output: ', 0
	buffer_integer: dd 0

section .bss

section .text
global main

m1:
	push rbp
	mov rbp, rsp
	sub rsp, 32
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
	mov word [rbp - 14], 2
__L0__:
	mov ax, word [rbp - 14]
	cmp ax, 4
	jg __LL10__
	mov byte [rbp - 15], 1
	jmp __LL11__
__LL10__:
	mov byte [rbp - 15], 0
__LL11__:
	mov al, byte [rbp - 15]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp - 15]
	cmp al, 0
	jz __L2__
__L1__:
	mov ax, word [rbp - 14]
	cmp ax, 2
	jge __LL12__
	mov byte [rbp - 16], 1
	jmp __LL13__
__LL12__:
	mov byte [rbp - 16], 0
__LL13__:
	mov al, byte [rbp - 16]
	cmp al, 0
	jz __L3__
	sub rsp, 48
	mov rax, 'RUN TIME'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, ' ERROR: '
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'Array in'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'dex out '
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'of bound'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'sf bound'
	mov qword [rsp], rax
	add rsp, 1
	mov byte [rsp], 0
	sub rsp, 41
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 48

;exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
__L3__:
	mov ax, word [rbp - 14]
	cmp ax, 4
	jle __LL14__
	mov byte [rbp - 16], 1
	jmp __LL15__
__LL14__:
	mov byte [rbp - 16], 0
__LL15__:
	mov al, byte [rbp - 16]
	cmp al, 0
	jz __L4__
	sub rsp, 48
	mov rax, 'RUN TIME'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, ' ERROR: '
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'Array in'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'dex out '
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'of bound'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'sf bound'
	mov qword [rsp], rax
	add rsp, 1
	mov byte [rsp], 0
	sub rsp, 41
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 48

;exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
__L4__:
	mov ax, word [rbp - 14]
	sub ax, 2
	mov word [rbp - 18], ax
	mov ax, word [rbp - 18]
	imul ax, 2
	mov word [rbp - 20], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 20]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 28], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 28]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 14]
	add ax, 1
	mov word [rbp - 30], ax
	mov ax, word [rbp - 30]
	mov word [rbp - 14], ax
	jmp __L0__
__L2__:
	sub rsp, 32
	mov rax, 'Array el'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'ements p'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'rinted p'
	mov qword [rsp], rax
	add rsp, 6
	mov byte [rsp], 0
	sub rsp, 22
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 32
	mov rsp, rbp
	pop rbp
	ret

main:
	push rbp
	mov rbp, rsp
	sub rsp, 48
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
	mov word [rbp - 16], ax
	mov word [rbp - 18], 4
	mov word [rbp - 14], 4
	mov ax, word [rbp - 14]
	sub ax, word [rbp - 2]
	mov word [rbp - 14], ax
	mov ax, word [rbp - 14]
	add ax, 1
	mov word [rbp - 14], ax
	mov ax, word [rbp - 14]
	imul ax, 2
	mov word [rbp - 14], ax
	xor dx, dx
	mov ax, word [rbp - 14]
	mov cx, 16
	idiv cx
	mov word [rbp - 14], ax
	mov ax, word [rbp - 14]
	add ax, 1
	mov word [rbp - 14], ax
	mov ax, word [rbp - 14]
	imul ax, 16
	mov word [rbp - 14], ax
	mov ax, word [rbp - 14]
	movsx rax, ax
	sub rsp, rax
	mov qword [rbp - 12], rsp
	sub rsp, 16
	mov rax, 'Enter '
	mov qword [rsp], rax
	add rsp, 6
	mov byte [rsp], 0
	sub rsp, 6
	mov rax, rsp
	mov rdi, fmt_string_no_line_break
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 16
	mov ax, 4
	sub ax, word [rbp - 16]
	mov word [rbp - 20], ax
	mov ax, word [rbp - 20]
	add ax, 1
	mov word [rbp - 20], ax
	mov rax, 0
	mov ax, word [rbp - 20]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	sub rsp, 48
	mov rax, ' element'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 's of typ'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'e intege'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'r for ra'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'nge r ra'
	mov qword [rsp], rax
	add rsp, 4
	mov byte [rsp], 0
	sub rsp, 36
	mov rax, rsp
	mov rdi, fmt_string_no_line_break
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 48
	mov rax, 0
	mov ax, word [rbp - 16]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	sub rsp, 16
	mov rax, ' to '
	mov qword [rsp], rax
	add rsp, 4
	mov byte [rsp], 0
	sub rsp, 4
	mov rax, rsp
	mov rdi, fmt_string_no_line_break
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 16
	sub rsp, 16
	mov rax, '4'
	mov qword [rsp], rax
	add rsp, 1
	mov byte [rsp], 0
	sub rsp, 1
	mov rax, rsp
	mov rdi, fmt_string_no_line_break
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 16
	mov rax, message_lb
	mov rdi, fmt_string_no_line_break
	mov rsi, rax
	xor rax, rax
	call printf
	mov ax, word [rbp - 16]
	mov word [rbp - 20], ax
__L5__:
	mov ax, word [rbp - 20]
	cmp ax, 4
	jg __LL16__
	mov byte [rbp - 21], 1
	jmp __LL17__
__LL16__:
	mov byte [rbp - 21], 0
__LL17__:
	mov al, byte [rbp - 21]
	cmp al, 1
	jz __L6__
	mov al, byte [rbp - 21]
	cmp al, 0
	jz __L7__
__L6__:
	mov ax, word [rbp - 20]
	cmp ax, word [rbp - 16]
	jge __LL18__
	mov byte [rbp - 22], 1
	jmp __LL19__
__LL18__:
	mov byte [rbp - 22], 0
__LL19__:
	mov al, byte [rbp - 22]
	cmp al, 0
	jz __L8__
	sub rsp, 48
	mov rax, 'RUN TIME'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, ' ERROR: '
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'Array in'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'dex out '
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'of bound'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'sf bound'
	mov qword [rsp], rax
	add rsp, 1
	mov byte [rsp], 0
	sub rsp, 41
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 48

;exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
__L8__:
	mov ax, word [rbp - 20]
	cmp ax, 4
	jle __LL20__
	mov byte [rbp - 22], 1
	jmp __LL21__
__LL20__:
	mov byte [rbp - 22], 0
__LL21__:
	mov al, byte [rbp - 22]
	cmp al, 0
	jz __L9__
	sub rsp, 48
	mov rax, 'RUN TIME'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, ' ERROR: '
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'Array in'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'dex out '
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'of bound'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'sf bound'
	mov qword [rsp], rax
	add rsp, 1
	mov byte [rsp], 0
	sub rsp, 41
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 48

;exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
__L9__:
	mov ax, word [rbp - 20]
	sub ax, word [rbp - 16]
	mov word [rbp - 24], ax
	mov ax, word [rbp - 24]
	imul ax, 2
	mov word [rbp - 26], ax
	mov rax, qword [rbp - 12]
	mov bx, word [rbp - 26]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 34], rax
	mov rbx, qword [rbp - 34]
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
	mov ax, word [rbp - 20]
	add ax, 1
	mov word [rbp - 36], ax
	mov ax, word [rbp - 36]
	mov word [rbp - 20], ax
	jmp __L5__
__L7__:
	sub rsp, 32
	mov rax, 'End of a'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'rray inp'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'utay inp'
	mov qword [rsp], rax
	add rsp, 2
	mov byte [rsp], 0
	sub rsp, 18
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 32
	mov rax, rsp
	sub rax, 24
	mov rbx, qword [rbp - 12]
	mov qword [rax], rbx
	mov rax, rsp
	sub rax, 26
	mov bx, word [rbp - 16]
	mov word [rax], bx
	mov bx, 4
	mov word [rax], bx
	call m1

;exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
