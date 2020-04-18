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

main:
	push rbp
	mov rbp, rsp
	sub rsp, 208
	mov rsi, message_ip_integer
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 16], ax
	mov rsi, message_ip_integer
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 18], ax
	mov ax, word [rbp - 16]
	mov word [rbp - 46], ax
	mov ax, word [rbp - 18]
	mov word [rbp - 48], ax
	mov ax, word [rbp - 18]
	sub ax, word [rbp - 16]
	mov word [rbp - 44], ax
	mov ax, word [rbp - 44]
	add ax, 1
	mov word [rbp - 44], ax
	mov ax, word [rbp - 44]
	imul ax, 2
	mov word [rbp - 44], ax
	xor dx, dx
	mov ax, word [rbp - 44]
	mov cx, 16
	idiv cx
	mov word [rbp - 44], ax
	mov ax, word [rbp - 44]
	add ax, 1
	mov word [rbp - 44], ax
	mov ax, word [rbp - 44]
	imul ax, 16
	mov word [rbp - 44], ax
	mov ax, word [rbp - 44]
	movsx rax, ax
	sub rsp, rax
	mov qword [rbp - 26], rsp
	mov ax, word [rbp - 16]
	mov word [rbp - 52], ax
	mov ax, word [rbp - 18]
	mov word [rbp - 54], ax
	mov ax, word [rbp - 18]
	sub ax, word [rbp - 16]
	mov word [rbp - 50], ax
	mov ax, word [rbp - 50]
	add ax, 1
	mov word [rbp - 50], ax
	mov ax, word [rbp - 50]
	imul ax, 2
	mov word [rbp - 50], ax
	xor dx, dx
	mov ax, word [rbp - 50]
	mov cx, 16
	idiv cx
	mov word [rbp - 50], ax
	mov ax, word [rbp - 50]
	add ax, 1
	mov word [rbp - 50], ax
	mov ax, word [rbp - 50]
	imul ax, 16
	mov word [rbp - 50], ax
	mov ax, word [rbp - 50]
	movsx rax, ax
	sub rsp, rax
	mov qword [rbp - 34], rsp
	mov ax, word [rbp - 16]
	mov word [rbp - 58], ax
	mov ax, word [rbp - 18]
	mov word [rbp - 60], ax
	mov ax, word [rbp - 18]
	sub ax, word [rbp - 16]
	mov word [rbp - 56], ax
	mov ax, word [rbp - 56]
	add ax, 1
	mov word [rbp - 56], ax
	mov ax, word [rbp - 56]
	imul ax, 2
	mov word [rbp - 56], ax
	xor dx, dx
	mov ax, word [rbp - 56]
	mov cx, 16
	idiv cx
	mov word [rbp - 56], ax
	mov ax, word [rbp - 56]
	add ax, 1
	mov word [rbp - 56], ax
	mov ax, word [rbp - 56]
	imul ax, 16
	mov word [rbp - 56], ax
	mov ax, word [rbp - 56]
	movsx rax, ax
	sub rsp, rax
	mov qword [rbp - 42], rsp
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
	mov ax, word [rbp - 48]
	sub ax, word [rbp - 46]
	mov word [rbp - 62], ax
	mov ax, word [rbp - 62]
	add ax, 1
	mov word [rbp - 62], ax
	mov rax, 0
	mov ax, word [rbp - 62]
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
	mov ax, word [rbp - 46]
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
	mov ax, word [rbp - 48]
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
	mov ax, word [rbp - 46]
	mov word [rbp - 62], ax
__L0__:
	mov ax, word [rbp - 62]
	cmp ax, word [rbp - 48]
	jg __LL25__
	mov byte [rbp - 63], 1
	jmp __LL26__
__LL25__:
	mov byte [rbp - 63], 0
__LL26__:
	mov al, byte [rbp - 63]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp - 63]
	cmp al, 0
	jz __L2__
__L1__:
	mov ax, word [rbp - 62]
	cmp ax, word [rbp - 46]
	jge __LL27__
	mov byte [rbp - 64], 1
	jmp __LL28__
__LL27__:
	mov byte [rbp - 64], 0
__LL28__:
	mov al, byte [rbp - 64]
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
	mov ax, word [rbp - 62]
	cmp ax, word [rbp - 48]
	jle __LL29__
	mov byte [rbp - 64], 1
	jmp __LL30__
__LL29__:
	mov byte [rbp - 64], 0
__LL30__:
	mov al, byte [rbp - 64]
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
	mov ax, word [rbp - 62]
	sub ax, word [rbp - 46]
	mov word [rbp - 66], ax
	mov ax, word [rbp - 66]
	imul ax, 2
	mov word [rbp - 68], ax
	mov rax, qword [rbp - 26]
	mov bx, word [rbp - 68]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 76], rax
	mov rbx, qword [rbp - 76]
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
	mov ax, word [rbp - 62]
	add ax, 1
	mov word [rbp - 78], ax
	mov ax, word [rbp - 78]
	mov word [rbp - 62], ax
	jmp __L0__
