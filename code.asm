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

array_parameter_demo:
	push rbp
	mov rbp, rsp
	sub rsp, 464
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
	mov word [rbp - 96], 10
__L0__:
	mov ax, word [rbp - 96]
	cmp ax, 14
	jg __LL92__
	mov byte [rbp - 97], 1
	jmp __LL93__
__LL92__:
	mov byte [rbp - 97], 0
__LL93__:
	mov al, byte [rbp - 97]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp - 97]
	cmp al, 0
	jz __L2__
__L1__:
	mov ax, word [rbp - 96]
	cmp ax, 10
	jge __LL94__
	mov byte [rbp - 98], 1
	jmp __LL95__
__LL94__:
	mov byte [rbp - 98], 0
__LL95__:
	mov al, byte [rbp - 98]
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
	mov ax, word [rbp - 96]
	cmp ax, 14
	jle __LL96__
	mov byte [rbp - 98], 1
	jmp __LL97__
__LL96__:
	mov byte [rbp - 98], 0
__LL97__:
	mov al, byte [rbp - 98]
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
	mov ax, word [rbp - 96]
	sub ax, 10
	mov word [rbp - 100], ax
	mov ax, word [rbp - 100]
	imul ax, 2
	mov word [rbp - 102], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 102]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 110], rax
	mov rbx, qword [rbp - 110]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 96]
	add ax, 1
	mov word [rbp - 112], ax
	mov ax, word [rbp - 112]
	mov word [rbp - 96], ax
	jmp __L0__
__L2__:
	sub rsp, 16
	mov rax, '+^+各'
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
	mov ax, word [rbp - 22]
	mov word [rbp - 114], ax
__L5__:
	mov ax, word [rbp - 114]
	cmp ax, word [rbp - 24]
	jg __LL98__
	mov byte [rbp - 115], 1
	jmp __LL99__
__LL98__:
	mov byte [rbp - 115], 0
__LL99__:
	mov al, byte [rbp - 115]
	cmp al, 1
	jz __L6__
	mov al, byte [rbp - 115]
	cmp al, 0
	jz __L7__
__L6__:
	mov ax, word [rbp - 114]
	cmp ax, word [rbp - 22]
	jge __LL100__
	mov byte [rbp - 116], 1
	jmp __LL101__
__LL100__:
	mov byte [rbp - 116], 0
__LL101__:
	mov al, byte [rbp - 116]
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
	mov ax, word [rbp - 114]
	cmp ax, word [rbp - 24]
	jle __LL102__
	mov byte [rbp - 116], 1
	jmp __LL103__
__LL102__:
	mov byte [rbp - 116], 0
__LL103__:
	mov al, byte [rbp - 116]
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
	mov ax, word [rbp - 114]
	sub ax, word [rbp - 22]
	mov word [rbp - 118], ax
	mov ax, word [rbp - 118]
	imul ax, 2
	mov word [rbp - 120], ax
	mov rax, qword [rbp - 20]
	mov bx, word [rbp - 120]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 128], rax
	mov rbx, qword [rbp - 128]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 114]
	add ax, 1
	mov word [rbp - 130], ax
	mov ax, word [rbp - 130]
	mov word [rbp - 114], ax
	jmp __L5__
__L7__:
	sub rsp, 16
	mov rax, '+^+各'
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
	mov rsi, message_ip_integer
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 60], ax
	mov rsi, message_ip_integer
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 62], ax
	mov ax, word [rbp - 60]
	mov word [rbp - 134], ax
	mov ax, word [rbp - 62]
	mov word [rbp - 136], ax
	mov ax, word [rbp - 62]
	sub ax, word [rbp - 60]
	mov word [rbp - 132], ax
	mov ax, word [rbp - 132]
	add ax, 1
	mov word [rbp - 132], ax
	mov ax, word [rbp - 132]
	imul ax, 2
	mov word [rbp - 132], ax
	xor dx, dx
	mov ax, word [rbp - 132]
	mov cx, 16
	idiv cx
	mov word [rbp - 132], ax
	mov ax, word [rbp - 132]
	add ax, 1
	mov word [rbp - 132], ax
	mov ax, word [rbp - 132]
	imul ax, 16
	mov word [rbp - 132], ax
	mov ax, word [rbp - 132]
	movsx rax, ax
	sub rsp, rax
	mov qword [rbp - 90], rsp
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
	mov ax, 14
	sub ax, 10
	mov word [rbp - 138], ax
	mov ax, word [rbp - 138]
	add ax, 1
	mov word [rbp - 138], ax
	mov rax, 0
	mov ax, word [rbp - 138]
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
	sub rsp, 16
	mov rax, '10'
	mov qword [rsp], rax
	add rsp, 2
	mov byte [rsp], 0
	sub rsp, 2
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
	mov rax, '14'
	mov qword [rsp], rax
	add rsp, 2
	mov byte [rsp], 0
	sub rsp, 2
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
	mov word [rbp - 138], 10
__L10__:
	mov ax, word [rbp - 138]
	cmp ax, 14
	jg __LL104__
	mov byte [rbp - 139], 1
	jmp __LL105__
__LL104__:
	mov byte [rbp - 139], 0
