#include <iostream>
using namespace std;


#define BASE_PRIME 29 // liter w alfabecie jest 26 a to jest next_prime(26)
#define MOD_PRIME 1000000007 // jedna z wiekszych liczb pierwsza x taka ze x^2 < LONGLONGMAX

int* s;
long long* base_prime_pow;
long long* hash_prefix;

long long hash_fragment(int l, int r, int k) {
    return (((hash_prefix[r] - hash_prefix[l - 1] + MOD_PRIME) % MOD_PRIME) * base_prime_pow[k-l]) % MOD_PRIME;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    cin >> n >> m;

    s = new int[n + 1];
    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c;
        s[i] = c - 'a';
    }

    base_prime_pow = new long long[n];
    base_prime_pow[0] = 1;
    for (int i = 1; i < n; ++i) {
        base_prime_pow[i] = (base_prime_pow[i-1] * BASE_PRIME) % MOD_PRIME;
    }

    hash_prefix = new long long[n+1];
    hash_prefix[0] = 0;
    hash_prefix[1] = s[1];
    for (int i = 2; i <= n; ++i) {
        hash_prefix[i] = (hash_prefix[i-1] + (base_prime_pow[i-1] * s[i])% MOD_PRIME)% MOD_PRIME;
    }

    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int len1 = b - a + 1;
        int len2 = d - c + 1;
        int k = max(a, c);
        long long hash1 = hash_fragment(a, b, k);
        long long hash2 = hash_fragment(c, d, k);
        if (len1 == len2 && hash1 == hash2) {
            cout << "=\n";
        } else {
            int l = 0;
            int r = min(len1, len2) - 1;
            while (l < r) {
                int mid = (l + r) / 2;
                if (hash_fragment(a, a + mid, k) != hash_fragment(c, c + mid, k)) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            if (s[a + l] > s[c + l]) {
                cout << ">\n";
            } else if (s[a + l] < s[c + l]) {
                cout << "<\n";
            } else {
                if (len1 < len2) {
                    cout << "<\n";
                } else {
                    cout << ">\n";
                }
            }
        }
    }

    delete[] s;
    delete[] base_prime_pow;
    delete[] hash_prefix;
    return 0;
}
