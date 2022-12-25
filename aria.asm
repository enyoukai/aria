global main
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
        mov     rsp, rbp
        pop     rbp
        ret