__L2__:
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
	mov ax, word [rbp - 54]
	sub ax, word [rbp - 52]
	mov word [rbp - 80], ax
	mov ax, word [rbp - 80]
	add ax, 1
	mov word [rbp - 80], ax
	mov rax, 0
	mov ax, word [rbp - 80]
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
	mov ax, word [rbp - 52]
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
	mov ax, word [rbp - 54]
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
	mov ax, word [rbp - 52]
	mov word [rbp - 80], ax
__L5__:
	mov ax, word [rbp - 80]
	cmp ax, word [rbp - 54]
	jg __LL31__
	mov byte [rbp - 81], 1
	jmp __LL32__
__LL31__:
	mov byte [rbp - 81], 0
__LL32__:
	mov al, byte [rbp - 81]
	cmp al, 1
	jz __L6__
	mov al, byte [rbp - 81]
	cmp al, 0
	jz __L7__
__L6__:
	mov ax, word [rbp - 80]
	cmp ax, word [rbp - 52]
	jge __LL33__
	mov byte [rbp - 82], 1
	jmp __LL34__
__LL33__:
	mov byte [rbp - 82], 0
__LL34__:
	mov al, byte [rbp - 82]
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
	mov ax, word [rbp - 80]
	cmp ax, word [rbp - 54]
	jle __LL35__
	mov byte [rbp - 82], 1
	jmp __LL36__
__LL35__:
	mov byte [rbp - 82], 0
__LL36__:
	mov al, byte [rbp - 82]
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
	mov ax, word [rbp - 80]
	sub ax, word [rbp - 52]
	mov word [rbp - 84], ax
	mov ax, word [rbp - 84]
	imul ax, 2
	mov word [rbp - 86], ax
	mov rax, qword [rbp - 34]
	mov bx, word [rbp - 86]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 94], rax
	mov rbx, qword [rbp - 94]
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
	mov ax, word [rbp - 80]
	add ax, 1
	mov word [rbp - 96], ax
	mov ax, word [rbp - 96]
	mov word [rbp - 80], ax
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
	mov word [rbp - 98], 7
	mov ax, word [rbp - 98]
	mov word [rbp - 6], ax
	mov word [rbp - 8], 1
__L10__:
	mov ax, word [rbp - 8]
	cmp ax, 3
	jg __LL37__
	mov byte [rbp - 99], 1
	jmp __LL38__
__LL37__:
	mov byte [rbp - 99], 0
__LL38__:
	mov al, byte [rbp - 99]
	cmp al, 1
	jz __L11__
	mov al, byte [rbp - 99]
	cmp al, 0
	jz __L12__
__L11__:
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
	cmp ax, word [rbp - 46]
	jge __LL39__
	mov byte [rbp - 100], 1
	jmp __LL40__
__LL39__:
	mov byte [rbp - 100], 0
__LL40__:
	mov al, byte [rbp - 100]
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
	mov ax, word [rbp - 2]
	cmp ax, word [rbp - 48]
	jle __LL41__
	mov byte [rbp - 100], 1
	jmp __LL42__
__LL41__:
	mov byte [rbp - 100], 0
__LL42__:
	mov al, byte [rbp - 100]
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
	mov ax, word [rbp - 2]
	sub ax, word [rbp - 46]
	mov word [rbp - 102], ax
	mov ax, word [rbp - 102]
	imul ax, 2
	mov word [rbp - 104], ax
	mov rax, qword [rbp - 26]
	mov bx, word [rbp - 104]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 112], rax
	mov rbx, qword [rbp - 112]
	mov ax, word [rbx]
	mov word [rbp - 114], ax
	mov ax, word [rbp - 4]
	cmp ax, word [rbp - 52]
	jge __LL43__
	mov byte [rbp - 115], 1
	jmp __LL44__
__LL43__:
	mov byte [rbp - 115], 0
__LL44__:
	mov al, byte [rbp - 115]
	cmp al, 0
	jz __L15__
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
__L15__:
	mov ax, word [rbp - 4]
	cmp ax, word [rbp - 54]
	jle __LL45__
	mov byte [rbp - 115], 1
	jmp __LL46__
__LL45__:
	mov byte [rbp - 115], 0
__LL46__:
	mov al, byte [rbp - 115]
	cmp al, 0
	jz __L16__
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
__L16__:
	mov ax, word [rbp - 4]
	sub ax, word [rbp - 52]
	mov word [rbp - 117], ax
	mov ax, word [rbp - 117]
	imul ax, 2
	mov word [rbp - 119], ax
	mov rax, qword [rbp - 34]
	mov bx, word [rbp - 119]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 127], rax
	mov rbx, qword [rbp - 127]
	mov ax, word [rbx]
	mov word [rbp - 129], ax
	mov ax, word [rbp - 114]
	add ax, word [rbp - 129]
	mov word [rbp - 131], ax
	mov ax, word [rbp - 131]
	mov word [rbp - 10], ax
	mov ax, word [rbp - 6]
	cmp ax, word [rbp - 46]
	jge __LL47__
	mov byte [rbp - 132], 1
	jmp __LL48__
