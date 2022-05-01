#include <iostream>

using namespace std;

#define LENGTH_LIMIT 20
#define POSITIVE_INFINITY INT32_MAX
#define NEGATIVE_INFINITY 0

/* WPPR - wspolny podciag prawie rosnacy
 * Ai - prefix A{1..i}
 * WPPR(i, j, k)-zbior WPPR prefiksow Ai oraz Bj dlugosci k
 * best(WPPR(i, j, k))-najlepszy WPPR prefiksow Ai i Bj o dlugosci k 
 *                   (najlepszy tj. o najmienjszym elemencie maksymalnym w nim)
 * tablice indeksuje od 1
* */
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int32_t n, m, c;
    cin >> n;
    cin >> m;
    cin >> c;

    int32_t a[n + 1], b[m + 1];
    for (int32_t i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int32_t i = 1; i <= m; ++i) {
        cin >> b[i];
    }

    /* tab[i][j][k] = best(WPPR(i, j, k)) */
    int32_t tab[n + 1][m + 1][LENGTH_LIMIT + 1];
    for (int32_t i = 0; i <= n; ++i) {
        for (int32_t j = 0; j <= m; ++j) {
            tab[i][j][0] = NEGATIVE_INFINITY;
            for (int32_t k = 1; k <= LENGTH_LIMIT; ++k) {
                tab[i][j][k] = POSITIVE_INFINITY;
            }
        }
    }
    bool exceed = false;
    for (int32_t i = 1; i <= n && !exceed; ++i) { //a
        for (int32_t j = 1; j <= m && !exceed; ++j) { //b
            for (int32_t k = min(LENGTH_LIMIT, min(i, j));
                 k >= 1 && !exceed; --k) { //tab
                int32_t new_max = POSITIVE_INFINITY;
                if (a[i] == b[j] && tab[i - 1][j - 1][k - 1] - c <= a[i] &&
                    tab[i - 1][j - 1][k - 1] - c <= b[j]) {
                    new_max = max(a[i], tab[i - 1][j - 1][k - 1]);
                }
                new_max = min(new_max, min(tab[i - 1][j][k], tab[i][j - 1][k]));
                if (new_max < tab[i][j][k]) {
                    if (k >= LENGTH_LIMIT) {
                        exceed = true;
                    }
                    tab[i][j][k] = new_max;
                }
            }
        }
    }
    if (exceed) {
        cout << LENGTH_LIMIT << "\n";
        return 0;
    }
    int32_t p = 1;
    for (; p <= LENGTH_LIMIT; ++p) {
        if (tab[n][m][p] == POSITIVE_INFINITY) {
            break;
        }
    }
    cout << p - 1 << "\n";
    return 0;
}
