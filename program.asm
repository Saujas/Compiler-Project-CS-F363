extern printf

section .data
	fmt_integer: db '%d', 10, 0
	fmt_float: db '%f', 10, 0
	fmt_string: db '%s', 10, 0

section .bss
	mem_main resb 6
section .text
global main

main:
	mov rbp, mem_main
	push rbp
	mov rbp, rsp
	mov word [rbp + 2], 2
	mov ax, word [rbp + 2]
	mov word [rbp + 0], ax
	xor dx, dx
	mov ax, word [rbp + 0]
	mov cx, 2
	idiv cx
	mov word [rbp + 4], ax
	mov ax, word [rbp + 4]
	mov word [rbp + 0], ax
	mov rax, 0
	mov ax, [rbp + 0]
	movsx rax, ax
	mov rdi, fmt_integer
	mov rsi, rax
	mov rax, 0
	call printf


; exiting program
	mov rax, 1
	mov rbx, 0
	int 80h
