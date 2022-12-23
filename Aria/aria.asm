global main
section .text
main:
        push    rbp
        mov     rbp, rsp
        mov     DWORD [rbp-8], -5
        mov     DWORD [rbp-12], -1
        mov     DWORD [rbp-16], 4
        mov     rsp, rbp
        ret