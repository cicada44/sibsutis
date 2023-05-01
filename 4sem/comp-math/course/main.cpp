#include <cmath>
#include <iostream>

#define MU 0.0188     // коэф. смертности от COVID-19
#define BETA 0.999    // скорость выздоровления заражённых случаев
#define RO 0.952      // скорость восстановления выявленных случаев
#define ALPHA_E 0.999 // коэф. заражения между бессимптомно-инфицированным и восприимчивым населением
#define ALPHA_I 0.999 // коэф. заражения между инфицированным и восприимчивым населением (социальные факторы)
#define K 0.042       // частота появления симптомов в открытых случаях
#define N0 2798170    // население Новосибирской области
#define E0 99         // начальное количество бессимптомно инфицированных
#define R0 24         // начальное количество вылеченных
#define GAMMA 0       // скорость повторного заражения, раз (0 - устойчивый иммунитет)
#define C 1           // ограничение на передвижения граждан (изначально - 1 + C_ISOL * (...), сокращена до 1, т.к. C_ISOL = 0)
// N - вся популяция, S - восприимчивые, E - заражённые бессимптомные, I - инфицированные с симптомами, R - вылеченные, D - умершие

// система дифференциальных уравнений модели SEIR-D
double dS_dt(double S, double E, double I, double R, double D)
{
    double N = S + E + I + R + D;
    return -C * (ALPHA_I * S * I + ALPHA_E * S * E) / N + GAMMA * R;
}

double dE_dt(double S, double E, double I, double R, double D)
{
    double N = S + E + I + R + D;
    return C * (ALPHA_I * S * I + ALPHA_E * S * E) / N - (K + RO) * E;
}

double dI_dt(double S, double E, double I, double R, double D)
{
    return K * E - BETA * I - MU * I + 0 * (S + R + D);
}

double dR_dt(double S, double E, double I, double R, double D)
{
    return BETA * I + RO * E - GAMMA * R + 0 * (S + D);
}

double dD_dt(double S, double E, double I, double R, double D)
{
    return MU * I + 0 * (S + E + R + D);
}

// метод Эйлера-Коши (метод Эйлера с пересчётом)
void euler_modified(double a, double b, double h, double *S, double *E, double *I, double *R, double *D)
{
    int n = (int)ceil((b - a) / h) + 1;
    double s = *S, e = *E, i = *I, r = *R, d = *D;
    double si, ei, ii, ri, di;
    double s1, e1, i1, r1, d1;

    for (int k = 0; k <= n; k++)
    {
        s1 = s + h * dS_dt(s, e, i, r, d);
        e1 = e + h * dE_dt(s, e, i, r, d);
        i1 = i + h * dI_dt(s, e, i, r, d);
        r1 = r + h * dR_dt(s, e, i, r, d);
        d1 = d + h * dD_dt(s, e, i, r, d);
        // std::cout << k << ": S1 = " << s1 << "; E1 = " << e1 << "; I1 = " << i1 << "; R1 = " << r1 << "; D1 = " << d1 << std::endl;
        si = s + (h / 2) * (dS_dt(s, e, i, r, d) + dS_dt(s1, e1, i1, r1, d1));
        ei = e + (h / 2) * (dE_dt(s, e, i, r, d) + dE_dt(s1, e1, i1, r1, d1));
        ii = i + (h / 2) * (dI_dt(s, e, i, r, d) + dI_dt(s1, e1, i1, r1, d1));
        ri = r + (h / 2) * (dR_dt(s, e, i, r, d) + dR_dt(s1, e1, i1, r1, d1));
        di = d + (h / 2) * (dD_dt(s, e, i, r, d) + dD_dt(s1, e1, i1, r1, d1));
        // std::cout << k << ": Si = " << si << "; Ei = " << ei << "; Ii = " << ii << "; Ri = " << ri << "; Di = " << di << std::endl;
        s = s1;
        e = e1;
        i = i1;
        r = r1;
        d = d1;
        // std::cout << k << ": S = " << s << "; E = " << e << "; I = " << i << "; R = " << r << "; D = " << d << std::endl;
    }
    *S = s;
    *E = e;
    *I = i;
    *R = r;
    *D = d;
}

int main()
{
    std::cout.precision(12);
    std::cout.setf(std::ios::fixed);

    // начальные данные
    int a = 0, b = 90;
    double eps = 1e-2, h = 1;
    double e = E0, i = 0, r = R0, d = 0, s = N0 - i - e - r - d;
    std::cout << "\nНачальные данные для модели SEIR-D:\nN0 = " << N0 << " (всё население)\nS0 = " << (int)floor(s) << " (восприимчивое население)\nE0 = " << E0 << " (бессимптомно инфицированные)\nI0 = " << (int)floor(i) << " (выявленные случаи / инфицированные с симптомами)\nR0 = " << R0 << " (вылечившиеся)\nD0 = " << (int)floor(d) << " (умершие)\na = " << a << " (день начала отсчёта), b = " << b << " (день конца отсчёта), h = " << h << " (шаг разбиения)" << std::endl;

    euler_modified(a, b, h, &s, &e, &i, &r, &d); // первая итерация

    double delta, d1 = d;
    int k = 1;
    do // цикл до заданной точности решения
    {
        h = h / 2;
        e = E0, i = 0, r = R0, d = 0, s = N0 - i - e - r - d;
        euler_modified(a, b, h, &s, &e, &i, &r, &d);
        delta = fabs(d - d1);
        d1 = d;
        std::cout << k << ": delta = " << delta << ", h = " << h << std::endl;
        k++;
    } while (delta > eps);

    std::cout << "\nРезультаты метода Эйлера-Коши (метода Эйлера с пересчётом):\nE (бессимптомно инфицированных) = " << (int)floor(e) << "\nI (выявленные случаи / инфицированные с симптомами) = " << (int)floor(i) << "\nD (количество умерших) = " << (int)floor(d) << std::endl;
    double n = s + e + i + r + d;
    std::cout << "N (final) = " << (int)round(n) << " = N0 (начальное население) => ни один человек не потерян\n\n";
    return 0;
}