global main
extern puts
section .text

main:
 global main
section .text
main:
        push    rbp
        mov     rbp, rsp
        mov     rax, 100
        mov     rbx, 7
        add     rax, rbx
        mov     QWORD [rbp-8], rax
        mov     rax, [rbp-8]
        mov     rbx, 1
        add     rax, rbx
        mov     QWORD [rbp-16], rax


        sub     rsp, 100                        ; Reserve the shadow space
        lea     rcx, [rbp-16]                    ; First argument is address of message
        call    puts                            ; puts(message)
        add     rsp, 100  

        mov     rsp, rbp
        pop     rbp
        ret