__LL105__:
	mov al, byte [rbp - 139]
	cmp al, 1
	jz __L11__
	mov al, byte [rbp - 139]
	cmp al, 0
	jz __L12__
__L11__:
	mov ax, word [rbp - 138]
	cmp ax, 10
	jge __LL106__
	mov byte [rbp - 140], 1
	jmp __LL107__
__LL106__:
	mov byte [rbp - 140], 0
__LL107__:
	mov al, byte [rbp - 140]
	cmp al, 0
	jz __L13__
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
__L13__:
	mov ax, word [rbp - 138]
	cmp ax, 14
	jle __LL108__
	mov byte [rbp - 140], 1
	jmp __LL109__
__LL108__:
	mov byte [rbp - 140], 0
__LL109__:
	mov al, byte [rbp - 140]
	cmp al, 0
	jz __L14__
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
__L14__:
	mov ax, word [rbp - 138]
	sub ax, 10
	mov word [rbp - 142], ax
	mov ax, word [rbp - 142]
	imul ax, 2
	mov word [rbp - 144], ax
	mov rax, rbp
	sub rax, 72
	xor rbx, rbx
	mov bx, word [rbp - 144]
	add rax, rbx
	mov qword [rbp - 152], rax
	mov rbx, qword [rbp - 152]
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbx], ax
	mov ax, word [rbp - 138]
	add ax, 1
	mov word [rbp - 154], ax
	mov ax, word [rbp - 154]
	mov word [rbp - 138], ax
	jmp __L10__
__L12__:
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
	mov ax, word [rbp - 136]
	sub ax, word [rbp - 134]
	mov word [rbp - 156], ax
	mov ax, word [rbp - 156]
	add ax, 1
	mov word [rbp - 156], ax
	mov rax, 0
	mov ax, word [rbp - 156]
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
	mov ax, word [rbp - 134]
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
	mov rax, 0
	mov ax, word [rbp - 136]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov rax, message_lb
	mov rdi, fmt_string_no_line_break
	mov rsi, rax
	xor rax, rax
	call printf
	mov ax, word [rbp - 134]
	mov word [rbp - 156], ax
__L15__:
	mov ax, word [rbp - 156]
	cmp ax, word [rbp - 136]
	jg __LL110__
	mov byte [rbp - 157], 1
	jmp __LL111__
__LL110__:
	mov byte [rbp - 157], 0
__LL111__:
	mov al, byte [rbp - 157]
	cmp al, 1
	jz __L16__
	mov al, byte [rbp - 157]
	cmp al, 0
	jz __L17__
__L16__:
	mov ax, word [rbp - 156]
	cmp ax, word [rbp - 134]
	jge __LL112__
	mov byte [rbp - 158], 1
	jmp __LL113__
__LL112__:
	mov byte [rbp - 158], 0
__LL113__:
	mov al, byte [rbp - 158]
	cmp al, 0
	jz __L18__
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
__L18__:
	mov ax, word [rbp - 156]
	cmp ax, word [rbp - 136]
	jle __LL114__
	mov byte [rbp - 158], 1
	jmp __LL115__
__LL114__:
	mov byte [rbp - 158], 0
__LL115__:
	mov al, byte [rbp - 158]
	cmp al, 0
	jz __L19__
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
__L19__:
	mov ax, word [rbp - 156]
	sub ax, word [rbp - 134]
	mov word [rbp - 160], ax
	mov ax, word [rbp - 160]
	imul ax, 2
	mov word [rbp - 162], ax
	mov rax, qword [rbp - 90]
	mov bx, word [rbp - 162]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 170], rax
	mov rbx, qword [rbp - 170]
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbx], ax
	mov ax, word [rbp - 156]
	add ax, 1
	mov word [rbp - 172], ax
	mov ax, word [rbp - 172]
	mov word [rbp - 156], ax
	jmp __L15__
__L17__:
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
	mov word [rbp - 174], 10
__L20__:
	mov ax, word [rbp - 174]
	cmp ax, 14
	jg __LL116__
	mov byte [rbp - 175], 1
	jmp __LL117__
__LL116__:
	mov byte [rbp - 175], 0
__LL117__:
	mov al, byte [rbp - 175]
	cmp al, 1
	jz __L21__
	mov al, byte [rbp - 175]
	cmp al, 0
	jz __L22__
__L21__:
	mov ax, word [rbp - 174]
	cmp ax, 10
	jge __LL118__
	mov byte [rbp - 176], 1
	jmp __LL119__
__LL118__:
	mov byte [rbp - 176], 0
__LL119__:
	mov al, byte [rbp - 176]
	cmp al, 0
	jz __L23__
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
__L23__:
	mov ax, word [rbp - 174]
	cmp ax, 14
	jle __LL120__
	mov byte [rbp - 176], 1
	jmp __LL121__
__LL120__:
	mov byte [rbp - 176], 0
