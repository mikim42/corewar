.name "ReplicationCentral"
.comment "time to do the thing"

init:
		sti r1, %:live0, %1		; initialize live instructions
		sti r1, %:live1, %1
		sti r1, %:live2, %1
		sti r1, %:persist, %1
		sti r1, %:copy, %1
		sti r1, %:clone, %1

		ld %0, r5					; destroy live initialization routine
		sti r5, %:init, %0
		sti r5, %:init, %3
		sti r5, %:init, %7
		sti r5, %:init, %10
		sti r5, %:init, %14
		sti r5, %:init, %17
		sti r5, %:init, %21
		sti r5, %:init, %24
		sti r5, %:init, %28
		sti r5, %:init, %31
		sti r5, %:init, %35
		sti r5, %:init, %38

start:
		ld %0, r2					; copy start position
		ld %4, r3					; set copy size to 4
		ld %0, r6
		ld %1, r7
		ld %16, r8
		ld %210, r9					; jmp dist

lspawn:
live0:	live %0
		fork %:clone
		add r2, r3, r2
		add r6, r7, r6
live1:	live %0
		fork %:clone
		add r2, r3, r2
		add r6, r7, r6
live2:	live %0
		fork %:clone
		add r2, r3, r2
		add r6, r7, r6

clone:
		live %0
		ld %:end, r4				; get the length of the data to copy
		ld %:start, r5
		sub r4, r5, r4
		and r4, %3, r5				; check 4 byte alignment
		zjmp %:copy
		add r4, r3, r4				; align length to 4
		and r4, %-4, r4

copy:
		live %0
		ldi %:start, r2, r5			; read 4 bytes
		add r2, r9, r10				; offset by r9
		sti r5, %:end, r10			; write 4 bytes
		add r2, r8, r2

		add r2, r7, r5				; if (r2 < r4)
		sub r4, r5, r5				; -> if ((r2 + 1) <= r4)
		and r5, %-2147483648, r5	; 0x80000000 (if result is positive or 0, carry bit is set)
		zjmp %:copy

check:
		xor r6, %3, r5				; if (r6 == 3)
		zjmp %:branch
		ld %0, r5

persist:
		live %0
		zjmp %:persist

branch:
		zjmp %210

end:
