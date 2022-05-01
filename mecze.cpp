#include <iostream>
#include <unordered_set>
#include <limits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n;
    cin >> m;
    uint64_t players[n];
    for (int i = 0; i < n; ++i) {
        players[i] = 0ULL;
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n/2; ++j) {
            int x;
            cin >> x;
            players[x - 1] |= (1ULL << i);
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    unordered_set<uint64_t> set(players, players + n);
    if (set.size() < n) {
        cout << "NIE\n";
    } else {
        cout << "TAK\n";
    }
    return 0;
}
