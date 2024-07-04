section .data
i dq 0
start dq 0
free dq 0
k dq 0
equal dq 0
notEq dq 1
string db "word word cat name cats password nam", 10
section .bss
dict resb 255

section .text
    global _start
_start:
createDict:
    mov rdi, dict

    ;start
    mov ecx, 255
    mov edi, dict
clear:
    mov byte [edi], 32
    inc edi
    loop clear
    mov byte [edi], 10
    mov edi, dict
    mov byte [edi], 10

    mov rdi, string
    mov rax, [i]
cycle:
    cmp byte [rdi], 10
    je break1
.cycle:
    cmp byte [rdi], 10
    je .break
    cmp byte [rdi], 32
    je .break
    inc rdi
    inc rax
    jmp .cycle
.break:

    push rax
    sub rax, [start]
    mov [k], rax
    call addToDict
    pop rax
    inc rax
    mov [start], rax
    jmp cycle
break1:


    ;end

    ;copy dict
    ;mov rsi, rdi
    ;mov rdi, dict
    ;mov rcx, 255
    ;rep movsb

    ;out dict
    mov rax, 4
    mov rbx, 1
    mov rcx, dict
    mov rdx, 255
    int 80h

    ;вернуть строку
    mov rax, dict
    ;reg

    mov rax, 1
    xor rbx, rbx
    int 80h

addToDict:
    push rdi
    push rcx
    push rax
    push rbx

    mov rsi, dict
    mov rcx, 0
.cycle1:
    cmp rsi, 10
    je .break1
    mov rax, 1
    mov [notEq], rax
    mov rbx, 0
.for:
    cmp rbx, qword [k]
    je .endfor
    mov rdi, string
    add rdi, [start]
    add rdi, rbx
    push rax
    mov al, byte [rdi]
    cmp byte [rsi], al
    pop rax
    jnz .if
    inc rbx
    inc rsi
    jmp .for
.if:
    mov rax, 0
    mov [notEq], rax
.endfor:
    cmp rbx, [k]
    je .skip
    mov rax, 0
    mov [notEq], rax
.skip:
    ;if (dict = '' or dict = \0) && notEq == true
    cmp byte [rsi], 10
    je .setEqual
    cmp byte [rsi], 32
    je .setEqual
    jmp .unless
.setEqual:
    mov rax, 0
    cmp [notEq], rax
    je .unless
    mov rax, 1
    mov [equal], rax
    jmp .break1
.unless:
.cycle2:
    cmp byte [rsi], 32
    je .plus
    cmp byte [rsi], 10
    je .break2
    inc rsi
.plus:
    inc rsi
.break2:
    jmp .cycle1
.break1:
    mov rax, [equal]
    cmp rax, 1
    je .end
    mov rsi, dict
    add rsi, [free]
    mov rax, [free]
    mov rbx, 0
.for2:
    cmp rbx, [k]
    je .end
    mov rdi, string
    add rdi, [start]
    add rdi, rbx
    push rax
    mov al, byte [rdi]
    mov byte [rsi], al
    pop rax
    inc rsi
    inc rax
    inc rbx
.end:
    inc rsi
    inc rbx
    inc rax
    mov byte [rsi], 10
    mov [free], rax

    push rbx
    push rax
    pop rcx
    pop rdi
    ret