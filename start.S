.align 4
.global _start
_start:
	cpsid aif
	ldr sp, =0x1c000000

        ldr r0, =__bss_start
        ldr r1, =__bss_end
        mov r2, #0
label:
        str r2, [r0]
        add r0, r0, #4
        cmp r0, r1
        bne label

        bl main

