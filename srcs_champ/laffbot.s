.name "laffbot"
.comment "i liek 2 laff"

sti r1, %:time_to_aff, %1
st r2, -5
ld %72, r1
ld %97, r2
ld %104, r3
ld %97, r4
ld %33, r5
ld %32, r6

ld %0, r7

time_to_aff:
live %0
aff r1
aff r2
aff r3
aff r4
aff r5
aff r6

zjmp %:time_to_aff

