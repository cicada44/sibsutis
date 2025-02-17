import math
import matplotlib.pyplot as plt

N = 16
lam = 0.024
u = 0.71
m = 1
n = 10  # {10 ... 16}
array1 = []
array2 = []
array3 = []
array4 = []
array5 = []
array6 = []
array7 = []

while n <= N:
    t = 0
    while t <= 24:
        i = 0
        Pi = 0
        while i <= n - 1:
            pi_r = 0
            r = 0
            while r <= N:
                l = 0
                ul = 0
                while l <= n - i - 1 + r:
                    if N - i - m >= 0:
                        deltaX_1 = 1
                    else:
                        deltaX_1 = 0

                    if m - N + i >= 0:
                        deltaX_2 = 1
                    else:
                        deltaX_2 = 0
                    ul += (math.pow(u * t, l) / math.factorial(l)) * (deltaX_1 * math.pow(m, l) * math.exp(-m * u * t)) + \
                        deltaX_2 * math.pow(N - i, l) * math.exp(-(N - i) * u * t)
                    l += 1
                pi_r += ((math.pow(i * lam * t, r) / math.factorial(r)) * math.exp(- i * lam * t)) * ul
                r += 1
            k = 0
            sumP_i = 0
            while k <= N:
                sumP_i += math.pow((u / lam), k) * (1 / math.factorial(k))
                k += 1
            Pi += math.pow((u / lam), i) * (1 / math.factorial(i)) * math.pow(sumP_i, -1) * pi_r
            i += 1
        Ut = 1 - Pi
        if n == 10:
            array1.append(Ut)
        if n == 11:
            array2.append(Ut)
        if n == 12:
            array3.append(Ut)
        if n == 13:
            array4.append(Ut)
        if n == 14:
            array5.append(Ut)
        if n == 15:
            array6.append(Ut)
        if n == 16:
            array7.append(Ut)
        t += 2
    n += 1

t = [i for i in range(0, 26, 2)]  # {0 ... 24}

plt.figure(figsize=(12, 8))
plt.plot(t, array1, label="n = 10")
plt.plot(t, array2, label="n = 11")
plt.plot(t, array3, label="n = 12")
plt.plot(t, array4, label="n = 13")
plt.plot(t, array5, label="n = 14")
plt.plot(t, array6, label="n = 15")
plt.plot(t, array7, label="n = 16")

plt.legend()
plt.grid()
plt.title('Operative recoverability function')
plt.xlabel(f'Working time t, h')
plt.ylabel(f'Operative recoverability function U*(t)')
plt.savefig('graphs/UStar.png')
# plt.show()