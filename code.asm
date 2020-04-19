extern printf, scanf

section .data
	fmt_integer: db '%d', 10, 0
	fmt_integer_no_line_break: db '%d ', 0
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
	sub rsp, 192
	mov byte [rbp - 33], 1
	mov al, byte [rbp - 33]
	mov byte [rbp - 15], al
	mov word [rbp - 35], 5
	mov ax, word [rbp - 35]
	mov word [rbp - 10], ax
	mov word [rbp - 37], 9
	mov ax, word [rbp - 37]
	mov word [rbp - 12], ax
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
	mov ax, word [rbp - 4]
	imul ax, word [rbp - 12]
	mov word [rbp - 39], ax
	mov ax, word [rbp - 2]
	add ax, word [rbp - 39]
	mov word [rbp - 41], ax
	mov ax, word [rbp - 10]
	sub ax, word [rbp - 12]
	mov word [rbp - 43], ax
	mov ax, word [rbp - 43]
	imul ax, word [rbp - 4]
	mov word [rbp - 45], ax
	mov ax, word [rbp - 41]
	add ax, word [rbp - 45]
	mov word [rbp - 47], ax
	mov ax, word [rbp - 10]
	imul ax, 2
	mov word [rbp - 49], ax
	mov ax, word [rbp - 47]
	add ax, word [rbp - 49]
	mov word [rbp - 51], ax
	mov ax, word [rbp - 12]
	imul ax, word [rbp - 2]
	mov word [rbp - 53], ax
	mov ax, word [rbp - 51]
	sub ax, word [rbp - 53]
	mov word [rbp - 55], ax
	mov ax, word [rbp - 55]
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
	mov word [rbp - 8], 10
__L0__:
	mov ax, word [rbp - 8]
	cmp ax, 15
	jg __LL19__
	mov byte [rbp - 56], 1
	jmp __LL20__
__LL19__:
	mov byte [rbp - 56], 0
__LL20__:
	mov al, byte [rbp - 56]
	cmp al, 1
	jz __L1__
	mov al, byte [rbp - 56]
	cmp al, 0
	jz __L2__
__L1__:
	mov word [rbp - 58], 7
	mov ax, word [rbp - 58]
	mov word [rbp - 30], ax
	mov rsi, message_ip_integer
	mov rdi, fmt_string
	xor rax, rax
	call printf
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbp - 32], ax
	mov ax, word [rbp - 30]
	add ax, word [rbp - 32]
	mov word [rbp - 60], ax
	mov ax, word [rbp - 60]
	mov word [rbp - 30], ax
	mov rsi, message_output
	mov rdi, fmt_string_no_line_break
	xor rax, rax
	call printf
	mov rax, 0
	mov ax, word [rbp - 30]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 6]
	add ax, word [rbp - 8]
	mov word [rbp - 62], ax
	mov ax, word [rbp - 30]
	imul ax, 2
	mov word [rbp - 64], ax
	mov ax, word [rbp - 62]
	add ax, word [rbp - 64]
	mov word [rbp - 66], ax
	mov ax, word [rbp - 66]
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
	mov ax, word [rbp - 8]
	add ax, 1
	mov word [rbp - 68], ax
	mov ax, word [rbp - 68]
	mov word [rbp - 8], ax
	jmp __L0__
__L2__:
	mov ax, word [rbp - 4]
	imul ax, word [rbp - 12]
	mov word [rbp - 70], ax
	mov ax, word [rbp - 2]
	add ax, word [rbp - 70]
	mov word [rbp - 72], ax
	mov ax, word [rbp - 10]
	sub ax, word [rbp - 12]
	mov word [rbp - 74], ax
	mov ax, word [rbp - 74]
	imul ax, word [rbp - 4]
	mov word [rbp - 76], ax
	mov ax, word [rbp - 72]
	add ax, word [rbp - 76]
	mov word [rbp - 78], ax
	mov ax, word [rbp - 10]
	imul ax, 2
	mov word [rbp - 80], ax
	mov ax, word [rbp - 78]
	add ax, word [rbp - 80]
	mov word [rbp - 82], ax
	mov ax, word [rbp - 12]
	imul ax, word [rbp - 2]
	mov word [rbp - 84], ax
	mov ax, word [rbp - 82]
	sub ax, word [rbp - 84]
	mov word [rbp - 86], ax
	mov ax, word [rbp - 86]
	mov word [rbp - 6], ax
	mov ax, word [rbp - 6]
	cmp ax, 10
	jle __LL21__
	mov byte [rbp - 87], 1
	jmp __LL22__
