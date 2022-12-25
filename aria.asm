; ----------------------------------------------------------------------------------------
; This is a Win64 console program that writes "Hello" on one line and then exits.  It
; uses puts from the C library.  To assemble and run:
;
;     nasm -fwin64 hello.asm && gcc hello.obj && a
; ----------------------------------------------------------------------------------------

        global  main
        extern  puts
        section .text
main:
        push    rbp
        mov     rbp, rsp
        mov     QWORD [rbp-8], 5
        mov     QWORD [rbp-16], 1
L0:
        cmp     QWORD [rbp-8], 0
        jle     L0_exit
        mov     rax, [rbp-16]
        mov     rbx, [rbp-8]
        imul    rax, rbx
        mov     QWORD [rbp-16], rax
        mov     rax, [rbp-8]
        mov     rbx, 1
        sub     rax, rbx
        mov     QWORD [rbp-8], rax
        jmp     L0
L0_exit:
        sub     rsp, 100h                        ; Reserve the shadow space

        lea     rcx, [rbp-16]

        call    puts                            ; puts(message)
        add     rsp, 100h                        ; Remove shadow space
        mov     rsp, rbp
        pop     rbp
        ret
message:
        db      'Hello', 0                      ; C strings need a zero byte at the end