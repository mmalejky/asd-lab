#include <iostream>

using namespace std;
#define N 1000000000


void add(int tree[], int b, int i, int x) {
    i = i + b;
    tree[i] = (tree[i] + x) % N;
    while (i != 1) {
        i /= 2;
        tree[i] = (tree[i] + x) % N;
    }
}

int query(const int tree[], int b, int l, int r) {
    l += b;
    r += b;
    if (l >= 2*b) {
        return 0;
    }
    int sum = tree[l];
    if (r != l) {
        sum = (sum + tree[r]) % N;
    }

    while (l / 2 != r / 2) {
        if (l % 2 == 0) {
            sum = (sum + tree[l + 1]) % N;
        }

        if (r % 2 == 1) {
            sum = (sum + tree[r - 1]) % N;
        }

        l /= 2;
        r /= 2;
    }

    return sum;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;

    int k = 0;
    cin >> k;

    int tab[n];
    for (int i = 0; i < n; ++i) {
        cin >> tab[i];
    }

    int b = 1;
    while (b < n) {
        b *= 2;
    }

    int trees[k][2 * b];
    for (int l = 0; l < k; ++l) {
        for (int i = 0; i < 2*b; ++i) {
            trees[l][i] = 0;
        }
    }
    int partialResult[n][k];
    for (int l = 0; l < k; ++l) {
        for (int i = 0; i < n; ++i) {
            partialResult[i][l] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        partialResult[i][0] = 1;
    }

    for (int l = 1; l < k; ++l) {
        for (int i = 0; i < n; ++i) {
            partialResult[i][l] = query(trees[l], b, tab[i], b - 1);
            add(trees[l], b, tab[i] - 1, partialResult[i][l - 1]);
        }
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        result = (result + partialResult[i][k - 1]) % N;
    }

    cout << result << "\n";
    return 0;
}