__LL21__:
	mov byte [rbp - 87], 0
__LL22__:
	mov ax, word [rbp - 10]
	cmp ax, word [rbp - 12]
	jg __LL23__
	mov byte [rbp - 88], 1
	jmp __LL24__
__LL23__:
	mov byte [rbp - 88], 0
__LL24__:
	mov al, byte [rbp - 87]
	or al, byte [rbp - 88]
	mov byte [rbp - 89], al
	mov ax, word [rbp - 2]
	cmp ax, word [rbp - 4]
	jge __LL25__
	mov byte [rbp - 90], 1
	jmp __LL26__
__LL25__:
	mov byte [rbp - 90], 0
__LL26__:
	mov al, byte [rbp - 89]
	and al, byte [rbp - 90]
	mov byte [rbp - 91], al
	mov al, byte [rbp - 91]
	and al, byte [rbp - 15]
	mov byte [rbp - 92], al
	mov al, byte [rbp - 92]
	mov byte [rbp - 16], al
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
	cmp byte [rbp - 15], 1
	jz __LL27__
	mov rax, message_false
	jmp __LL28__
__LL27__:
	mov rax, message_true
__LL28__:
	mov rdi, fmt_string
	mov rsi, rax
	xor rax, rax
	call printf
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
	mov ax, 15
	sub ax, 10
	mov word [rbp - 94], ax
	mov ax, word [rbp - 94]
	add ax, 1
	mov word [rbp - 94], ax
	mov rax, 0
	mov ax, word [rbp - 94]
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
	mov rax, '15'
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
	mov word [rbp - 94], 10
__L3__:
	mov ax, word [rbp - 94]
	cmp ax, 15
	jg __LL29__
	mov byte [rbp - 95], 1
	jmp __LL30__
__LL29__:
	mov byte [rbp - 95], 0
__LL30__:
	mov al, byte [rbp - 95]
	cmp al, 1
	jz __L4__
	mov al, byte [rbp - 95]
	cmp al, 0
	jz __L5__
__L4__:
	mov ax, word [rbp - 94]
	cmp ax, 10
	jge __LL31__
	mov byte [rbp - 96], 1
	jmp __LL32__
__LL31__:
	mov byte [rbp - 96], 0
__LL32__:
	mov al, byte [rbp - 96]
	cmp al, 0
	jz __L6__
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
__L6__:
	mov ax, word [rbp - 94]
	cmp ax, 15
	jle __LL33__
	mov byte [rbp - 96], 1
	jmp __LL34__
__LL33__:
	mov byte [rbp - 96], 0
__LL34__:
	mov al, byte [rbp - 96]
	cmp al, 0
	jz __L7__
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
__L7__:
	mov ax, word [rbp - 94]
	sub ax, 10
	mov word [rbp - 98], ax
	mov ax, word [rbp - 98]
	imul ax, 2
	mov word [rbp - 100], ax
	mov rax, rbp
	sub rax, 28
	xor rbx, rbx
	mov bx, word [rbp - 100]
	add rax, rbx
	mov qword [rbp - 108], rax
	mov rbx, qword [rbp - 108]
	mov rsi, buffer_integer
	mov rdi, fmt_ip_integer
	mov al, 0
	call scanf
	mov eax, [buffer_integer]
	mov word [rbx], ax
	mov ax, word [rbp - 94]
	add ax, 1
	mov word [rbp - 110], ax
	mov ax, word [rbp - 110]
	mov word [rbp - 94], ax
	jmp __L3__
__L5__:
	mov ax, word [rbp - 10]
	add ax, word [rbp - 2]
	mov word [rbp - 112], ax
	mov ax, 13
	cmp ax, 10
	jge __LL35__
	mov byte [rbp - 113], 1
	jmp __LL36__
__LL35__:
	mov byte [rbp - 113], 0
__LL36__:
	mov al, byte [rbp - 113]
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
	mov ax, 13
	cmp ax, 15
	jle __LL37__
	mov byte [rbp - 113], 1
	jmp __LL38__
__LL37__:
	mov byte [rbp - 113], 0
__LL38__:
	mov al, byte [rbp - 113]
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
	mov ax, 13
	sub ax, 10
	mov word [rbp - 115], ax
	mov ax, word [rbp - 115]
	imul ax, 2
	mov word [rbp - 117], ax
	mov rax, rbp
	sub rax, 28
	xor rbx, rbx
	mov bx, word [rbp - 117]
	add rax, rbx
	mov qword [rbp - 125], rax
	mov rbx, qword [rbp - 125]
	mov ax, word [rbx]
	mov word [rbp - 127], ax
	mov ax, word [rbp - 127]
	imul ax, 2
	mov word [rbp - 129], ax
	mov ax, word [rbp - 112]
	add ax, word [rbp - 129]
	mov word [rbp - 131], ax
	mov ax, 14
	cmp ax, 10
	jge __LL39__
	mov byte [rbp - 132], 1
	jmp __LL40__
