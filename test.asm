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
        mov     QWORD [rbp-8], 0
        mov     QWORD [rbp-16], 10
        mov     QWORD [rbp-24], 10
L0:
        cmp     QWORD [rbp-16], 0
        jle     L0_exit
        mov     QWORD [rbp-24], 10
L1:
        cmp     QWORD [rbp-24], 0
        jle     L1_exit
        mov     rax, [rbp-8]
        mov     rbx, 1
        add     rax, rbx
        mov     QWORD [rbp-8], rax
        mov     rax, [rbp-24]
        mov     rbx, 1
        sub     rax, rbx
        mov     QWORD [rbp-24], rax
        jmp     L1
L1_exit:
        mov     rax, [rbp-16]
        mov     rbx, 1
        sub     rax, rbx
        mov     QWORD [rbp-16], rax
        jmp     L0
L0_exit:
        sub     rsp, 100h                        ; Reserve the shadow space

        lea     rcx, [rbp-8]

        call    puts                            ; puts(message)
        add     rsp, 100h                        ; Remove shadow space
        mov     rsp, rbp
        pop     rbp
        ret
message:
        db      'Hello', 0                      ; C strings need a zero byte at the end