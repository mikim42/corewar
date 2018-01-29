.name "Do You Like Forks?"
.comment "yOU BETTER LIKE FORKS"

# r1 => champion id
# r2 => thread id

init:
		sti r1, %:live0, %1			; initialize live instructions
		sti r1, %:live1, %1
		sti r1, %:live2, %1
		sti r1, %:live3, %1
		sti r1, %:live4, %1
		sti r1, %:live5, %1
		sti r1, %:live6, %1
		sti r1, %:live7, %1
		sti r1, %:live8, %1
		sti r1, %:live9, %1
		sti r1, %:live10, %1
		sti r1, %:live11, %1
		sti r1, %:live12, %1
		sti r1, %:live13, %1
		sti r1, %:live14, %1
		sti r1, %:thread0, %1
		sti r1, %:wait, %1
		sti r1, %:copy_start, %1
		sti r1, %:prep_jmp, %1

#init_end:
#		ld %3, r3
#		ld %4, r4
#		ld %0, r5
#		ld %0, r6
#		ld %:init_end, r7
#		ld %:init, r8
#		sub r7, r8, r7
#
#destroy:							; destroy live initialization routine
#		sti r5, %:init, r6
#		add r6, r3, r6
#		sti r5, %:init, r6
#		add r6, r4, r6
#		sub r6, r7, r8				; if (r7 <= r6)
#		and r8, %-2147483648, r8	; 0x80000000 (if result is positive or 0, carry bit is set)
#		zjmp %:destroy

		ld %1, r3					; incremental contsants
		ld %4, r6
		ld %16, r7
		ld %7, r10

		ld %:copy_end, r4			; get the length of the data to copy
		ld %:copy_start, r5
		add r5, r10, r5				; fix relativity to match copy_end
		sub r4, r5, r4

#		and r4, %3, r5				; check 4 byte alignment on length
#		zjmp %:fork0
#		add r4, r6, r4				; align length to 4
#		and r4, %-4, r4
		ld %0, r2					; set carry bit

# Model #1 - ETA (live + fork) * 4
###########################################################################################################
# It would be possible to spawn 16 processes using 4 simple forks, but they would all overlap pointlessly #
###########################################################################################################

#fork0:
#		live %0
#		fork %:fork1				; 1 -> 2
#fork1:
#		live %0
#		fork %:fork2				; 2 -> 4
#fork2:
#		live %0
#		fork %:fork3				; 4 -> 8
#fork3:
#		live %0
#		fork %:spawn				; 8 -> 16
#spawn:
#		...

# Model #2 - ETA ((live + fork) * 4) + zjmp
############################################################################################
# The result here is almost identical to the Model #1, but with controlled execution flows #
############################################################################################

fork0:
live0:	live %0
		fork %:fork0_1
live1:	live %0
		fork %:fork0_2
live2:	live %0
		fork %:fork0_3
live3:	live %0
		fork %:thread0
		zjmp %:thread1

fork0_1:
live4:	live %0
		fork %:fork0_1_2
live5:	live %0
		fork %:fork0_1_3
live6:	live %0
		fork %:thread2
		zjmp %:thread3

fork0_2:
live7:	live %0
		fork %:fork0_2_3
live8:	live %0
		fork %:thread4
		zjmp %:thread5

fork0_1_2:
live9:	live %0
		fork %:fork0_1_2_3
live10:	live %0
		fork %:thread6
		zjmp %:thread7

fork0_3:
live11:	live %0
		fork %:thread8
		zjmp %:thread9

fork0_1_3:
live12:	live %0
		fork %:thread10
		zjmp %:thread11

fork0_2_3:
live13:	live %0
		fork %:thread12
		zjmp %:thread13

fork0_1_2_3:
live14:	live %0
		fork %:thread14

thread15:
		add r2, r3, r2
thread14:
		add r2, r3, r2
thread13:
		add r2, r3, r2
thread12:
		add r2, r3, r2
		sub r8, r4, r8				; threads 12->15 => r8 -= copy_size
thread11:
		add r2, r3, r2
thread10:
		add r2, r3, r2
thread9:
		add r2, r3, r2
thread8:
		add r2, r3, r2
		sub r8, r4, r8				; threads 8->11 => r8 -= copy_size + copy_size + copy_size
		sub r8, r4, r8
		sub r8, r4, r8
thread7:
		add r2, r3, r2
thread6:
		add r2, r3, r2
thread5:
		add r2, r3, r2
thread4:
		add r2, r3, r2
		add r8, r4, r8				; threads 4->7 => r8 += copy_size
thread3:
		add r2, r3, r2
thread2:
		add r2, r3, r2
thread1:
		add r2, r3, r2
thread0:							; threads 0->3 => r8 += 0
		live %0
		st r2, r5					; save a copy of the thread id

copy_init:
		and r5, %3, r10				; derive a starting offset based on thread id
		zjmp %:init_end
		add r9, r6, r9
		and r5, %2, r10
		zjmp %:init_end
		add r9, r6, r9
		and r5, %1, r10
		zjmp %:init_end
		add r9, r6, r9
init_end:
		st r9, r11
		st r2, r5

wait:								; Force a delayed order of execution based on thread id.
		live %0
		add r5, r3, r10				; if (r5 < r6)
		sub r6, r10, r10			; -> if ((r5 + 1) <= r6)
		and r10, %-2147483648, r10	; 0x80000000
		zjmp %:copy_start
		lldi r10, r10, r10			; Delay 70+ extra cycles between set iterations
		sub r5, r6, r5
		ld %0, r10
		zjmp %:wait

copy_start:
		live %0
		ldi %:copy_start, r9, r5	; read 4 bytes
		add r9, r8, r10				; offset by r8
		sti r5, %:copy_end, r10		; write 4 bytes
		add r9, r7, r9

		add r9, r3, r5				; if (r9 < r4)
		sub r4, r5, r5				; -> if ((r9 + 1) <= r4)
		and r5, %-2147483648, r5	; 0x80000000 (if result is positive or 0, carry bit is set)
		zjmp %:copy_start

		lldi r10, r10, r10			; Delay 100 cycles for any unfinished writes on this set
		lldi r10, r10, r10
		st r11, r9

prep_jmp:							; Multiple sets of threads running at once forces jumps to the wrong relative addresses.
		live %0						; This is fixed somewhat by the order of execution patch, but it should still be noted.
		ld %3, r5					; set base relative jmp => sizeof(zjmp)
		add r5, r8, r5				; offset by r8
		and r5, %65535, r5			; clear out high bits
		or r5, %84475904, r5		; 05] <- r5, [09 XX XX] <- zjmp
		sti r5, %:jmp_pc, %-1

		ld %0, r5
jmp_pc:
		zjmp %:copy_end				; meant to be replaced by the above code
copy_end:
