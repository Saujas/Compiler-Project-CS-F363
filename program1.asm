; Define variables in the data section
SECTION .DATA
	hello:     db '2', 10
	helloLen:  equ 2

section .bss
    mem: resb 200

; Code goes in the text section
SECTION .TEXT
	GLOBAL main 

main:
    mov dword [mem + 2], 'abcd'
    mov ecx, mem
    add ecx, 2
	mov eax,4            ; 'write' system call = 4
	mov ebx,1            ; file descriptor 1 = STDOUT
	;mov ecx, mem+2        ; string to write
	mov edx, 4    ; length of string to write
	int 80h              ; call the kernel


	// print stack pointer
	;mov rax, rsp
	;mov rdi, fmt_integer
	;mov rsi, rax
	;mov rax, 0
	;call printf

	; Terminate program
	mov eax,1            ; 'exit' system call
	mov ebx,0            ; exit with error code 0
	int 80h              ; call the kernel