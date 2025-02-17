import math
import matplotlib.pyplot as plt

N = 10
n = 8  # {8, 9 ,10}
lam = 0.024
u = 0.71
m = 1
t = 0
array_1 = []
array_2 = []
array_3 = []

while t <= 24:
    i = n
    while i <= N:
        l = 0
        Q = 0
        p_i = 0
        while l <= N:
            if N - i - m >= 0:
                deltaX_1 = 1
            else:
                deltaX_1 = 0

            if m - N + i >= 0:
                deltaX_2 = 1
            else:
                deltaX_2 = 0
            ul = (math.pow(u * t, l) / math.factorial(l) * ((deltaX_1 * math.pow(m, l) * math.exp(-m * u * t)) + \
                 (deltaX_2 * math.pow(N - i, l) * math.exp(-1 * (N - i) * u * t))))
            r = 0
            pr = 0
            while r <= (i - n + l):
                pr += ((math.pow((i * lam * t), r) / math.factorial(r)) * math.exp(-i * lam * t))
                r += 1
            p_i += (math.pow((u / lam), l)) * (1 / math.factorial(l))
            Q += ul * pr
            l += 1
        Pi = (math.pow((u / lam), i)) * (1 / math.factorial(i)) * math.pow(p_i, -1)
        Rt = Pi * Q
        if i == 8:
            array_1.append(Rt)
        elif i == 9:
            array_2.append(Rt)
        elif i == 10:
            array_3.append(Rt)
        #print(Rt, i, t)
        i += 1
    t += 2

t = [i for i in range(0, 26, 2)]  # {0 ... 24}

plt.figure(figsize=(12, 8))
plt.plot(t, array_1, label="n = 8")
plt.plot(t, array_2, label="n = 9")
plt.plot(t, array_3, label="n = 10")

plt.legend()
plt.grid()

plt.title('Operative reliability function')
plt.xlabel(f'Working time t, h')
plt.ylabel(f'Operative reliability function R*(t)')
plt.savefig('graphs/RStar.png')

plt.save()