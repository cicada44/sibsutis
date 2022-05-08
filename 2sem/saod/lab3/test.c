#include <stdio.h>

int main()
{
    char c;
    char s[10];
    printf("Enter the sym: ");
    fflush(stdin);
    scanf("%c", &c);
    printf("Input the str: ");
    fgets(s, 10, stdin);

    return 0;
}