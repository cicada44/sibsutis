#include <iostream>

#include <boost/multiprecision/miller_rabin.hpp>
#include <cmath>

#include <unordered_map>

using namespace std;

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

tuple<long long, long long, long long> extendedGCD(long long a, long long b) {
    if (b == 0) {
        return make_tuple(a, 1, 0);
    }
    auto [gcd, x1, y1] = extendedGCD(b, a % b);
    long long x = y1;
    long long y = x1 - (a / b) * y1;
    return make_tuple(gcd, x, y);
}

int diffieHellman(int x_a, int x_b) {
    srand(time(0));

    int p = 0, g = 0;
    do {
        p = rand() % 100 * rand() % 100 + 1;
    } while (!boost::multiprecision::miller_rabin_test(p, 25));

    do {
        g = rand() % (p - 1) + 2;
        auto gcd = extendedGCD(g, p - 1);
    } while (std::get<0>(extendedGCD(g, p - 1)) != 1);

    int A = modExp(g, x_a, p);
    int B = modExp(g, x_b, p);
    int K = modExp(B, x_a, p);

    return K;
}

long long babyStepGiantStep(long long g, long long y, long long p) {
    long long m = ceil(sqrt(static_cast<double>(p)));
    unordered_map<long long, long long> valueMap;

    // g^j mod p from j  {0, m-1}
    long long babyStep = 1;
    for (long long j = 0; j < m; j++) {
        valueMap[babyStep] = j;
        babyStep = (babyStep * g) % p;
    }

    // Giant step: accordance
    long long factor = modExp(g, p - m - 1, p); // g^(m*(p-2)) mod p
    long long giantStep = y;
    
    for (long long i = 0; i < m; i++) {
        auto it = valueMap.find(giantStep);
        if (it != valueMap.end()) {
            return i * m + it->second; // Result found
        }
        giantStep = (giantStep * factor) % p;
    }

    return -1;
}

int main() {
    int choice = -1;
    cout << "Input choise:\n";
    cout << "1. Modula exponenta\n";
    cout << "2. Extended Euclid algo\n";
    cout << "3. Diffie-Hellman\n";
    cout << "4. Baby-Giant step\n";
    cout << "0. Exit\n";

    while (choice != 0)
    {
        cout << "\n --->  ";
        cin >> choice;
        switch (choice) {
            case 1: {
                long long base, exp, mod;
                cout << "Base, exp, modulo: ";
                cin >> base >> exp >> mod;
                cout << "Result: " << modExp(base, exp, mod) << endl;
                break;
            }
            case 2: {
                long long a, b;
                cout << "a, b: ";
                cin >> a >> b;
                auto [gcd, x, y] = extendedGCD(a, b);
                cout << "GCD: " << gcd << ", x: " << x << ", y: " << y << endl;
                break;
            }
            case 3: {
                int x_a, x_b;
                cout << "Private keys x_a и x_b: ";
                cin >> x_a >> x_b;
                int sharedKey = diffieHellman(x_a, x_b);
                cout << "Z: " << sharedKey << endl;
                break;
            }
            case 4: {
                long long g, y, p;
                cout << "g, y, p: ";
                cin >> g >> y >> p;
                long long result = babyStepGiantStep(g, y, p);
                if (result != -1) {
                    cout << "Log: " << result << endl;
                } else {
                    cout << "Not found" << endl;
                }
                break;
            }
            default:
                cout << "Wrong choise" << endl;
                break;
        }
    }
}
