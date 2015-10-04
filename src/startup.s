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
        mov.l    #0xffff00,sp
        # call main function
        jsr      @_main
1:
        bra      1b
