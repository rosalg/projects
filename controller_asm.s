.equ LONG_DELAY_TIME, 0x000028
.equ SHORT_DELAY_TIME, 0x000008

// Send 0100 0000 0000 0011 0000 0010
.global controller_asm_write
controller_asm_write:
    
    mov r2, pc
    b low_pulse
    
    mov r2, pc
    b high_pulse

    mov r3, #12
    zero_loop:
        mov r2, pc
        b low_pulse
        subs r3, #1
        bne zero_loop

    mov r3, #2
    one_loop:
        mov r2, pc
        b high_pulse
        subs r3, #1
        bne one_loop
    
    mov r3, #6
    zero_loop_2:
        mov r2, pc
        b low_pulse
        subs r3, #1
        bne zero_loop_2    

    mov r3, #3
    one_loop_2:
        mov r2, pc
        b high_pulse
        subs r3, #1
        bne one_loop_2
    
    bx lr
    
    
low_pulse:

    ldr r0, CLR0
    mov r1, #(3 << 20)
    str r1, [r0]
    
    mov r0, #LONG_DELAY_TIME
    delay_1:
        subs r0, #1
        bne delay_1
    
    ldr r0, SET0
    str r1, [r0]
    
    mov r0, #SHORT_DELAY_TIME
    delay_2:
        subs r0, #1
        bne delay_2

    mov pc, r2

high_pulse:
    ldr r0, CLR0
    mov r1, #(3 << 20)
    str r1, [r0]

    mov r0, #SHORT_DELAY_TIME
    delay_3:
        subs r0, #1
        bne delay_3
    
    ldr r0, SET0
    str r1, [r0]
    
    mov r0, #LONG_DELAY_TIME
    delay_4:
        subs r0, #1
        bne delay_4

    mov pc, r2

FSEL2: .word 0x20200008
SET0: .word 0x2020001C
CLR0: .word 0x20200028
LEV0: .word 0x20200034


