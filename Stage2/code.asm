
extern printf, scanf

global main 


section .data

	in_format:            db "%d", 0
	in_format_int:        db "Input: Enter an integer value -> ", 10, 0
	in_format_int_a:      db "Input: Enter %d array elements of integer type for range %d to %d -> ", 10, 0
	in_format_real:       db "Input: Enter a real value -> ", 10, 0
	in_format_real_a:     db "Input: Enter %d array elements of real type for range %d to %d -> ", 10, 0
	in_format_boolean:    db "Input: Enter a boolean value -> ", 10, 0
	in_format_boolean_a:  db "Input: Enter %d array elements of boolean type for range %d to %d -> ", 10, 0
	out_format_m:         db "Output:", 10, 0
	out_format:           db "%d", 10, 0
	trueout:              db "True", 10, 0
	falseout:             db "False", 10, 0

section .text

main:
	; Assignment Statement for 'a' at LineNo: 9
		mov [ri7], dword 5

		mov eax, [ri7]
		mov [ri4], eax

	; Assignment Statement for 'b' at LineNo: 10
		mov [ri8], dword 9

		mov eax, [ri8]
		mov [ri5], eax

		; Getting A Value In ID: x
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

		; Getting A Value In ID: y
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

	; Assignment Statement for 'z' at LineNo: 13
		; Multiplication
		mov eax, [ri2]
		mov ebx, [ri5]
		imul ebx
		mov [ri9], eax

		; Subtraction
		mov eax, [ri4]
		mov ebx, [ri5]
		sub eax, ebx
		mov [ri10], eax

		; Multiplication
		mov eax, [ri10]
		mov ebx, [ri2]
		imul ebx
		mov [ri11], eax

		mov [ri12], dword 2

		; Multiplication
		mov eax, [ri4]
		mov ebx, [ri12]
		imul ebx
		mov [ri13], eax

		; Multiplication
		mov eax, [ri5]
		mov ebx, [ri1]
		imul ebx
		mov [ri14], eax

		; Subtraction
		mov eax, [ri13]
		mov ebx, [ri14]
		sub eax, ebx
		mov [ri15], eax

		; Addition
		mov eax, [ri11]
		mov ebx, [ri15]
		add eax, ebx
		mov [ri16], eax

		; Addition
		mov eax, [ri9]
		mov ebx, [ri16]
		add eax, ebx
		mov [ri17], eax

		; Addition
		mov eax, [ri1]
		mov ebx, [ri17]
		add eax, ebx
		mov [ri18], eax

		mov eax, [ri18]
		mov [ri3], eax

		; Printing INTEGER ID: z
		push rbp
		mov rdi, out_format_m
		mov rax, 0
		call printf
		pop rbp

		push rbp
		mov rdi, out_format
		mov rax, 0
		mov rsi, [ri3]
		call printf
		pop rbp


	;exit code
	exit: mov eax, 1
		mov ebx, 0
		int 80h

section .bss

	ri1: 	resd 1 ; ID: x | Line No: 7
	ri2: 	resd 1 ; ID: y | Line No: 7
	ri3: 	resd 1 ; ID: z | Line No: 7
	ri4: 	resd 1 ; ID: a | Line No: 8
	ri5: 	resd 1 ; ID: b | Line No: 8
	ri6: 	resd 1 ; ID: c | Line No: 8
	ri7: 	resd 1
	ri8: 	resd 1
	ri9: 	resd 1
	ri10: 	resd 1
	ri11: 	resd 1
	ri12: 	resd 1
	ri13: 	resd 1
	ri14: 	resd 1
	ri15: 	resd 1
	ri16: 	resd 1
	ri17: 	resd 1
	ri18: 	resd 1
