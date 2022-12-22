global main
extern printf          ; NASM requires declarations of external symbols, unlike GAS
section .rodata         ; read only 
    format db "What? %d", 10, 0   ; C 0-terminated string: "%#x\n"
section .text

main:
    push rbp                  ;  prologue
    mov rbp, rsp


    sub rsp, 4                ; optional: space for location variable

    mov DWORD [rbp - 4], 6065 ; initialize the the local variable


    ; Call printf.
    mov   esi,  [rbp - 4]     ; second argument
    lea   rdi, [ format]      ; first argument
    xor   eax, eax            ; must always be set to 0 for non-floating point data
    call  printf

    ; Return from main.
    xor   eax, eax


    add esp, 4                ; optional, since we created a variable, lets remove
    leave                     ; epilogue -> mov rsp, rbp & then pop rbp
    ret