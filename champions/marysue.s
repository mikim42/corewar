.name "MarySue"
.comment "You won't win cAUSE IM JUST THAT GOOD"

# r1 - champion number
# r2 - write position
# r3 - copy size
# r4 - length to copy
# r5 - free space
# r6 - irrelevant register

init:
		sti r1, %:copy, %1			; initialize live instructions
		sti r1, %:live, %1

		ld %0, r6					; destroy live initialization routine
		sti r6, %:init, %0
		sti r6, %:init, %3
		sti r6, %:init, %7
		sti r6, %:init, %10

start:								; marks the start of the core program
		ld %0, r2
		ld %4, r3					; set copy size to 4
		ld %:end, r4				; get the length of the data to copy
		ld %:start, r5
		sub r4, r5, r4
		and r4, %3, r5				; check 4 byte alignment
		zjmp %:copy
		add r4, r3, r4				; align length to 4
		and r4, %-4, r4

copy:
		live %1
		ldi %:start, r2, r5			; read 4 bytes
		sti r5, %:end, r2			; write 4 bytes
		add r2, r3, r2				; increase current write position
		xor r4, r2, r5				; compare current write position with final position
		zjmp %:persist				; exit copy loop
		ld %0, r5					; trick to force zjmp -> jmp
		zjmp %:copy					; copy until the core code has completed its copy cycle

live:
		live %1
		zjmp %:live

persist:
		fork %:live

end:								; marks the end of the program
