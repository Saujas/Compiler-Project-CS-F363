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
	sub rsp, 48
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
	sub ax, 2
	mov word [rbp - 7], ax
	mov ax, word [rbp - 7]
	add ax, 1
	mov word [rbp - 7], ax
	mov rax, 0
	mov ax, word [rbp - 7]
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
	mov rax, 'e boolea'
	mov qword [rsp], rax
	add rsp, 8
	mov rax, 'n for ra'
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
	sub rsp, 16
	mov rax, '2'
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
	mov word [rbp - 7], 2
__L0__:
	mov ax, word [rbp - 7]
	cmp ax, 4
	jg __LL10__
	mov byte [rbp - 8], 1
	jmp __LL11__
__LL10__:
	mov byte [rbp - 8], 0
__LL11__:
	mov al, byte [rbp - 8]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp - 8]
	cmp al, 0
	jz __L2__
__L1__:
	mov ax, word [rbp - 7]
	cmp ax, 2
	jge __LL12__
	mov byte [rbp - 9], 1
	jmp __LL13__
__LL12__:
	mov byte [rbp - 9], 0
__LL13__:
	mov al, byte [rbp - 9]
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
	mov ax, word [rbp - 7]
	cmp ax, 4
	jle __LL14__
	mov byte [rbp - 9], 1
	jmp __LL15__
__LL14__:
	mov byte [rbp - 9], 0
__LL15__:
	mov al, byte [rbp - 9]
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
	mov ax, word [rbp - 7]
	sub ax, 2
	mov word [rbp - 11], ax
	mov ax, word [rbp - 11]
	imul ax, 1
	mov word [rbp - 13], ax
	mov rax, rbp
	sub rax, 5
	xor rbx, rbx
	mov bx, word [rbp - 13]
	add rax, rbx
	mov qword [rbp - 21], rax
	mov rbx, qword [rbp - 21]
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov byte [rbx], al
	mov ax, word [rbp - 7]
	add ax, 1
	mov word [rbp - 23], ax
	mov ax, word [rbp - 23]
	mov word [rbp - 7], ax
	jmp __L0__
__L2__:
	sub rsp, 16
	mov rax, 'Output: '
	mov qword [rsp], rax
	add rsp, 8
	mov byte [rsp], 0
	sub rsp, 8
	mov rax, rsp
	mov rdi, fmt_string_no_line_break
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 16
	mov word [rbp - 25], 2
__L5__:
	mov ax, word [rbp - 25]
	cmp ax, 4
	jg __LL16__
	mov byte [rbp - 26], 1
	jmp __LL17__
__LL16__:
	mov byte [rbp - 26], 0
__LL17__:
	mov al, byte [rbp - 26]
	cmp al, 1
	jz __L6__
	mov al, byte [rbp - 26]
	cmp al, 0
	jz __L7__
__L6__:
	mov ax, word [rbp - 25]
	cmp ax, 2
	jge __LL18__
	mov byte [rbp - 27], 1
	jmp __LL19__
__LL18__:
	mov byte [rbp - 27], 0
__LL19__:
	mov al, byte [rbp - 27]
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
	mov ax, word [rbp - 25]
	cmp ax, 4
	jle __LL20__
	mov byte [rbp - 27], 1
	jmp __LL21__
__LL20__:
	mov byte [rbp - 27], 0
__LL21__:
	mov al, byte [rbp - 27]
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
	mov ax, word [rbp - 25]
	sub ax, 2
	mov word [rbp - 29], ax
	mov ax, word [rbp - 29]
	imul ax, 1
	mov word [rbp - 31], ax
	mov rax, rbp
	sub rax, 5
	xor rbx, rbx
	mov bx, word [rbp - 31]
	add rax, rbx
	mov qword [rbp - 39], rax
	mov rbx, qword [rbp - 39]
	cmp byte [rbx], 0
	jz __LL22__
	mov rax, message_true
	jmp __LL23__
__LL22__:
	mov rax, message_false
__LL23__:
	mov rdi, fmt_string_no_line_break
	mov rsi, rax
	xor rax, rax
	call printf
	mov ax, word [rbp - 25]
	add ax, 1
	mov word [rbp - 41], ax
	mov ax, word [rbp - 41]
	mov word [rbp - 25], ax
	jmp __L5__
__L7__:
	sub rsp, 16
	mov rax, '\'
	mov qword [rsp], rax
	add rsp, 0
	mov byte [rsp], 0
	sub rsp, 0
	mov rax, rsp
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
	add rsp, 16
	mov byte [rbp - 42], 1
	mov al, byte [rbp - 42]
	mov byte [rbp - 1], al
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	cmp byte [rbp - 1], 0
	jz __LL24__
	mov rax, message_true
	jmp __LL25__
__LL24__:
	mov rax, message_false
__LL25__:
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf

;exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