__LL121__:
	mov al, byte [rbp - 176]
	cmp al, 0
	jz __L24__
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
__L24__:
	mov ax, word [rbp - 174]
	sub ax, 10
	mov word [rbp - 178], ax
	mov ax, word [rbp - 178]
	imul ax, 2
	mov word [rbp - 180], ax
	mov rax, rbp
	sub rax, 72
	xor rbx, rbx
	mov bx, word [rbp - 180]
	add rax, rbx
	mov qword [rbp - 188], rax
	mov rbx, qword [rbp - 188]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 174]
	add ax, 1
	mov word [rbp - 190], ax
	mov ax, word [rbp - 190]
	mov word [rbp - 174], ax
	jmp __L20__
__L22__:
	sub rsp, 16
	mov rax, '+^+各'
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
	mov word [rbp - 192], 0
	mov ax, word [rbp - 192]
	mov word [rbp - 26], ax
	mov word [rbp - 56], 10
__L25__:
	mov ax, word [rbp - 56]
	cmp ax, 14
	jg __LL122__
	mov byte [rbp - 193], 1
	jmp __LL123__
__LL122__:
	mov byte [rbp - 193], 0
__LL123__:
	mov al, byte [rbp - 193]
	cmp al, 1
	jz __L26__
	mov al, byte [rbp - 193]
	cmp al, 0
	jz __L27__
__L26__:
	mov ax, word [rbp - 56]
	cmp ax, 10
	jge __LL124__
	mov byte [rbp - 194], 1
	jmp __LL125__
__LL124__:
	mov byte [rbp - 194], 0
__LL125__:
	mov al, byte [rbp - 194]
	cmp al, 0
	jz __L28__
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
__L28__:
	mov ax, word [rbp - 56]
	cmp ax, 14
	jle __LL126__
	mov byte [rbp - 194], 1
	jmp __LL127__
__LL126__:
	mov byte [rbp - 194], 0
__LL127__:
	mov al, byte [rbp - 194]
	cmp al, 0
	jz __L29__
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
__L29__:
	mov ax, word [rbp - 56]
	sub ax, 10
	mov word [rbp - 196], ax
	mov ax, word [rbp - 196]
	imul ax, 2
	mov word [rbp - 198], ax
	mov rax, rbp
	sub rax, 72
	xor rbx, rbx
	mov bx, word [rbp - 198]
	add rax, rbx
	mov qword [rbp - 206], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 206]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 56]
	cmp ax, 10
	jge __LL128__
	mov byte [rbp - 207], 1
	jmp __LL129__
__LL128__:
	mov byte [rbp - 207], 0
__LL129__:
	mov al, byte [rbp - 207]
	cmp al, 0
	jz __L30__
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
__L30__:
	mov ax, word [rbp - 56]
	cmp ax, 14
	jle __LL130__
	mov byte [rbp - 207], 1
	jmp __LL131__
__LL130__:
	mov byte [rbp - 207], 0
__LL131__:
	mov al, byte [rbp - 207]
	cmp al, 0
	jz __L31__
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
__L31__:
	mov ax, word [rbp - 56]
	sub ax, 10
	mov word [rbp - 209], ax
	mov ax, word [rbp - 209]
	imul ax, 2
	mov word [rbp - 211], ax
	mov rax, rbp
	sub rax, 72
	xor rbx, rbx
	mov bx, word [rbp - 211]
	add rax, rbx
	mov qword [rbp - 219], rax
	mov rbx, qword [rbp - 219]
	mov ax, word [rbx]
	mov word [rbp - 221], ax
	mov ax, word [rbp - 26]
	add ax, word [rbp - 221]
	mov word [rbp - 223], ax
	mov ax, word [rbp - 223]
	mov word [rbp - 26], ax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 26]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 56]
	add ax, 1
	mov word [rbp - 225], ax
	mov ax, word [rbp - 225]
	mov word [rbp - 56], ax
	jmp __L25__
__L27__:
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
	mov word [rbp - 227], 10
__L32__:
	mov ax, word [rbp - 227]
	cmp ax, 14
	jg __LL132__
	mov byte [rbp - 228], 1
	jmp __LL133__
__LL132__:
	mov byte [rbp - 228], 0
__LL133__:
	mov al, byte [rbp - 228]
	cmp al, 1
	jz __L33__
	mov al, byte [rbp - 228]
	cmp al, 0
	jz __L34__
__L33__:
	mov ax, word [rbp - 227]
	cmp ax, 10
	jge __LL134__
	mov byte [rbp - 229], 1
	jmp __LL135__
__LL134__:
	mov byte [rbp - 229], 0
__LL135__:
	mov al, byte [rbp - 229]
	cmp al, 0
	jz __L35__
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
__L35__:
	mov ax, word [rbp - 227]
	cmp ax, 14
	jle __LL136__
	mov byte [rbp - 229], 1
	jmp __LL137__
__LL136__:
	mov byte [rbp - 229], 0
__LL137__:
	mov al, byte [rbp - 229]
	cmp al, 0
	jz __L36__
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
__L36__:
	mov ax, word [rbp - 227]
	sub ax, 10
	mov word [rbp - 231], ax
	mov ax, word [rbp - 231]
	imul ax, 2
	mov word [rbp - 233], ax
	mov rax, rbp
	sub rax, 72
	xor rbx, rbx
	mov bx, word [rbp - 233]
	add rax, rbx
	mov qword [rbp - 241], rax
	mov rbx, qword [rbp - 241]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 227]
	add ax, 1
	mov word [rbp - 243], ax
	mov ax, word [rbp - 243]
	mov word [rbp - 227], ax
	jmp __L32__
