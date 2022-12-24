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

        sub     rsp, 100h                        ; Reserve the shadow space

        mov     QWORD [rbp-8], 132
        mov     QWORD [rbp-16], 2
        mov     rax, [rbp-8]
        mov     rbx, [rbp-16]
        imul    rax, rbx
        mov     rax, rax
        mov     rbx, [rbp-8]
        mov     rcx, [rbp-16]
division:
        mov     r8, rdx
        mov     r9, rax
        xor     rdx, rdx
        mov     rax, rbx
        idiv    rcx
        mov     rbx, rax
        mov     rax, r9
        mov     rdx, r8
        mov     rbx, rbx
        sub     rax, rbx
        mov     QWORD [rbp-24], rax
        lea     rcx, [rbp-24]
     
        call    puts                            ; puts(message)
        add     rsp, 100h                        ; Remove shadow space
        mov     rsp, rbp
        pop     rbp
        ret
message:
        db      'Hello', 0                      ; C strings need a zero byte at the end