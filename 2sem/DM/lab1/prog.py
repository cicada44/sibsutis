from curses.ascii import isdigit
from pickle import NONE
import re
from collections import Counter

print("Внимание! {b'N'},set() - пустое множество\n")

concatArr = []
iscArr = []


def plus(inpArr, inpArr2):
    return inpArr + inpArr2


def minus(inpArr, inpArr2):
    return set(inpArr) - set(inpArr2)


def per(inpArr, inpArr2):
    c = list((Counter(inpArr) & Counter(inpArr2)).elements())
    c = set(c)
    return c


def pris(inpArr, inpArr2):
    j = 0
    for x in range(0, len(inpArr)):
        if inpArr[x] in inpArr2:
            j += 1
    if j == len(inpArr):
        return 1
    else:
        return 0


def subStr1(str):
    inpArr = [None] * len(str)
    inpArr = list(map(int, str.split(",")))
    return inpArr


def subStr2(str2):
    inpArr2 = [None] * len(str2)
    inpArr2 = list(map(int, str2.split(",")))
    return inpArr2


def inpStr1():
    print("Введите элементы массива 1 через запятую")
    str = input()
    return str


def inpStr2():
    print("Введите элементы массива 2 через запятую")
    str2 = input()
    return str2


def vich():
    arr1 = []
    arr2 = []
    str = inpStr1()
    if (str == ''):
        arr1 = [NONE]
    else:
        arr1 = subStr1(str)
    str2 = inpStr2()
    if (str2 == ''):
        arr2 = [NONE]
    else:
        arr2 = subStr2(str2)

    print("Множества, которые вы ввели: \n", arr1, arr2)
    print("\n")

    print("Введите соответствующую цифу\n1 - Обьединение\n2 - Пересечение\n3 - Присутствие элементов м1 в м2\n4 - Вычитание\n")

    cs = int(input())

    print("Результат:")
    if cs == 1:
        concatArr = plus(arr1, arr2)
        concatArr = set(concatArr)
        print(concatArr)
    elif cs == 2:
        perArr = per(arr1, arr2)
        print(perArr)
    elif cs == 3:
        if (pris(arr1, arr2)):
            print("Присутствует")
        elif (pris(arr1, arr2) == 0):
            print("Отсутствует")
    elif cs == 4:
        iscArr = minus(arr1, arr2)
        print(iscArr)
    rel()


def rel():
    print("\n")
    c = int(input("0 - воспользоваться программой еще раз\n1 - выход: "))
    if (c == 0):
        vich()
    elif (c == 1):
        return 0


vich()