__L34__:
	sub rsp, 16
	mov rax, '+^+各'
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
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 26]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, 5
	cmp ax, word [rbp - 134]
	jge __LL138__
	mov byte [rbp - 244], 1
	jmp __LL139__
__LL138__:
	mov byte [rbp - 244], 0
__LL139__:
	mov al, byte [rbp - 244]
	cmp al, 0
	jz __L37__
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
__L37__:
	mov ax, 5
	cmp ax, word [rbp - 136]
	jle __LL140__
	mov byte [rbp - 244], 1
	jmp __LL141__
__LL140__:
	mov byte [rbp - 244], 0
__LL141__:
	mov al, byte [rbp - 244]
	cmp al, 0
	jz __L38__
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
__L38__:
	mov ax, 5
	sub ax, word [rbp - 134]
	mov word [rbp - 246], ax
	mov ax, word [rbp - 246]
	imul ax, 2
	mov word [rbp - 248], ax
	mov rax, qword [rbp - 90]
	mov bx, word [rbp - 248]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 256], rax
	mov ax, 6
	cmp ax, word [rbp - 134]
	jge __LL142__
	mov byte [rbp - 257], 1
	jmp __LL143__
__LL142__:
	mov byte [rbp - 257], 0
__LL143__:
	mov al, byte [rbp - 257]
	cmp al, 0
	jz __L39__
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
__L39__:
	mov ax, 6
	cmp ax, word [rbp - 136]
	jle __LL144__
	mov byte [rbp - 257], 1
	jmp __LL145__
__LL144__:
	mov byte [rbp - 257], 0
__LL145__:
	mov al, byte [rbp - 257]
	cmp al, 0
	jz __L40__
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
__L40__:
	mov ax, 6
	sub ax, word [rbp - 134]
	mov word [rbp - 259], ax
	mov ax, word [rbp - 259]
	imul ax, 2
	mov word [rbp - 261], ax
	mov rax, qword [rbp - 90]
	mov bx, word [rbp - 261]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 269], rax
	mov rbx, qword [rbp - 269]
	mov ax, word [rbx]
	mov word [rbp - 271], ax
	mov ax, 7
	cmp ax, word [rbp - 134]
	jge __LL146__
	mov byte [rbp - 272], 1
	jmp __LL147__
__LL146__:
	mov byte [rbp - 272], 0
__LL147__:
	mov al, byte [rbp - 272]
	cmp al, 0
	jz __L41__
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
__L41__:
	mov ax, 7
	cmp ax, word [rbp - 136]
	jle __LL148__
	mov byte [rbp - 272], 1
	jmp __LL149__
__LL148__:
	mov byte [rbp - 272], 0
__LL149__:
	mov al, byte [rbp - 272]
	cmp al, 0
	jz __L42__
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
__L42__:
	mov ax, 7
	sub ax, word [rbp - 134]
	mov word [rbp - 274], ax
	mov ax, word [rbp - 274]
	imul ax, 2
	mov word [rbp - 276], ax
	mov rax, qword [rbp - 90]
	mov bx, word [rbp - 276]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 284], rax
	mov rbx, qword [rbp - 284]
	mov ax, word [rbx]
	mov word [rbp - 286], ax
	mov ax, word [rbp - 271]
	add ax, word [rbp - 286]
	mov word [rbp - 288], ax
	mov rbx, qword [rbp - 256]
	mov ax, word [rbp - 288]
	mov word [rbx], ax
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
	mov ax, word [rbp - 134]
	mov word [rbp - 290], ax
__L43__:
	mov ax, word [rbp - 290]
	cmp ax, word [rbp - 136]
	jg __LL150__
	mov byte [rbp - 291], 1
	jmp __LL151__
__LL150__:
	mov byte [rbp - 291], 0
__LL151__:
	mov al, byte [rbp - 291]
	cmp al, 1
	jz __L44__
	mov al, byte [rbp - 291]
	cmp al, 0
	jz __L45__
__L44__:
	mov ax, word [rbp - 290]
	cmp ax, word [rbp - 134]
	jge __LL152__
	mov byte [rbp - 292], 1
	jmp __LL153__
__LL152__:
	mov byte [rbp - 292], 0
__LL153__:
	mov al, byte [rbp - 292]
	cmp al, 0
	jz __L46__
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
__L46__:
	mov ax, word [rbp - 290]
	cmp ax, word [rbp - 136]
	jle __LL154__
	mov byte [rbp - 292], 1
	jmp __LL155__
__LL154__:
	mov byte [rbp - 292], 0
__LL155__:
	mov al, byte [rbp - 292]
	cmp al, 0
	jz __L47__
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
__L47__:
	mov ax, word [rbp - 290]
	sub ax, word [rbp - 134]
	mov word [rbp - 294], ax
	mov ax, word [rbp - 294]
	imul ax, 2
	mov word [rbp - 296], ax
	mov rax, qword [rbp - 90]
	mov bx, word [rbp - 296]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 304], rax
	mov rbx, qword [rbp - 304]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 290]
	add ax, 1
	mov word [rbp - 306], ax
	mov ax, word [rbp - 306]
	mov word [rbp - 290], ax
	jmp __L43__
