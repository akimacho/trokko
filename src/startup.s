# ============================================================================
#   Name        : startup.s
#   Discription : jump to main function
# ============================================================================

        .h8300h
        .section .text
        .global  _start
#       .type    _start,@function
_start:
        # set up stack pointer
        # _start is a symbol in linker script
        mov.l    #_stack,sp
        # call main function
        jsr      @_main
1:
        bra      1b