__LL47__:
	mov byte [rbp - 132], 0
__LL48__:
	mov al, byte [rbp - 132]
	cmp al, 0
	jz __L17__
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
__L17__:
	mov ax, word [rbp - 6]
	cmp ax, word [rbp - 48]
	jle __LL49__
	mov byte [rbp - 132], 1
	jmp __LL50__
__LL49__:
	mov byte [rbp - 132], 0
__LL50__:
	mov al, byte [rbp - 132]
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
	mov ax, word [rbp - 6]
	sub ax, word [rbp - 46]
	mov word [rbp - 134], ax
	mov ax, word [rbp - 134]
	imul ax, 2
	mov word [rbp - 136], ax
	mov rax, qword [rbp - 26]
	mov bx, word [rbp - 136]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 144], rax
	mov rbx, qword [rbp - 144]
	mov ax, word [rbx]
	mov word [rbp - 146], ax
	mov ax, word [rbp - 4]
	cmp ax, word [rbp - 52]
	jge __LL51__
	mov byte [rbp - 147], 1
	jmp __LL52__
__LL51__:
	mov byte [rbp - 147], 0
__LL52__:
	mov al, byte [rbp - 147]
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
	mov ax, word [rbp - 4]
	cmp ax, word [rbp - 54]
	jle __LL53__
	mov byte [rbp - 147], 1
	jmp __LL54__
__LL53__:
	mov byte [rbp - 147], 0
__LL54__:
	mov al, byte [rbp - 147]
	cmp al, 0
	jz __L20__
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
__L20__:
	mov ax, word [rbp - 4]
	sub ax, word [rbp - 52]
	mov word [rbp - 149], ax
	mov ax, word [rbp - 149]
	imul ax, 2
	mov word [rbp - 151], ax
	mov rax, qword [rbp - 34]
	mov bx, word [rbp - 151]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 159], rax
	mov rbx, qword [rbp - 159]
	mov ax, word [rbx]
	mov word [rbp - 161], ax
	mov ax, word [rbp - 146]
	add ax, word [rbp - 161]
	mov word [rbp - 163], ax
	mov ax, word [rbp - 163]
	mov word [rbp - 12], ax
	mov ax, word [rbp - 2]
	cmp ax, word [rbp - 46]
	jge __LL55__
	mov byte [rbp - 164], 1
	jmp __LL56__
__LL55__:
	mov byte [rbp - 164], 0
__LL56__:
	mov al, byte [rbp - 164]
	cmp al, 0
	jz __L21__
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
__L21__:
	mov ax, word [rbp - 2]
	cmp ax, word [rbp - 48]
	jle __LL57__
	mov byte [rbp - 164], 1
	jmp __LL58__
__LL57__:
	mov byte [rbp - 164], 0
__LL58__:
	mov al, byte [rbp - 164]
	cmp al, 0
	jz __L22__
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
__L22__:
	mov ax, word [rbp - 2]
	sub ax, word [rbp - 46]
	mov word [rbp - 166], ax
	mov ax, word [rbp - 166]
	imul ax, 2
	mov word [rbp - 168], ax
	mov rax, qword [rbp - 26]
	mov bx, word [rbp - 168]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 176], rax
	mov rbx, qword [rbp - 176]
	mov ax, word [rbx]
	mov word [rbp - 178], ax
	mov ax, word [rbp - 6]
	cmp ax, word [rbp - 52]
	jge __LL59__
	mov byte [rbp - 179], 1
	jmp __LL60__
__LL59__:
	mov byte [rbp - 179], 0
__LL60__:
	mov al, byte [rbp - 179]
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
	mov ax, word [rbp - 6]
	cmp ax, word [rbp - 54]
	jle __LL61__
	mov byte [rbp - 179], 1
	jmp __LL62__
__LL61__:
	mov byte [rbp - 179], 0
__LL62__:
	mov al, byte [rbp - 179]
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
	mov ax, word [rbp - 6]
	sub ax, word [rbp - 52]
	mov word [rbp - 181], ax
	mov ax, word [rbp - 181]
	imul ax, 2
	mov word [rbp - 183], ax
	mov rax, qword [rbp - 34]
	mov bx, word [rbp - 183]
	movsx rbx, bx
	add rax, rbx
	mov qword [rbp - 191], rax
	mov rbx, qword [rbp - 191]
	mov ax, word [rbx]
	mov word [rbp - 193], ax
	mov ax, word [rbp - 178]
	add ax, word [rbp - 193]
	mov word [rbp - 195], ax
	mov ax, word [rbp - 195]
	mov word [rbp - 14], ax
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
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 12]
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
	mov ax, word [rbp - 14]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 8]
	add ax, 1
	mov word [rbp - 197], ax
	mov ax, word [rbp - 197]
	mov word [rbp - 8], ax
	jmp __L10__
__L12__:

;exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
