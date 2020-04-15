extern printf

section .data
	fmt_integer: db '%d', 10, 0
	fmt_float: db '%f', 10, 0
	fmt_string: db '%s', 10, 0
	message_true: db 'true', 0
	message_false: db 'false', 0

section .bss
	mem_main resb 140

section .text
global main

main:
	mov rbp, mem_main
	push rbp
	mov rbp, rsp
	mov ax, 1
	sub ax, 1
	mov word [rbp + 46], ax
	mov ax, word [rbp + 46]
	imul ax, 2
	mov word [rbp + 48], ax
	mov rax, rbp
	add rax, 2
	xor rbx, rbx
	mov bx, word [rbp + 48]
	add rax, rbx
	mov qword [rbp + 50], rax
	mov word [rbp + 58], 1
	mov rbx,  [rbp + 50]
	mov ax, word [rbp + 58]
	mov word [rbx], ax
	mov ax, 2
	sub ax, 1
	mov word [rbp + 60], ax
	mov ax, word [rbp + 60]
	imul ax, 2
	mov word [rbp + 62], ax
	mov rax, rbp
	add rax, 2
	xor rbx, rbx
	mov bx, word [rbp + 62]
	add rax, rbx
	mov qword [rbp + 64], rax
	mov word [rbp + 72], 1
	mov rbx,  [rbp + 64]
	mov ax, word [rbp + 72]
	mov word [rbx], ax
	mov word [rbp + 0], 3
L0:
	cmp word [rbp + 0], 25
	jg __L6__
	MOV byte [rbp + 74], 1
	JMP __L7__
__L6__:
	MOV byte [rbp + 74], 0
__L7__:		mov al, byte [rbp + 74]
	cmp al, 1
	jz L1
	mov al, byte [rbp + 74]
	cmp al, 0
	jz L2
L1:
	mov ax, word [rbp + 0]
	sub ax, 1
	mov word [rbp + 75], ax
	mov ax, word [rbp + 75]
	mov word [rbp + 42], ax
	mov ax, word [rbp + 0]
	sub ax, 2
	mov word [rbp + 77], ax
	mov ax, word [rbp + 77]
	mov word [rbp + 44], ax
	mov ax, word [rbp + 0]
	sub ax, 1
	mov word [rbp + 79], ax
	mov ax, word [rbp + 79]
	imul ax, 2
	mov word [rbp + 81], ax
	mov rax, rbp
	add rax, 2
	xor rbx, rbx
	mov bx, word [rbp + 81]
	add rax, rbx
	mov qword [rbp + 83], rax
	mov ax, word [rbp + 42]
	sub ax, 1
	mov word [rbp + 91], ax
	mov ax, word [rbp + 91]
	imul ax, 2
	mov word [rbp + 93], ax
	mov rax, rbp
	add rax, 2
	xor rbx, rbx
	mov bx, word [rbp + 93]
	add rax, rbx
	mov qword [rbp + 95], rax
	mov rbx,  [rbp + 95]
	mov ax, word [rbx]
	mov word [rbp + 103], ax
	mov ax, word [rbp + 44]
	sub ax, 1
	mov word [rbp + 105], ax
	mov ax, word [rbp + 105]
	imul ax, 2
	mov word [rbp + 107], ax
	mov rax, rbp
	add rax, 2
	xor rbx, rbx
	mov bx, word [rbp + 107]
	add rax, rbx
	mov qword [rbp + 109], rax
	mov rbx,  [rbp + 109]
	mov ax, word [rbx]
	mov word [rbp + 117], ax
	mov ax, word [rbp + 103]
	add ax, word [rbp + 117]
	mov word [rbp + 119], ax
	mov rbx,  [rbp + 83]
	mov ax, word [rbp + 119]
	mov word [rbx], ax
	mov ax, word [rbp + 0]
	add ax, 1
	mov word [rbp + 121], ax
	mov ax, word [rbp + 121]
	mov word [rbp + 0], ax
	jmp L0
L2:
	mov word [rbp + 123], 1
L3:
	cmp word [rbp + 123], 20
	jg __L8__
	MOV byte [rbp + 125], 1
	JMP __L9__
__L8__:
	MOV byte [rbp + 125], 0
__L9__:		mov al, byte [rbp + 125]
	cmp al, 1
	jz L4
	mov al, byte [rbp + 125]
	cmp al, 0
	jz L5
L4:
	mov ax, word [rbp + 123]
	sub ax, 1
	mov word [rbp + 126], ax
	mov ax, word [rbp + 126]
	imul ax, 2
	mov word [rbp + 128], ax
	mov rax, rbp
	add rax, 2
	xor rbx, rbx
	mov bx, word [rbp + 128]
	add rax, rbx
	mov qword [rbp + 130], rax
	mov rbx, qword [rbp + 130]
	mov rax, 0
	mov ax, word [rbx]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf
	mov ax, word [rbp + 123]
	add ax, 1
	mov word [rbp + 138], ax
	mov ax, word [rbp + 138]
	mov word [rbp + 123], ax
	jmp L3
L5:


; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
