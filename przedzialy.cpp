#include <iostream>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::set<int> r_bounds;
    std::set<int, std::greater<>> l_bounds;
    r_bounds.insert(0);
    l_bounds.insert(n+1);

    for (int i = 0; i < m; ++i) {
        char sign;
        int l, r;
        std::cin >> sign >> l >> r;
        if (l == 1) {
            if (sign == '+') {
                r_bounds.insert(r);
            } else {
                r_bounds.erase(r);
            }
        } else {
            if (sign == '+') {
                l_bounds.insert(l);
            } else {
                l_bounds.erase(l);
            }
        }
        std::cout << std::max(0, *l_bounds.rbegin() - *r_bounds.rbegin() - 1) << "\n";
    }

    return 0;
}