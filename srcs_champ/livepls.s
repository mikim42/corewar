.name "livepls"
.comment "p l s"

init:
		sti r1, %:lspawn, %1		; initialize live instructions
		sti r1, %:write, %1
		sti r1, %:live, %1

		ld %0, r7					; destroy live initialization routine
		sti r7, %:init, %0
		sti r7, %:init, %3
		sti r7, %:init, %7
		sti r7, %:init, %10
		sti r7, %:init, %14
		sti r7, %:init, %17

start:
		ld %16777216, r2			; 0x01000000
		ld %0, r3
		ld %19, r4
		ld %1, r5
		ld %5, r6
		ld %490, r8

lspawn:
		live %0
		fork %:write
		add r3, r6, r3
		ld %0, r7
		zjmp %:lspawn

write:
		live %0
		sti r2, %:end, r3
		add r3, r5, r3
		sti r1, %:end, r3
		add r3, r4, r3

		ld %:end, r7				; r7 = (r3 + %:end)
		add r7, r3, r7
		sub r8, r7, r7				; if (r7 <= 490)
		and r7, %-2147483648, r7	; 0x80000000
		zjmp %:write

		ld %0, r7

live:
		live %0
		zjmp %:live

end:
