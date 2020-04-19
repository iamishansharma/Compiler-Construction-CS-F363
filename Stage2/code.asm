
extern printf, scanf

global main 


section .data

	in_format:            db "%d", 0
	in_format_int:        db "Input: Enter an integer value -> ", 10, 0
	in_format_int_a:      db "Input: Enter %d array elements of integer type for range %d to %d -> ", 10, 0
	in_format_real:       db "Input: Enter a real value -> ", 10, 0
	in_format_real_a:     db "Input: Enter %d array elements of real type for range %d to %d -> ", 10, 0
	in_format_boolean:    db "Input: Enter a boolean value (0 or 1) -> ", 10, 0
	in_format_boolean_a:  db "Input: Enter %d array elements of boolean type (0 or 1) for range %d to %d -> ", 10, 0
	out_format_m:         db "Output: ", 10, 0
	out_format_ma:        db "Output Array: ", 10, 0
	out_format:           db "%d", 10, 0
	trueout:              db "True", 10, 0
	falseout:             db "False", 10, 0

	array_iofb:           db "(RUN TIME ERROR): Array index is out of bounds at line no %d", 10, 0

section .text

main:
		; Getting A Value In ID: A
		push rbp
		mov rdi, in_format_int_a ; printing array integer format
		mov rax, 0
		mov rsi, dword 5
		mov rdx, dword 6
		mov rcx, dword 10
		call printf
		pop rbp
		push rbp
		mov r14, dword 0
	l1: 
		mov rdi, in_format
		mov rax, 0
		lea rsi, [ri8 + 4*r14]
		call scanf
		inc r14
		cmp r14, 5
		jne l1
		pop rbp

		; Getting A Value In ID: B
		push rbp
		mov rdi, in_format_int_a ; printing array integer format
		mov rax, 0
		mov rsi, dword 5
		mov rdx, dword 6
		mov rcx, dword 10
		call printf
		pop rbp
		push rbp
		mov r14, dword 0
	l2: 
		mov rdi, in_format
		mov rax, 0
		lea rsi, [ri9 + 4*r14]
		call scanf
		inc r14
		cmp r14, 5
		jne l2
		pop rbp

	; Assignment Statement for 'p' at LineNo: 13
		mov [ri11], dword 7

		mov eax, [ri11]
		mov [ri3], eax

		; FOR iterative stmt ID: k
		mov r15, dword 1
		l3: 
		mov [ri4], r15d
		; Getting A Value In ID: m
		push rbp
		mov rdi, in_format_int ; printing integer format
		mov rax, 0
		call printf
		pop rbp
		push rbp
		mov rdi, in_format
		mov rax, 0
		mov rsi, ri1
		call scanf
		pop rbp

		; Getting A Value In ID: n
		push rbp
		mov rdi, in_format_int ; printing integer format
		mov rax, 0
		call printf
		pop rbp
		push rbp
		mov rdi, in_format
		mov rax, 0
		mov rsi, ri2
		call scanf
		pop rbp

	; Assignment Statement for 'x' at LineNo: 18
		push rbp
		mov r13d, [ri1]
		cmp r13d, 6
		jnge l4
		cmp r13d, 10
		jle l5

	; array index out of bounds error
	l4: 
		push rbp
		mov rdi, array_iofb
		mov rax, 0
		mov rsi, dword 18
		call printf
		pop rbp

		jmp exit
	l5: sub r13d, 6
		mov eax, [ri8 + 4*r13d]

		mov [ri12], eax
		pop rbp

		push rbp
		mov r13d, [ri2]
		cmp r13d, 6
		jnge l6
		cmp r13d, 10
		jle l7

	; array index out of bounds error
	l6: 
		push rbp
		mov rdi, array_iofb
		mov rax, 0
		mov rsi, dword 18
		call printf
		pop rbp

		jmp exit
	l7: sub r13d, 6
		mov eax, [ri9 + 4*r13d]

		mov [ri13], eax
		pop rbp

		; Addition
		mov eax, [ri12]
		mov ebx, [ri13]
		add eax, ebx
		mov [ri14], eax

		mov eax, [ri14]
		mov [ri5], eax

	; Assignment Statement for 'y' at LineNo: 19
		push rbp
		mov r13d, [ri3]
		cmp r13d, 6
		jnge l8
		cmp r13d, 10
		jle l9

	; array index out of bounds error
	l8: 
		push rbp
		mov rdi, array_iofb
		mov rax, 0
		mov rsi, dword 19
		call printf
		pop rbp

		jmp exit
	l9: sub r13d, 6
		mov eax, [ri8 + 4*r13d]

		mov [ri15], eax
		pop rbp

		push rbp
		mov r13d, [ri2]
		cmp r13d, 6
		jnge l10
		cmp r13d, 10
		jle l11

	; array index out of bounds error
	l10: 
		push rbp
		mov rdi, array_iofb
		mov rax, 0
		mov rsi, dword 19
		call printf
		pop rbp

		jmp exit
	l11: sub r13d, 6
		mov eax, [ri9 + 4*r13d]

		mov [ri16], eax
		pop rbp

		; Addition
		mov eax, [ri15]
		mov ebx, [ri16]
		add eax, ebx
		mov [ri17], eax

		mov eax, [ri17]
		mov [ri6], eax

	; Assignment Statement for 'z' at LineNo: 20
		push rbp
		mov r13d, [ri1]
		cmp r13d, 6
		jnge l12
		cmp r13d, 10
		jle l13

	; array index out of bounds error
	l12: 
		push rbp
		mov rdi, array_iofb
		mov rax, 0
		mov rsi, dword 20
		call printf
		pop rbp

		jmp exit
	l13: sub r13d, 6
		mov eax, [ri8 + 4*r13d]

		mov [ri18], eax
		pop rbp

		push rbp
		mov r13d, [ri3]
		cmp r13d, 6
		jnge l14
		cmp r13d, 10
		jle l15

	; array index out of bounds error
	l14: 
		push rbp
		mov rdi, array_iofb
		mov rax, 0
		mov rsi, dword 20
		call printf
		pop rbp

		jmp exit
	l15: sub r13d, 6
		mov eax, [ri9 + 4*r13d]

		mov [ri19], eax
		pop rbp

		; Addition
		mov eax, [ri18]
		mov ebx, [ri19]
		add eax, ebx
		mov [ri20], eax

		mov eax, [ri20]
		mov [ri7], eax

		; Printing INTEGER ID: x
		push rbp
		mov rdi, out_format_m
		mov rax, 0
		call printf
		pop rbp

		push rbp
		mov rdi, out_format
		mov rax, 0
		mov rsi, [ri5]
		call printf
		pop rbp

		; Printing INTEGER ID: y
		push rbp
		mov rdi, out_format_m
		mov rax, 0
		call printf
		pop rbp

		push rbp
		mov rdi, out_format
		mov rax, 0
		mov rsi, [ri6]
		call printf
		pop rbp

		; Printing INTEGER ID: z
		push rbp
		mov rdi, out_format_m
		mov rax, 0
		call printf
		pop rbp

		push rbp
		mov rdi, out_format
		mov rax, 0
		mov rsi, [ri7]
		call printf
		pop rbp

		inc r15
		cmp r15, 4
		jne l3


	;exit code
	exit: mov eax, 1
		mov ebx, 0
		int 80h

section .bss

	ri1: 	resd 1 ; ID: m | Line No: 9
	ri2: 	resd 1 ; ID: n | Line No: 9
	ri3: 	resd 1 ; ID: p | Line No: 9
	ri4: 	resd 1 ; ID: k | Line No: 9
	ri5: 	resd 1 ; ID: x | Line No: 9
	ri6: 	resd 1 ; ID: y | Line No: 9
	ri7: 	resd 1 ; ID: z | Line No: 9
	ri8: 	resd 5 ; ID: A | Line No: 10
	ri9: 	resd 5 ; ID: B | Line No: 10
	ri10: 	resd 5 ; ID: C | Line No: 10
	ri11: 	resd 1
	ri12: 	resd 1
	ri13: 	resd 1
	ri14: 	resd 1
	ri15: 	resd 1
	ri16: 	resd 1
	ri17: 	resd 1
	ri18: 	resd 1
	ri19: 	resd 1
	ri20: 	resd 1
