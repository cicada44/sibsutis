import math

N = 16
lam = 0.024
u = 0.71
m = 1
n = 10  # {10 ... 16}
array1 = []
array2 = []
j = 0
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
        t += 2
    array1.append(Ut)
    S = 1 - math.pow(lam, N - n + 1) * math.pow(lam + u, - (N - n + 1))
    array2.append(S)
    n += 1

print(array1)
print(array2)
