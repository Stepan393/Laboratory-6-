#include <math.h>
// Нахождеия приближённого корня уравнения f(x) = g(x) методом деления отрезка пополам 

int iterations = 0; // Глобальная переменная для подсчёта числа итераций при вычислении корня

double root(double (*func_f)(double), double (*func_g)(double), double a, double b, double eps1) { // Вычисление корня f(x) = g(x) с заданной точностью
    double c = (a + b) / 2;     // Начальное приближение корня

    while (fabs(func_f(c) - func_g(c)) > eps1) {
        
        iterations++;           // Увеличиваем число итераций
        
        if ((func_f(a) - func_g(a)) * (func_f(c) - func_g(c)) < 0) {
            b = c;
        } else {
            a = c;
        }
        c = (a + b) / 2;        // Обновляем приближение корня
    }

    return c;
}