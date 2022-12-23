        global  main
        extern  puts
        section .text
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 3
        mov     byte [rbp-1], 0
        mov     byte [rbp-2], 65
        mov     byte [rbp-3], 65
        lea     rcx, [rbp-3]                    ; First argument is address of message
        sub     rsp, 28h                        ; Reserve the shadow space
        call    puts                            ; puts(message)
        add     rsp, 28h                        ; Remove shadow space
        mov     rsp, rbp
        pop     rbp
        ret
message:
        db      'Hello', 0                      ; C strings need a zero byte at the end