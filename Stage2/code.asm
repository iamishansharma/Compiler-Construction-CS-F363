
extern printf, scanf

global main 


section .data

	in_format:            db "%d", 0
	in_format_int:        db "Input: Enter an integer value -> ", 10, 0
	in_format_real:       db "Input: Enter a real value -> ", 10, 0
	in_format_boolean:    db "Input: Enter a boolean value -> ", 10, 0
	out_format:           db "Output: %d", 10, 0
	trueout:              db "Output: True", 10, 0
	falseout:             db "Output: False", 10, 0

section .text

main:
	; Assignment Statement for 'u' at LineNo: 10
	; FALSE specific
		mov [ri9], dword 1
		mov eax, [ri9]
		mov [ri7], eax

	; Assignment Statement for 'a' at LineNo: 11
		mov [ri10], dword 5

		mov eax, [ri10]
		mov [ri4], eax

	; Assignment Statement for 'b' at LineNo: 12
		mov [ri11], dword 9

		mov eax, [ri11]
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

	; Assignment Statement for 'z' at LineNo: 15
		; Multiplication
		mov eax, [ri2]
		mov ebx, [ri5]
		imul ebx
		mov [ri12], eax

		; Subtraction
		mov eax, [ri4]
		mov ebx, [ri5]
		sub eax, ebx
		mov [ri13], eax

		; Multiplication
		mov eax, [ri13]
		mov ebx, [ri2]
		imul ebx
		mov [ri14], eax

		mov [ri15], dword 2

		; Multiplication
		mov eax, [ri4]
		mov ebx, [ri15]
		imul ebx
		mov [ri16], eax

		; Multiplication
		mov eax, [ri5]
		mov ebx, [ri1]
		imul ebx
		mov [ri17], eax

		; Subtraction
		mov eax, [ri16]
		mov ebx, [ri17]
		sub eax, ebx
		mov [ri18], eax

		; Addition
		mov eax, [ri14]
		mov ebx, [ri18]
		add eax, ebx
		mov [ri19], eax

		; Addition
		mov eax, [ri12]
		mov ebx, [ri19]
		add eax, ebx
		mov [ri20], eax

		; Addition
		mov eax, [ri1]
		mov ebx, [ri20]
		add eax, ebx
		mov [ri21], eax

		mov eax, [ri21]
		mov [ri3], eax

	; Assignment Statement for 'v' at LineNo: 16
		mov [ri22], dword 10

		; Greater Than
		mov eax, [ri3]
		mov ebx, [ri22]
		cmp eax, ebx
		jg l1
	; FALSE RELOP
		mov [ri23], dword 0
		jmp l2
	; TRUE RELOP
	l1: mov [ri23], dword 1
	l2:
		; Less Than Equal To
		mov eax, [ri4]
		mov ebx, [ri5]
		cmp eax, ebx
		jle l3
	; FALSE RELOP
		mov [ri24], dword 0
		jmp l4
	; TRUE RELOP
	l3: mov [ri24], dword 1
	l4:
		; Less Than
		mov eax, [ri1]
		mov ebx, [ri2]
		cmp eax, ebx
		jl l5
	; FALSE RELOP
		mov [ri25], dword 0
		jmp l6
	; TRUE RELOP
	l5: mov [ri25], dword 1
	l6:
		; AND
		mov eax, [ri25]
		mov ebx, [ri7]
	; if left == 0, goto lsetfalse
		cmp eax, dword 0
		je l7
	; if right == 0, goto lsetfalse
		cmp ebx, dword 0
		je l7
	; 11 case, set parent = True
		mov [ri26], dword 1
		jmp l8
	; 00/01/10 case, set Parent = False
	l7: mov [ri26], dword 0
	l8:
		; AND
		mov eax, [ri24]
		mov ebx, [ri26]
	; if left == 0, goto lsetfalse
		cmp eax, dword 0
		je l9
	; if right == 0, goto lsetfalse
		cmp ebx, dword 0
		je l9
	; 11 case, set parent = True
		mov [ri27], dword 1
		jmp l10
	; 00/01/10 case, set Parent = False
	l9: mov [ri27], dword 0
	l10:
		; OR
		mov eax, [ri23]
		mov ebx, [ri27]
	; if left == 1, goto lsettrue
		cmp eax, dword 1
		je l11
	; if right == 1, goto lsettrue
		cmp ebx, dword 0
		je l11
	; 00 case, set parent = false
		mov [ri28], dword 0
		jmp l12
	; 11/01/10 case, set Parent = true
	l11: mov [ri28], dword 1
	l12:
		mov eax, [ri28]
		mov [ri8], eax

		; Printing INTEGER ID: z
		push rbp
		mov rdi, out_format
		mov rax, 0
		mov rsi, [ri3]
		call printf
		pop rbp

		; Printing BOOLEAN ID: u
		push rbp
		cmp [ri7], dword 1
		je l13
		mov rdi, falseout
		mov rax, 0
		jmp l14
	l13: mov rdi, trueout
		mov rax, 0

	l14: 
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
	ri7: 	resd 1 ; ID: u | Line No: 9
	ri8: 	resd 1 ; ID: v | Line No: 9
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
	ri19: 	resd 1
	ri20: 	resd 1
	ri21: 	resd 1
	ri22: 	resd 1
	ri23: 	resd 1
	ri24: 	resd 1
	ri25: 	resd 1
	ri26: 	resd 1
	ri27: 	resd 1
	ri28: 	resd 1
