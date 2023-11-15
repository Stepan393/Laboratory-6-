section .rodata
    double_min_two dq -2.0 ; Объявление константы double_min_two и инициализация ее значением -2.0
    double_eight dq 8.0    ; Объявление константы double_eight и инициализация ее значением 8.0

section .text

global f2   ; Объявление глобальной функции f2 = -2x + 8
f2:                       
    push ebp              
    mov ebp, esp          

    and esp, 0xfffffff0   ; Выравнивание стека
    sub esp, 16           

    finit                 ; Инициализация сопроцессора FPU

    fld qword[ebp + 8]          ; Загрузка значения x из памяти в стек FPU
    fld qword[double_min_two]   ; Загрузка значения -2 из памяти в стек FPU
    fmulp                       ; Умножение значений x и -2

    fld qword[double_eight]     ; Загрузка значения 8 из памяти в стек FPU
    faddp                       ; Сложение значений стека FPU и извлечение результата

    mov esp, ebp          
    pop ebp               
    ret                   
