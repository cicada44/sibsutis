#include <stdio.h>
int var1, x; // глобальные переменные
int func();
int func3();
int func5();
int func()
{
    func(x);
}
int func1(int a)
{
    char z;
}
int func2(int a)
{
    int x, y, z;
    float x;
    func1(x);
    func3(x);
}
int main()
{
    int a, var1;
    func1(a);
    func2(var1);
}