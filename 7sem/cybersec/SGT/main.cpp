#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

// Modexp function
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

// Miller-Rabbin test for prime testing
bool isPrime(long long n, int k = 5) {
    if (n < 2) return false;
    if (n != 2 && n % 2 == 0) return false;
    long long s = n - 1;
    while (s % 2 == 0) s /= 2;

    auto millerTest = [](long long d, long long n) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<long long> dist(2, n - 2);
        long long a = dist(gen);
        long long x = modExp(a, d, n);
        if (x == 1 || x == n - 1) return true;
        while (d != n - 1) {
            x = (x * x) % n;
            d *= 2;
            if (x == 1) return false;
            if (x == n - 1) return true;
        }
        return false;
    };

    for (int i = 0; i < k; i++) {
        if (!millerTest(s, n)) return false;
    }
    return true;
}

// Generation random prime number in range [low, high]
long long generatePrime(long long low, long long high) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dist(low, high);
    long long prime = dist(gen);
    while (!isPrime(prime)) {
        prime = dist(gen);
    }
    return prime;
}

// GCD
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Reverse modulo number (Euclid)
int modInverse(int e, int phi) {
    int m0 = phi, t, q;
    int x0 = 0, x1 = 1;
    if (phi == 1) return 0;
    while (e > 1) {
        q = e / phi;
        t = phi;
        phi = e % phi;
        e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// RSA keygen
pair<pair<int, int>, pair<int, int>> generateRSAKeys() {
    long long p = generatePrime(10000, 50000);
    long long q = generatePrime(10000, 50000);
    long long N = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e = 3;
    while (gcd(e, phi) != 1) {
        e++;
    }

    long long d = modInverse(e, phi);

    return {{e, N}, {d, N}};
}

// RSA encrypt (public key)
int rsaEncrypt(int message, int e, int N) {
    return modExp(message, e, N);
}

// RSA decrypt (private key)
int rsaDecrypt(int cipher, int d, int N) {
    return modExp(cipher, d, N);
}

// Permutation graph edges
vector<int> randomPermutation(int n) {
    vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
        permutation[i] = i;
    }
    shuffle(permutation.begin(), permutation.end(), mt19937(random_device()()));
    return permutation;
}

// Hamilton cycle deteciton
bool isHamiltonianCycle(const vector<vector<int>>& graph, const vector<int>& cycle) {
    int n = cycle.size();
    for (int i = 0; i < n; ++i) {
        int u = cycle[i];
        int v = cycle[(i + 1) % n];
        if (graph[u][v] == 0) {
            return false;
        }
    }
    return true;
}

// Builds isomorphic graph
vector<vector<int>> getIsomorphicGraph(const vector<vector<int>>& graph, const vector<int>& permutation) {
    int n = graph.size();
    vector<vector<int>> newGraph(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            newGraph[permutation[i]][permutation[j]] = graph[i][j];
        }
    }
    return newGraph;
}

// Graph encrypt with RSA
vector<vector<int>> encryptGraph(const vector<vector<int>>& graph, int e, int N) {
    int n = graph.size();
    vector<vector<int>> encryptedGraph(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            encryptedGraph[i][j] = rsaEncrypt(graph[i][j], e, N);
        }
    }
    return encryptedGraph;
}

// Graph decrypt with RSA
vector<vector<int>> decryptGraph(const vector<vector<int>>& encryptedGraph, int d, int N) {
    int n = encryptedGraph.size();
    vector<vector<int>> decryptedGraph(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            decryptedGraph[i][j] = rsaDecrypt(encryptedGraph[i][j], d, N);
        }
    }
    return decryptedGraph;
}

// Graph and Hamilt. cycle reading from file
void readGraphFromFile(const string& filename, vector<vector<int>>& graph, vector<int>& hamiltonianCycle) {
    ifstream infile(filename);
    int n, m;
    infile >> n >> m;
    graph.resize(n, vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        int u, v;
        infile >> u >> v;
        graph[u][v] = graph[v][u] = 1;
    }

    for (int i = 0; i < n; ++i) {
        int vertex;
        infile >> vertex;
        hamiltonianCycle.push_back(vertex);
    }
}

// Zero-knoledge proof 
void zeroKnowledgeProof(const vector<vector<int>>& graph, const vector<int>& hamiltonianCycle) {
    if (!isHamiltonianCycle(graph, hamiltonianCycle)) {
        cout << "Error: Hamilton's cycle doesn't exist." << endl;
        return;
    }

    auto keys = generateRSAKeys();
    int e = keys.first.first;
    int N = keys.first.second;
    int d = keys.second.first;

    int n = graph.size();
    vector<int> permutation = randomPermutation(n);
    vector<vector<int>> isomorphicGraph = getIsomorphicGraph(graph, permutation);
    vector<vector<int>> encryptedGraph = encryptGraph(isomorphicGraph, e, N);

    cout << "Alice send Bob encrypted graph." << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);
    int bobQuestion = dist(gen);

    if (bobQuestion == 0) {
        cout << "Bob asks: show Hamilton's cycle." << endl;
        vector<int> encryptedCycle;
        for (int vertex : hamiltonianCycle) {
            encryptedCycle.push_back(rsaEncrypt(vertex, e, N));
        }
        cout << "Alice shows Hamilton's cycle." << endl;
    } else {
        cout << "Bob asks: show proof that graph isomorphic." << endl;
        vector<vector<int>> decryptedGraph = decryptGraph(encryptedGraph, d, N);
        cout << "Alice shows graph and permutations." << endl;
    }
}

int main(int argc, char** argv) {
    vector<vector<int>> graph;
    vector<int> hamiltonianCycle;

    string filename(argv[1]);

    readGraphFromFile(filename, graph, hamiltonianCycle);
    zeroKnowledgeProof(graph, hamiltonianCycle);
}