__L45__:
	sub rsp, 16
	mov rax, '+^+各'
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
	mov word [rbp - 308], 0
	mov ax, word [rbp - 308]
	mov word [rbp - 36], ax
	mov word [rbp - 310], 10
	mov word [rbp - 312], 10
__L48__:
	mov ax, word [rbp - 310]
	cmp ax, 14
	jg __LL156__
	mov byte [rbp - 313], 1
	jmp __LL157__
__LL156__:
	mov byte [rbp - 313], 0
__LL157__:
	mov al, byte [rbp - 313]
	cmp al, 1
	jz __L49__
	mov al, byte [rbp - 313]
	cmp al, 0
	jz __L50__
__L49__:
	mov ax, word [rbp - 312]
	cmp ax, 10
	jge __LL158__
	mov byte [rbp - 314], 1
	jmp __LL159__
__LL158__:
	mov byte [rbp - 314], 0
__LL159__:
	mov al, byte [rbp - 314]
	cmp al, 0
	jz __L51__
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
__L51__:
	mov ax, word [rbp - 312]
	cmp ax, 14
	jle __LL160__
	mov byte [rbp - 314], 1
	jmp __LL161__
__LL160__:
	mov byte [rbp - 314], 0
__LL161__:
	mov al, byte [rbp - 314]
	cmp al, 0
	jz __L52__
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
__L52__:
	mov ax, word [rbp - 312]
	sub ax, 10
	mov word [rbp - 316], ax
	mov ax, word [rbp - 316]
	imul ax, 2
	mov word [rbp - 318], ax
	mov rax, qword [rbp - 8]
	mov bx, word [rbp - 318]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 326], rax
	mov rbx, qword [rbp - 326]
	mov ax, word [rbx]
	mov word [rbp - 328], ax
	mov ax, word [rbp - 310]
	cmp ax, 10
	jge __LL162__
	mov byte [rbp - 329], 1
	jmp __LL163__
__LL162__:
	mov byte [rbp - 329], 0
__LL163__:
	mov al, byte [rbp - 329]
	cmp al, 0
	jz __L53__
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
__L53__:
	mov ax, word [rbp - 310]
	cmp ax, 14
	jle __LL164__
	mov byte [rbp - 329], 1
	jmp __LL165__
__LL164__:
	mov byte [rbp - 329], 0
__LL165__:
	mov al, byte [rbp - 329]
	cmp al, 0
	jz __L54__
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
__L54__:
	mov ax, word [rbp - 310]
	sub ax, 10
	mov word [rbp - 331], ax
	mov ax, word [rbp - 331]
	imul ax, 2
	mov word [rbp - 333], ax
	mov rax, rbp
	sub rax, 82
	xor rbx, rbx
	mov bx, word [rbp - 333]
	add rax, rbx
	mov qword [rbp - 341], rax
	mov rbx, qword [rbp - 341]
	mov ax, word [rbp - 328]
	mov word [rbx], ax
	mov ax, word [rbp - 310]
	add ax, 1
	mov word [rbp - 343], ax
	mov ax, word [rbp - 343]
	mov word [rbp - 310], ax
	mov ax, word [rbp - 312]
	add ax, 1
	mov word [rbp - 343], ax
	mov ax, word [rbp - 343]
	mov word [rbp - 312], ax
	jmp __L48__
__L50__:
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
	mov word [rbp - 345], 10
__L55__:
	mov ax, word [rbp - 345]
	cmp ax, 14
	jg __LL166__
	mov byte [rbp - 346], 1
	jmp __LL167__
__LL166__:
	mov byte [rbp - 346], 0
__LL167__:
	mov al, byte [rbp - 346]
	cmp al, 1
	jz __L56__
	mov al, byte [rbp - 346]
	cmp al, 0
	jz __L57__
__L56__:
	mov ax, word [rbp - 345]
	cmp ax, 10
	jge __LL168__
	mov byte [rbp - 347], 1
	jmp __LL169__
__LL168__:
	mov byte [rbp - 347], 0
__LL169__:
	mov al, byte [rbp - 347]
	cmp al, 0
	jz __L58__
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
__L58__:
	mov ax, word [rbp - 345]
	cmp ax, 14
	jle __LL170__
	mov byte [rbp - 347], 1
	jmp __LL171__
__LL170__:
	mov byte [rbp - 347], 0
__LL171__:
	mov al, byte [rbp - 347]
	cmp al, 0
	jz __L59__
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
__L59__:
	mov ax, word [rbp - 345]
	sub ax, 10
	mov word [rbp - 349], ax
	mov ax, word [rbp - 349]
	imul ax, 2
	mov word [rbp - 351], ax
	mov rax, rbp
	sub rax, 82
	xor rbx, rbx
	mov bx, word [rbp - 351]
	add rax, rbx
	mov qword [rbp - 359], rax
	mov rbx, qword [rbp - 359]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 345]
	add ax, 1
	mov word [rbp - 361], ax
	mov ax, word [rbp - 361]
	mov word [rbp - 345], ax
	jmp __L55__
