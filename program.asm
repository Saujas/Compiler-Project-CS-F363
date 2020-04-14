extern printf
section .data
	fmt_integer: db '%d', 10, 0
	fmt_float: db '%f', 10, 0
	fmt_string: db '%s', 10, 0

section .bss
	mem_main resb 42
section .text
global main

main:
mov rbp, mem_main
push rbp
mov rbp, rsp
mov word [rbp + 21], 3
mov ax, word [rbp + 21]
mov word [rbp + 2], ax
mov ax, word [rbp + 2]
mov word [rbp + 23], ax
mov ax, word [rbp + 23]
mov word [rbp + 0], ax
mov rax, 0
mov ax, [rbp + 0]
mov rdi, fmt_integer
mov rsi, rax
mov rax, 0
call printf
mov rax, 0
mov ax, [rbp + 2]
mov rdi, fmt_integer
mov rsi, rax
mov rax, 0
call printf
mov byte [rbp + 25], 0
mov al, byte [rbp + 25]
mov byte [rbp + 4], al
mov rax, 0
mov al, byte [rbp + 4]
mov rdi, fmt_integer
mov rsi, rax
mov rax, 0
call printf
mov rax, __float64__(2.43)
mov qword [rbp + 26], rax
mov rax, qword [rbp + 26]
mov qword [rbp + 5], rax
mov rax, qword [rbp + 5]
mov qword [rbp + 34], rax
mov rax, qword [rbp + 34]
mov qword [rbp + 13], rax
mov rax, qword[rbp + 13]
mov rdi, fmt_float
movq xmm0, rax
mov eax, 1
call printf
sub rsp, 12
mov rax, '23122.65'
mov qword [rsp], rax
add rsp, 8
mov rax, '44422.65'
mov qword [rsp], rax
add rsp, 3
mov byte [rsp], 0
sub rsp, 11
mov rax, rsp
mov rdi, fmt_string
mov rsi, rax
mov rax, 0
call printf
add rsp, 12
sub rsp, 5
mov rax, 'true'
mov qword [rsp], rax
add rsp, 4
mov byte [rsp], 0
sub rsp, 4
mov rax, rsp
mov rdi, fmt_string
mov rsi, rax
mov rax, 0
call printf
add rsp, 5


; exiting program
mov rax, 1
mov rbx, 0
int 80h
