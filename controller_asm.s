.equ LONG_DELAY_TIME, 0x000028
.equ SHORT_DELAY_TIME, 0x000008

// Send 0100 0000 0000 0011 0000 0010
.global controller_asm_write
controller_asm_write:
    
    mov r6, #LONG_DELAY_TIME
    mov r7, #SHORT_DELAY_TIME
    mov r9, pc
    b pulse

    mov r6, #12
    mov r7, #39
    mov r9, pc
    b pulse

    mov r3, #12
    zero_loop:
        mov r6, #LONG_DELAY_TIME
        mov r7, #SHORT_DELAY_TIME
        mov r9, pc
        b pulse
        subs r3, #1
        bne zero_loop

    mov r3, #2
    one_loop:
        mov r6, #12
        mov r7, #42
        mov r9, pc
        b pulse
        subs r3, #1
        bne one_loop
    
    mov r3, #6
    zero_loop_2:
        mov r6, #LONG_DELAY_TIME
        mov r7, #SHORT_DELAY_TIME
        mov r9, pc
        b pulse
        subs r3, #1
        bne zero_loop_2    

    mov r3, #3
    one_loop_2:
        mov r6, #12
        mov r7, #40
        mov r9, pc
        b pulse
        subs r3, #1
        bne one_loop_2

    bx lr
    
    
pulse:

    ldr r0, CLR0
    mov r1, #(3 << 20)
    str r1, [r0]
    
    mov r2, r6
    delay_1:
        subs r2, #1
        bne delay_1
    
    ldr r0, SET0
    str r1, [r0]
    
    mov r2, r7
    delay_2:
        subs r2, #1
        bne delay_2

    mov pc, r9

FSEL2: .word 0x20200008
SET0: .word 0x2020001C
CLR0: .word 0x20200028
LEV0: .word 0x20200034