__L57__:
	sub rsp, 16
	mov rax, '+^+各'
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
	mov word [rbp - 58], 10
__L60__:
	mov ax, word [rbp - 58]
	cmp ax, 14
	jg __LL172__
	mov byte [rbp - 362], 1
	jmp __LL173__
__LL172__:
	mov byte [rbp - 362], 0
__LL173__:
	mov al, byte [rbp - 362]
	cmp al, 1
	jz __L61__
	mov al, byte [rbp - 362]
	cmp al, 0
	jz __L62__
__L61__:
	mov ax, word [rbp - 58]
	cmp ax, 10
	jge __LL174__
	mov byte [rbp - 363], 1
	jmp __LL175__
__LL174__:
	mov byte [rbp - 363], 0
__LL175__:
	mov al, byte [rbp - 363]
	cmp al, 0
	jz __L63__
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
__L63__:
	mov ax, word [rbp - 58]
	cmp ax, 14
	jle __LL176__
	mov byte [rbp - 363], 1
	jmp __LL177__
__LL176__:
	mov byte [rbp - 363], 0
__LL177__:
	mov al, byte [rbp - 363]
	cmp al, 0
	jz __L64__
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
__L64__:
	mov ax, word [rbp - 58]
	sub ax, 10
	mov word [rbp - 365], ax
	mov ax, word [rbp - 365]
	imul ax, 2
	mov word [rbp - 367], ax
	mov rax, rbp
	sub rax, 82
	xor rbx, rbx
	mov bx, word [rbp - 367]
	add rax, rbx
	mov qword [rbp - 375], rax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rbx, qword [rbp - 375]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 58]
	cmp ax, 10
	jge __LL178__
	mov byte [rbp - 376], 1
	jmp __LL179__
__LL178__:
	mov byte [rbp - 376], 0
__LL179__:
	mov al, byte [rbp - 376]
	cmp al, 0
	jz __L65__
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
__L65__:
	mov ax, word [rbp - 58]
	cmp ax, 14
	jle __LL180__
	mov byte [rbp - 376], 1
	jmp __LL181__
__LL180__:
	mov byte [rbp - 376], 0
__LL181__:
	mov al, byte [rbp - 376]
	cmp al, 0
	jz __L66__
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
__L66__:
	mov ax, word [rbp - 58]
	sub ax, 10
	mov word [rbp - 378], ax
	mov ax, word [rbp - 378]
	imul ax, 2
	mov word [rbp - 380], ax
	mov rax, rbp
	sub rax, 82
	xor rbx, rbx
	mov bx, word [rbp - 380]
	add rax, rbx
	mov qword [rbp - 388], rax
	mov rbx, qword [rbp - 388]
	mov ax, word [rbx]
	mov word [rbp - 390], ax
	mov ax, word [rbp - 36]
	add ax, word [rbp - 390]
	mov word [rbp - 392], ax
	mov ax, word [rbp - 392]
	mov word [rbp - 36], ax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 36]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 58]
	add ax, 1
	mov word [rbp - 394], ax
	mov ax, word [rbp - 394]
	mov word [rbp - 58], ax
	jmp __L60__
__L62__:
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
	mov word [rbp - 396], 10
__L67__:
	mov ax, word [rbp - 396]
	cmp ax, 14
	jg __LL182__
	mov byte [rbp - 397], 1
	jmp __LL183__
__LL182__:
	mov byte [rbp - 397], 0
__LL183__:
	mov al, byte [rbp - 397]
	cmp al, 1
	jz __L68__
	mov al, byte [rbp - 397]
	cmp al, 0
	jz __L69__
__L68__:
	mov ax, word [rbp - 396]
	cmp ax, 10
	jge __LL184__
	mov byte [rbp - 398], 1
	jmp __LL185__
__LL184__:
	mov byte [rbp - 398], 0
__LL185__:
	mov al, byte [rbp - 398]
	cmp al, 0
	jz __L70__
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
__L70__:
	mov ax, word [rbp - 396]
	cmp ax, 14
	jle __LL186__
	mov byte [rbp - 398], 1
	jmp __LL187__
__LL186__:
	mov byte [rbp - 398], 0
__LL187__:
	mov al, byte [rbp - 398]
	cmp al, 0
	jz __L71__
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
__L71__:
	mov ax, word [rbp - 396]
	sub ax, 10
	mov word [rbp - 400], ax
	mov ax, word [rbp - 400]
	imul ax, 2
	mov word [rbp - 402], ax
	mov rax, rbp
	sub rax, 82
	xor rbx, rbx
	mov bx, word [rbp - 402]
	add rax, rbx
	mov qword [rbp - 410], rax
	mov rbx, qword [rbp - 410]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 396]
	add ax, 1
	mov word [rbp - 412], ax
	mov ax, word [rbp - 412]
	mov word [rbp - 396], ax
	jmp __L67__
__L69__:
	sub rsp, 16
	mov rax, '+^+各'
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
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 36]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov word [rbp - 414], 0
	mov ax, word [rbp - 414]
	mov word [rbp - 46], ax
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
	mov ax, word [rbp - 22]
	mov word [rbp - 416], ax
