.name "Plagiarism"
.comment "I wrote all this code"

start:
		st r1, r10
		lfork %2044
		st r10, 6
		live %0

		ld %42991616, r3
		ld %10, r4
		fork %:init

		lfork %1404
		st r10, 6
		live %0
		lfork %2415
		st r10, 6
		live %0
		lfork %2402
		st r10, 6
		live %0
		ld %0, r2
		fork %:fortress
		zjmp %:fork0

barrier:							; this portion is derived from helltrain
		st r10, 11
		st r2, -4
		live %0
		st r2, -87
		st r2, -96
		st r2, -105
		st r2, -114
		st r2, -123
		st r2, -132
		st r2, -141
		st r2, -150
		st r2, -159
		st r2, -168
		st r2, -177
		st r2, -186
		st r2, -195
		st r2, -204
		st r2, -213
		st r2, -222
		st r2, -231
		st r2, -240
		st r2, -249
		st r2, -258
		st r2, -267
		st r2, -276
		st r2, -285
		st r2, -294
		st r2, -303
		st r2, -312
		st r2, -321
		st r2, -330
		st r2, -339
		st r2, -348
		st r2, -357
		st r2, -366
		st r2, -375
		st r2, -384
		st r2, -393
		st r2, -402
		st r2, -411
		st r2, -420
		st r2, -429
		st r2, -438
		st r2, -447
		st r2, -456
		st r2, -465
		st r2, -474
		st r2, -483
		st r2, -492
		ld %0, r2
		zjmp %:barrier

fork0:								; meme forker
		st r10, 6
		live %0
		fork %:fork1				; 1 -> 2
		lldi r3, r3, r3				; delay 50 cycles
		st r10, 6
fork1:
		live %0
		fork %:fork2				; 2 -> 4
		lldi r3, r3, r3
		st r10, 6
fork2:
		live %0
		fork %:fork3				; 4 -> 8
		lldi r3, r3, r3
		st r10, 6
fork3:
		live %0
		fork %:fork4				; 8 -> 16
		lldi r3, r3, r3
		st r10, 6
fork4:
		live %0
		fork %:barrier				; 16 -> 32
		ld %0, r2
		zjmp %:persistence

init:
		sti r3, %:start, %18
		st r2, -5
		sti r4, %:start, %21
		st r2, -5
		sti r10, %:start, %20
		st r2, -5
		st r10, 11
		st r10, 14

fortress:
		live %0
		fork %:barrier
		live %0
		fork %:fortress

preserve:
		ld %16777216, r2			; 0x01000000
		ld %0, r3
		ld %19, r4
		ld %1, r5
		ld %5, r6
		ld %490, r8
		st r10, 6

lspawn:
		live %0
		fork %:write
		add r3, r6, r3
		ld %0, r7
		zjmp %:lspawn

write:
		st r10, 6
		live %0
		sti r2, %:end, r3
		add r3, r5, r3
		sti r10, %:end, r3
		add r3, r4, r3

		ld %:end, r7				; r7 = (r3 + %:end)
		add r7, r3, r7
		sub r8, r7, r7				; if (r7 <= 490)
		and r7, %-2147483648, r7	; 0x80000000
		zjmp %:write

		ld %0, r7

live:
		st r10, 6
		live %0
		fork %:fortress
		st r10, 6
		live %0
		fork %:end
		zjmp %:preserve

persistence:
		st r10, 11
		st r3, -4
persist:
		live %0
		zjmp %:persist

end:
