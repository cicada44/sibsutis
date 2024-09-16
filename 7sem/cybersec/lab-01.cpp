#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace std;

// Быстрое возведение в степень по модулю
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Расширенный алгоритм Евклида: возвращает gcd, x, y
tuple<long long, long long, long long> extendedGCD(long long a, long long b) {
    if (b == 0) {
        return make_tuple(a, 1, 0);
    }
    auto [gcd, x1, y1] = extendedGCD(b, a % b);
    long long x = y1;
    long long y = x1 - (a / b) * y1;
    return make_tuple(gcd, x, y);
}

// Построение общего ключа по схеме Диффи-Хеллмана
pair<long long, long long> diffieHellman(long long p, long long g, long long privateA, long long privateB) {
    long long publicA = modExp(g, privateA, p); // g^a mod p
    long long publicB = modExp(g, privateB, p); // g^b mod p

    // Обмен публичными ключами
    long long sharedKeyA = modExp(publicB, privateA, p); // (g^b)^a mod p
    long long sharedKeyB = modExp(publicA, privateB, p); // (g^a)^b mod p

    return make_pair(sharedKeyA, sharedKeyB); // sharedKeyA должно быть равно sharedKeyB
}

// Алгоритм "Шаг младенца, шаг великана"
long long babyStepGiantStep(long long g, long long y, long long p) {
    long long m = ceil(sqrt(static_cast<double>(p)));
    unordered_map<long long, long long> valueMap;

    // Шаг младенца: вычисляем g^j mod p для j от 0 до m-1
    long long babyStep = 1;
    for (long long j = 0; j < m; j++) {
        valueMap[babyStep] = j;
        babyStep = (babyStep * g) % p;
    }

    // Шаг великана: ищем соответствие
    long long factor = modExp(g, p - m - 1, p); // g^(m*(p-2)) mod p
    long long giantStep = y;
    
    for (long long i = 0; i < m; i++) {
        auto it = valueMap.find(giantStep);
        if (it != valueMap.end()) {
            return i * m + it->second; // Возвращаем решение
        }
        giantStep = (giantStep * factor) % p;
    }

    return -1; // Если решение не найдено
}

int main() {
    // Пример использования функций
    long long p = 23; // Пример простого числа
    long long g = 5;  // Основополагающий элемент
    long long privateA = 6; // Секретный ключ первого пользователя
    long long privateB = 15; // Секретный ключ второго пользователя
    
    auto [sharedKeyA, sharedKeyB] = diffieHellman(p, g, privateA, privateB);
    
    cout << "Shared Key A: " << sharedKeyA << endl;
    cout << "Shared Key B: " << sharedKeyB << endl;

    // Пример использования алгоритма "Шаг младенца, шаг великана"
    long long y = modExp(g, privateA, p); // y = g^a mod p
    long long result = babyStepGiantStep(g, y, p);
    cout << "Discrete log result: " << result << endl;
}