__L72__:
	mov ax, word [rbp - 416]
	cmp ax, word [rbp - 24]
	jg __LL188__
	mov byte [rbp - 417], 1
	jmp __LL189__
__LL188__:
	mov byte [rbp - 417], 0
__LL189__:
	mov al, byte [rbp - 417]
	cmp al, 1
	jz __L73__
	mov al, byte [rbp - 417]
	cmp al, 0
	jz __L74__
__L73__:
	mov ax, word [rbp - 416]
	cmp ax, word [rbp - 22]
	jge __LL190__
	mov byte [rbp - 418], 1
	jmp __LL191__
__LL190__:
	mov byte [rbp - 418], 0
__LL191__:
	mov al, byte [rbp - 418]
	cmp al, 0
	jz __L75__
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
__L75__:
	mov ax, word [rbp - 416]
	cmp ax, word [rbp - 24]
	jle __LL192__
	mov byte [rbp - 418], 1
	jmp __LL193__
__LL192__:
	mov byte [rbp - 418], 0
__LL193__:
	mov al, byte [rbp - 418]
	cmp al, 0
	jz __L76__
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
__L76__:
	mov ax, word [rbp - 416]
	sub ax, word [rbp - 22]
	mov word [rbp - 420], ax
	mov ax, word [rbp - 420]
	imul ax, 2
	mov word [rbp - 422], ax
	mov rax, qword [rbp - 20]
	mov bx, word [rbp - 422]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 430], rax
	mov rbx, qword [rbp - 430]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 416]
	add ax, 1
	mov word [rbp - 432], ax
	mov ax, word [rbp - 432]
	mov word [rbp - 416], ax
	jmp __L72__
__L74__:
	sub rsp, 16
	mov rax, '+^+各'
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
	mov word [rbp - 92], 1
__L77__:
	mov ax, word [rbp - 92]
	cmp ax, 4
	jg __LL194__
	mov byte [rbp - 433], 1
	jmp __LL195__
__LL194__:
	mov byte [rbp - 433], 0
__LL195__:
	mov al, byte [rbp - 433]
	cmp al, 1
	jz __L78__
	mov al, byte [rbp - 433]
	cmp al, 0
	jz __L79__
__L78__:
	mov rsi, message_ip_integer
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 94], ax
	mov ax, word [rbp - 94]
	cmp ax, word [rbp - 22]
	jge __LL196__
	mov byte [rbp - 434], 1
	jmp __LL197__
__LL196__:
	mov byte [rbp - 434], 0
__LL197__:
	mov al, byte [rbp - 434]
	cmp al, 0
	jz __L80__
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
__L80__:
	mov ax, word [rbp - 94]
	cmp ax, word [rbp - 24]
	jle __LL198__
	mov byte [rbp - 434], 1
	jmp __LL199__
__LL198__:
	mov byte [rbp - 434], 0
__LL199__:
	mov al, byte [rbp - 434]
	cmp al, 0
	jz __L81__
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
__L81__:
	mov ax, word [rbp - 94]
	sub ax, word [rbp - 22]
	mov word [rbp - 436], ax
	mov ax, word [rbp - 436]
	imul ax, 2
	mov word [rbp - 438], ax
	mov rax, qword [rbp - 20]
	mov bx, word [rbp - 438]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 446], rax
	mov rbx, qword [rbp - 446]
	mov ax, word [rbx]
	mov word [rbp - 448], ax
	mov ax, word [rbp - 46]
	add ax, word [rbp - 448]
	mov word [rbp - 450], ax
	mov ax, word [rbp - 450]
	mov word [rbp - 46], ax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 46]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 92]
	add ax, 1
	mov word [rbp - 452], ax
	mov ax, word [rbp - 452]
	mov word [rbp - 92], ax
	jmp __L77__
__L79__:
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 46]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov rbx, rbp
	sub rbx, 26
	mov ax, word [rbx]
	sub rbx, 8
	mov rbx, qword [rbx]
	mov word [rbx], ax
	mov rbx, rbp
	sub rbx, 36
	mov ax, word [rbx]
	sub rbx, 8
	mov rbx, qword [rbx]
	mov word [rbx], ax
	mov rbx, rbp
	sub rbx, 46
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
	sub rsp, 80
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
	mov word [rbp - 32], ax
	mov ax, word [rbp - 4]
	mov word [rbp - 34], ax
	mov ax, word [rbp - 4]
	sub ax, word [rbp - 2]
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
	mov qword [rbp - 28], rsp
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
	mov ax, 14
	sub ax, 10
	mov word [rbp - 36], ax
	mov ax, word [rbp - 36]
	add ax, 1
	mov word [rbp - 36], ax
	mov rax, 0
	mov ax, word [rbp - 36]
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
	sub rsp, 16
	mov rax, '10'
	mov qword [rsp], rax
	add rsp, 2
	mov byte [rsp], 0
	sub rsp, 2
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
	mov rax, '14'
	mov qword [rsp], rax
	add rsp, 2
	mov byte [rsp], 0
	sub rsp, 2
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
	mov word [rbp - 36], 10
