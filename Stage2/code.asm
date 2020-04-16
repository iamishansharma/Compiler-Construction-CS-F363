
extern printf, scanf

global mainseg 

section .bss

	ri1: resd 1
	ri2: resd 1
	ri3: resd 1
	ri4: resd 1
	ri5: resd 1
	ri6: resd 1
	ri7: resd 1
	ri8: resd 1
	ri9: resd 1
	ri10: resd 6
	ri11: resd 1
	ri12: resd 1

section .data

	in_format:    db "%d", 0
	out_format:   db "%d", 10, 0

section .text

mainseg:

	;exit code

	mov eax, 1
	mov ebx, 0
	int 80h
