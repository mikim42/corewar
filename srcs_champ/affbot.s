.name "affbot"
.comment "AFF U"

ld %65, r1
ld %66, r2
ld %67, r3
ld %68, r4

ld %0, r5

time_to_aff:
aff r1
aff r1
aff r1
aff r1
aff r2
aff r2
aff r2
aff r2
aff r3
aff r3
aff r3
aff r3
aff r4
aff r4
aff r4
aff r4

zjmp %:time_to_aff