__L82__:
	mov ax, word [rbp - 36]
	cmp ax, 14
	jg __LL200__
	mov byte [rbp - 37], 1
	jmp __LL201__
__LL200__:
	mov byte [rbp - 37], 0
__LL201__:
	mov al, byte [rbp - 37]
	cmp al, 1
	jz __L83__
	mov al, byte [rbp - 37]
	cmp al, 0
	jz __L84__
__L83__:
	mov ax, word [rbp - 36]
	cmp ax, 10
	jge __LL202__
	mov byte [rbp - 38], 1
	jmp __LL203__
__LL202__:
	mov byte [rbp - 38], 0
__LL203__:
	mov al, byte [rbp - 38]
	cmp al, 0
	jz __L85__
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
__L85__:
	mov ax, word [rbp - 36]
	cmp ax, 14
	jle __LL204__
	mov byte [rbp - 38], 1
	jmp __LL205__
__LL204__:
	mov byte [rbp - 38], 0
__LL205__:
	mov al, byte [rbp - 38]
	cmp al, 0
	jz __L86__
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
__L86__:
	mov ax, word [rbp - 36]
	sub ax, 10
	mov word [rbp - 40], ax
	mov ax, word [rbp - 40]
	imul ax, 2
	mov word [rbp - 42], ax
	mov rax, rbp
	sub rax, 20
	xor rbx, rbx
	mov bx, word [rbp - 42]
	add rax, rbx
	mov qword [rbp - 50], rax
	mov rbx, qword [rbp - 50]
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbx], ax
	mov ax, word [rbp - 36]
	add ax, 1
	mov word [rbp - 52], ax
	mov ax, word [rbp - 52]
	mov word [rbp - 36], ax
	jmp __L82__
__L84__:
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
	mov ax, word [rbp - 34]
	sub ax, word [rbp - 32]
	mov word [rbp - 54], ax
	mov ax, word [rbp - 54]
	add ax, 1
	mov word [rbp - 54], ax
	mov rax, 0
	mov ax, word [rbp - 54]
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
	mov ax, word [rbp - 32]
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
	mov rax, 0
	mov ax, word [rbp - 34]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov rax, message_lb
	mov rdi, fmt_string_no_line_break
	mov rsi, rax
	xor rax, rax
	call printf
	mov ax, word [rbp - 32]
	mov word [rbp - 54], ax
__L87__:
	mov ax, word [rbp - 54]
	cmp ax, word [rbp - 34]
	jg __LL206__
	mov byte [rbp - 55], 1
	jmp __LL207__
__LL206__:
	mov byte [rbp - 55], 0
__LL207__:
	mov al, byte [rbp - 55]
	cmp al, 1
	jz __L88__
	mov al, byte [rbp - 55]
	cmp al, 0
	jz __L89__
__L88__:
	mov ax, word [rbp - 54]
	cmp ax, word [rbp - 32]
	jge __LL208__
	mov byte [rbp - 56], 1
	jmp __LL209__
__LL208__:
	mov byte [rbp - 56], 0
__LL209__:
	mov al, byte [rbp - 56]
	cmp al, 0
	jz __L90__
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
__L90__:
	mov ax, word [rbp - 54]
	cmp ax, word [rbp - 34]
	jle __LL210__
	mov byte [rbp - 56], 1
	jmp __LL211__
__LL210__:
	mov byte [rbp - 56], 0
__LL211__:
	mov al, byte [rbp - 56]
	cmp al, 0
	jz __L91__
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
__L91__:
	mov ax, word [rbp - 54]
	sub ax, word [rbp - 32]
	mov word [rbp - 58], ax
	mov ax, word [rbp - 58]
	imul ax, 2
	mov word [rbp - 60], ax
	mov rax, qword [rbp - 28]
	mov bx, word [rbp - 60]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 68], rax
	mov rbx, qword [rbp - 68]
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbx], ax
	mov ax, word [rbp - 54]
	add ax, 1
	mov word [rbp - 70], ax
	mov ax, word [rbp - 70]
	mov word [rbp - 54], ax
	jmp __L87__
__L89__:
	mov rax, rsp
	sub rax, 24
	mov rbx, rbp
	sub rbx, 20
	mov qword [rax], rbx
	mov rax, rsp
	sub rax, 26
	mov bx, 10
	mov word [rax], bx
	mov rax, rsp
	sub rax, 28
	mov bx, 14
	mov word [rax], bx
	mov rax, rsp
	sub rax, 36
	mov rbx, qword [rbp - 28]
	mov qword [rax], rbx
	mov rax, rsp
	sub rax, 38
	mov bx, word [rbp - 32]
	mov word [rax], bx
	mov rax, rsp
	sub rax, 40
	mov bx, word [rbp - 34]
	mov word [rax], bx
	mov rax, rsp
	sub rax, 50
	mov rbx, rbp
	sub rbx, 6
	mov qword [rax], rbx
	mov rax, rsp
	sub rax, 60
	mov rbx, rbp
	sub rbx, 8
	mov qword [rax], rbx
	mov rax, rsp
	sub rax, 70
	mov rbx, rbp
	sub rbx, 10
	mov qword [rax], rbx
	call array_parameter_demo
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
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 8]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 10]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf

;exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
