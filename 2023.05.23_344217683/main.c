#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>

#include "f1.h"
#include "f2.h"
#include "f3.h"
#include "root.h"
#include "integral.h"
#include "example.h"

int main(int argc, char *argv[]) {
    const char *short_options = "HriR:I:";                      // Определение коротких опций
    const struct option long_options[] = {                      // Определение длинных опций
        {"help",          no_argument,       NULL, 'H'},
        {"root",          no_argument,       NULL, 'R'},
        {"iterations",    no_argument,       NULL, 'I'},
        {"test-root",     required_argument, NULL, 'T'},
        {"test-integral", required_argument, NULL, 'Q'},
        {NULL, 0,                            NULL, 0}
    };

    int options;
    double res_12 = root(f1, f2, 1, 1.5, 0.00001);        // Вычисление корня уравнения для f1 и f2
    int iterations_12 = iterations;
    iterations = 0;
    double res_23 = root(f2, f3, -0.8, -0.3, 0.00001);    // Вычисление корня уравнения для f2 и f3
    int iterations_23 = iterations;
    iterations = 0;
    double res_13 = root(f1, f3, -2.5, -2, 0.00001);      // Вычисление корня уравнения для f1 и f3
    int iterations_13 = iterations;
    
    char *parsing_element;
    void *func_array[] = {f1, f2, f3, ex_f1, ex_f2, ex_f3};             // Массив указателей на функции
    
    if (argc == 1) {
        printf("%lf\n", integral(f2, res_23, res_12, 0.00001) + integral(f3, res_13, res_23, 0.00001) - integral(f1, res_13, res_12, 0.00001));         // Вычисление интеграла и вывод результата
    }
    
    while ((options = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        // Цикл обработки опций командной строки
        if (options == 'H') {
            printf("Данная программа вычисляет площадь фигуры, ограниченной функциями:\n");
            printf("\tf1 = exp(x) + 2,\n");
            printf("\tf2 = -2 * x + 8,\n");
            printf("\tf3 = -5 / x (x > 0),\n");
            printf("с заданной точностью eps = 0.001.\n");
            printf("Для нахождения точек пересечения используется комбинированный метод (хорд и касательных).\n");
            printf("Для вычисления интеграла используется квадратурная формула трапеций.\n");
            printf("Для запуска программы в обычном режиме введите: %s\n", argv[0]);
            printf("\n");
            printf("Доступные опции командной строки:\n");
            printf("--help, -H: Выводит на печать справочную информацию о программе и список всех допустимых ключей командной строки.\n");
            printf("--root, -R: Печатает координаты точек пересечения кривых.\n");
            printf("--iterations, -I: Печатает число итераций, необходимых для приближенного решения уравнений при поиске точек пересечения.\n");
            printf("--test-root, -T: Позволяет протестировать функцию root. Фактические параметры вызова root задаются единственным параметром этой опции в виде F1:F2:A:B:E:R, где F1, F2 - номера используемых функций, A, B, E - значения параметров a, b, eps1 функции root, R - правильный ответ (вычисленный аналитически). Программа вызывает функцию root с указанными параметрами, сравнивает результат с правильным ответом и выводит на экран полученный результат, абсолютную и относительную ошибку.\n");
            printf("--test-integral, -Q: Позволяет протестировать функцию integral. Фактические параметры вызова integral задаются единственным параметром этой опции в виде F:A:B:E:R, где F - номер используемой функции, A, B, E - значения параметров a, b, eps2 функции integral, R - правильный ответ (вычисленный аналитически). Программа вызывает функцию integral с указанными параметрами, сравнивает результат с правильным ответом и выводит на экран полученный результат, абсолютную и относительную ошибку.\n");
        } else if (options == 'R') {
            printf("Точка пересечения первой и второй функций: (%lf %lf)\n", res_12, f1(res_12));
            printf("Точка пересечения второй и третьей функций: (%lf %lf)\n", res_23, f2(res_23));
	        printf("Точка пересечения первой и третьей функций: (%lf %lf)\n", res_13, f1(res_13));
        } else if (options == 'I') {
            printf("Количество итераций для нахождения пересечения первой и второй функций: %d\n", iterations_12);
            printf("Количество итераций для нахождения пересечения второй и третьей функций: %d\n", iterations_23);
            printf("Количество итераций для нахождения пересечения первой и третьей функций: %d\n", iterations_13);
        } else if (options == 'T') {
            parsing_element = strtok(optarg, ":");
            int first_index = atoi(parsing_element);
            parsing_element = strtok(NULL, ":");
            int second_index = atoi(parsing_element);
            parsing_element = strtok(NULL, ":");
            double a_ = atof(parsing_element);
            parsing_element = strtok(NULL, ":");
            double b_ = atof(parsing_element);
            parsing_element = strtok(NULL, ":");
            double eps = atof(parsing_element);
            parsing_element = strtok(NULL, ":\0");
            double answer = atof(parsing_element);
            double ans = root(func_array[first_index - 1], func_array[second_index - 1], a_, b_, eps);
            printf("%lf %lf %lf\n", ans, fabs(ans - answer), fabs(ans - answer) / fabs(ans));
        } else if (options == 'Q') {
            parsing_element = strtok(optarg, ":");
            int indexx = atoi(parsing_element);
            parsing_element = strtok(NULL, ":");
            double a_2 = atof(parsing_element);
            parsing_element = strtok(NULL, ":");
            double b_2 = atof(parsing_element);
            parsing_element = strtok(NULL, ":");
            double eps_2 = atof(parsing_element);
            parsing_element = strtok(NULL, ":\0");
            double answerr = atof(parsing_element);
            double answ = integral(func_array[indexx - 1], a_2, b_2, eps_2);
            printf("%lf %lf %lf\n", answ, fabs(answ - answerr), fabs(answ - answerr) / fabs(answ));
            printf("%lf %lf %lf\n", answ, fabs(answ - answerr), fabs(answ - answerr) / fabs(answ));
        } else {
            printf("Неверный ввод, для печати справочной информации введите: '%s --help' или '%s -H'\n", argv[0], argv[0]);
        }
    }
    return 0;
}