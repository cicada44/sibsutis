#include <stdio.h>
int var1, x; // глобальные переменные
int func1(int a)
{
    char z;
}
int func2(int a)
{
    func3(a);
    int x, y, z;
    float x;
    func1(x);
}
int func3(int a)
{
    int a, b;
}
int main()
{
    int a, var1;
    func1(a);
    func2(var1);
}