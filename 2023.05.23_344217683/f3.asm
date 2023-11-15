section .rodata
    double_five dq 5.0       ; Объявление константы double_five и инициализация ее значением 5.0
    double_min_five dq -5.0  ; Объявление константы double_min_five и инициализация ее значением -5.0

section .text

global f3   ; Объявление глобальной функции f3 = -5/x
f3:                        
    push ebp               
    mov ebp, esp           

    and esp, 0xfffffff0    ; Выравнивание стека 
    sub esp, 16            

    finit                  ; Инициализация сопроцессора FPU

    fld qword[double_min_five]  ; Загрузка значения -5 из памяти в стек FPU
    fld qword[ebp + 8]          ; Загрузка значения x из памяти в стек FPU
    fdivp                       ; Деление значения -5 на значение x

    mov esp, ebp           
    pop ebp                
    ret                    
