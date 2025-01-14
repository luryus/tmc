	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section .rodata
    .align 2

gUnk_0810CF4C:: @ 0810CF4C
	.incbin "guard/gUnk_0810CF4C.bin"

gUnk_0810D0A4:: @ 0810D0A4
	.incbin "guard/gUnk_0810D0A4.bin"

gUnk_0810F524:: @ 0810F524
	.incbin "guard/gUnk_0810F524.bin"

gUnk_0810F544:: @ 0810F544
	.4byte sub_08063E90
	.4byte sub_08063F20
	.4byte sub_08063F78

gUnk_0810F550:: @ 0810F550
	.4byte sub_08063D44
	.4byte sub_08063DC8
	.4byte sub_08063E54
	.4byte sub_08063E6C

gUnk_0810F560:: @ 0810F560
	.incbin "guard/gUnk_0810F560.bin"

gUnk_0810F59A:: @ 0810F59A
	.incbin "guard/gUnk_0810F59A.bin"

gUnk_0810F5D4:: @ 0810F5D4
	.incbin "guard/gUnk_0810F5D4.bin"

gUnk_0810F60E:: @ 0810F60E
	.incbin "guard/gUnk_0810F60E.bin"
.ifdef JP
    @ TODO only small differences
	.incbin "guard/gUnk_0810F60E_1_JP.bin"
.else
.ifdef EU
	.incbin "guard/gUnk_0810F60E_2_EU.bin"
.else
	.incbin "guard/gUnk_0810F60E_3_USA-DEMO_USA-DEMO_JP.bin"
.endif
.endif
.ifdef JP
    @ TODO only small differences
	.incbin "guard/gUnk_0810F60E_4_JP.bin"
.else
.ifdef EU
	.incbin "guard/gUnk_0810F60E_5_EU.bin"
.else
	.incbin "guard/gUnk_0810F60E_6_USA-DEMO_USA-DEMO_JP.bin"
.endif
.endif

gUnk_0810F648:: @ 0810F648
	.incbin "guard/gUnk_0810F648.bin"

gUnk_0810F682:: @ 0810F682
	.incbin "guard/gUnk_0810F682.bin"

gUnk_0810F6BC:: @ 0810F6BC
	.4byte gUnk_0810F560
	.4byte gUnk_0810F59A
	.4byte gUnk_0810F5D4
	.4byte gUnk_0810F60E
	.4byte gUnk_0810F648
	.4byte gUnk_0810F682
