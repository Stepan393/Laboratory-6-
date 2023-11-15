section .rodata
    double_two dq 2.0    ; Объявление константы double_two и инициализация ее значением 2.0

section .text

global f1               ; Объявление глобальной функции f1 = e^x + 2
f1:                      
    push ebp             
    mov ebp, esp        

    and esp, 0xfffffff0  ; Выравнивание стека
    sub esp, 16          

    finit                ; Инициализация сопроцессора FPU

    fldl2e               ; Загрузка значения логарифма по основанию e в стек FPU
    fld qword[ebp + 8]   ; Загрузка значения x из памяти в стек FPU
    fmulp                ; Умножение значений x и логарифма по основанию e

    fld1                 ; Загрузка значения 1 в стек FPU
    fld st1              ; Копирование вершины стека FPU второй с вершины стека
    fprem                ; Остаток от деления в стеке FPU
    f2xm1                ; Вычисление значения (2^x) - 1
    faddp st1, st0   ; Сложение значений стека FPU и извлечение результата

    fscale               ; Изменение масштаба числа в стеке FPU
    fstp st1           ; Сохранение результата из вершины стека FPU в память

    fld1                 ; Загрузка значения 1 в стек FPU
    faddp                ; Сложение значений стека FPU и извлечение результата
    fld1                 ; Загрузка значения 1 в стек FPU
    faddp                ; Сложение значений стека FPU и извлечение результата

    mov esp, ebp        
    pop ebp             
    ret             