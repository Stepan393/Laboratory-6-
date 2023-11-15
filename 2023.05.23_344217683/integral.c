#include <math.h>

// Вычисление интеграла по формуле прямоугольников

double integral(double (*func_f)(double), double a, double b, double eps2) {
    double result = 0.0;

    // Вычисление интеграла для отрицательной части интервала
    if (a < 0 && b < 0) {
        result += -1*integral(func_f, -1*b, -1*a, eps2);
        return result;
    }

    int n = 1000;               // Количество интервалов
    double h = (b - a) / n;     // Шаг интегрирования

    double sum = 0.0;           // Сумма значений функции
    double prev_sum;            // Предыдущее значение суммы

    do {
        prev_sum = sum;
        sum = 0.0;              // Обнуляем сумму значений функции

        for (int i = 0; i < n; i++) {
            double x = a + (i + 0.5) * h;   // Середина интервала
            sum += func_f(x);               // Прибавляем значение функции в середине интервала
        }

        sum *= h;           // Умножаем сумму на шаг интегрирования

        n *= 2;             // Удваиваем количество интервалов
        h = (b - a) / n;    // Обновляем шаг интегрирования
    } while (fabs(sum - prev_sum) > eps2);

    result += sum;
    return result;
}