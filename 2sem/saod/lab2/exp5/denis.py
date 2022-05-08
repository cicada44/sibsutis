a = int(input('Введите первое число '))
n = 0
sum = 0
pr = 1
min = a
max = a
chet = 0
while a != 0:
    sum = sum + a
    n = n + 1
    pr = a*pr
    if a % 2 == 0:
        chet = chet + 1
    else:
        pass
    if a > max:
        max = a
    elif a < min:
        min = a
    else:
        pass
    a = int(input('Введите следующее число '))
num = int(input('Введите номер операции от 1 до 6'))
if num == 1:
    print('Сумма введенных чисел = ', sum)
elif num == 2:
    print('Произведение введенных чисел = ', pr)
elif num == 3:
    print('Среднее арифметическое введенных чисел =%.1f' % float(sum/n))
elif num == 4:
    print('Максимальное введенное число = ', max)
elif num == 5:
    print('Минимальное введенное число = ', min)
elif num == 6:
    print('Количество четных чисел =', chet)
    print('Количество нечетных чисел =', n - chet)