__LL39__:
	mov byte [rbp - 132], 0
__LL40__:
	mov al, byte [rbp - 132]
	cmp al, 0
	jz __L10__
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
__L10__:
	mov ax, 14
	cmp ax, 15
	jle __LL41__
	mov byte [rbp - 132], 1
	jmp __LL42__
__LL41__:
	mov byte [rbp - 132], 0
__LL42__:
	mov al, byte [rbp - 132]
	cmp al, 0
	jz __L11__
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
__L11__:
	mov ax, 14
	sub ax, 10
	mov word [rbp - 134], ax
	mov ax, word [rbp - 134]
	imul ax, 2
	mov word [rbp - 136], ax
	mov rax, rbp
	sub rax, 28
	xor rbx, rbx
	mov bx, word [rbp - 136]
	add rax, rbx
	mov qword [rbp - 144], rax
	mov rbx, qword [rbp - 144]
	mov ax, word [rbx]
	mov word [rbp - 146], ax
	mov ax, word [rbp - 146]
	imul ax, 3
	mov word [rbp - 148], ax
	mov ax, word [rbp - 131]
	add ax, word [rbp - 148]
	mov word [rbp - 150], ax
	mov ax, 15
	cmp ax, 10
	jge __LL43__
	mov byte [rbp - 151], 1
	jmp __LL44__
__LL43__:
	mov byte [rbp - 151], 0
__LL44__:
	mov al, byte [rbp - 151]
	cmp al, 0
	jz __L12__
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
__L12__:
	mov ax, 15
	cmp ax, 15
	jle __LL45__
	mov byte [rbp - 151], 1
	jmp __LL46__
__LL45__:
	mov byte [rbp - 151], 0
__LL46__:
	mov al, byte [rbp - 151]
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
	mov ax, 15
	sub ax, 10
	mov word [rbp - 153], ax
	mov ax, word [rbp - 153]
	imul ax, 2
	mov word [rbp - 155], ax
	mov rax, rbp
	sub rax, 28
	xor rbx, rbx
	mov bx, word [rbp - 155]
	add rax, rbx
	mov qword [rbp - 163], rax
	mov rbx, qword [rbp - 163]
	mov ax, word [rbx]
	mov word [rbp - 165], ax
	mov ax, word [rbp - 150]
	add ax, word [rbp - 165]
	mov word [rbp - 167], ax
	mov ax, word [rbp - 167]
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
	mov word [rbp - 169], 10
__L14__:
	mov ax, word [rbp - 169]
	cmp ax, 15
	jg __LL47__
	mov byte [rbp - 170], 1
	jmp __LL48__
__LL47__:
	mov byte [rbp - 170], 0
__LL48__:
	mov al, byte [rbp - 170]
	cmp al, 1
	jz __L15__
	mov al, byte [rbp - 170]
	cmp al, 0
	jz __L16__
__L15__:
	mov ax, word [rbp - 169]
	cmp ax, 10
	jge __LL49__
	mov byte [rbp - 171], 1
	jmp __LL50__
__LL49__:
	mov byte [rbp - 171], 0
__LL50__:
	mov al, byte [rbp - 171]
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
	mov ax, word [rbp - 169]
	cmp ax, 15
	jle __LL51__
	mov byte [rbp - 171], 1
	jmp __LL52__
__LL51__:
	mov byte [rbp - 171], 0
__LL52__:
	mov al, byte [rbp - 171]
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
	mov ax, word [rbp - 169]
	sub ax, 10
	mov word [rbp - 173], ax
	mov ax, word [rbp - 173]
	imul ax, 2
	mov word [rbp - 175], ax
	mov rax, rbp
	sub rax, 28
	xor rbx, rbx
	mov bx, word [rbp - 175]
	add rax, rbx
	mov qword [rbp - 183], rax
	mov rbx, qword [rbp - 183]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer_no_line_break
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp - 169]
	add ax, 1
	mov word [rbp - 185], ax
	mov ax, word [rbp - 185]
	mov word [rbp - 169], ax
	jmp __L14__
__L16__:
	sub rsp, 16
	mov rax, 'TºÇœÓU'
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

;exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
