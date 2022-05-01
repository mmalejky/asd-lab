#include <iostream>

#define vt std::pair<int, int>

int *depth;
int *left_son;
int *right_son;
int *father;
vt *deepest;
vt *outermost;
vt *farthest;
int **ancestor;
int logn;
static vt base(-1, 0);

void deep(int v) {
    if (v != 0) {
        deep(left_son[v]);
        deep(right_son[v]);
        vt temp = max(deepest[left_son[v]], deepest[right_son[v]]);
        if (temp.first == -1)
            temp.second = v;
        ++temp.first;
        deepest[v] = temp;
    }
}

#define print(x) std::cout << ((x == 0) ? -1 : x) << "\n"

void outside(int v, int d) {
    if (v == 0) {
        return;
    }
    depth[v] = d;
    if (father[v] != 0) {
        vt v1 = outermost[father[v]];
        vt v2 = (left_son[father[v]] == v) ? deepest[right_son[father[v]]] : deepest[left_son[father[v]]];
        if (v1 > v2) {
            ++v1.first;
            outermost[v] = v1;
        } else {
            v2.second = (v2.first == -1) ? father[v] : v2.second;
            v2.first+=2;
            outermost[v] = v2;
        }
    } else {
        outermost[v] = base;
    }
    outside(left_son[v], d + 1);
    outside(right_son[v], d + 1);
}

inline int anc(int v, int k) {
    int i = __builtin_ffs(k)-1;
    while (i != -1) {
        v = ancestor[v][i];
        k &= ~(1 << i);
        i = __builtin_ffs(k)-1;
    }
    return v;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n = 0;
    std::cin >> n;

    left_son = new int[n + 1];
    right_son = new int[n + 1];
    father = new int[n + 1];
    deepest = new vt[n + 1];
    outermost = new vt[n + 1];
    farthest = new vt[n + 1];
    depth = new int[n + 1];
    ancestor = new int *[n + 1];

    father[1] = 0;
    int temp;
    for (int i = 1; i <= n; ++i) {
        std::cin >> temp;
        left_son[i] = temp == -1 ? 0 : temp;
        if (temp != 0)
            father[left_son[i]] = i;
        std::cin >> temp;
        right_son[i] = temp == -1 ? 0 : temp;
        if (temp != 0)
            father[right_son[i]] = i;
    }

    deepest[0] = base;
    deep(1);
    outside(1, 0);

    for (int i = 1; i <= n; ++i) {
        farthest[i] = max(deepest[i], outermost[i]);
    }

    int temp1 = deepest[1].first;
    logn = 0;
    while (temp1 > 1) {
        temp1 /= 2;
        ++logn;
    }
    ++logn;

    for (int i = 0; i <= n; ++i) {
        ancestor[i] = new int[logn];
        ancestor[i][0] = father[i];
    }

    for (int k = 1; k < logn; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (ancestor[i][k - 1] == 0) {
                ancestor[i][k] = 0;
            } else {
                ancestor[i][k] = ancestor[ancestor[i][k - 1]][k - 1];
            }
        }
    }

    int m = 0;
    std::cin >> m;

    for (int i = 0; i < m; ++i) {
        int glade;
        int dist;
        std::cin >> glade;
        std::cin >> dist;
        if (dist > farthest[glade].first) {
            std::cout << "-1\n";
            continue;
        } else if (dist == farthest[glade].first) {
            print(farthest[glade].second);
            continue;
        } else if (dist == 0) {
            print(glade);
            continue;
        }
        vt v = vt(0, glade);
        vt u = vt(0, farthest[glade].second);
        int diff = depth[u.second] - depth[v.second];
        if (depth[u.second] > depth[v.second]) {
            u.first = diff;
            u.second = anc(u.second, diff);
        } else {
            v.first = -diff;
            v.second = anc(v.second, -diff);
        }
        int k = logn-1;
        while (u.second != v.second) {
            int begin = 0;
            int end = k;
            while (begin < end) {
                int mid = (begin + end) / 2 + ((begin + end) % 2 != 0);
                if (ancestor[v.second][mid] == ancestor[u.second][mid]) {
                    end = mid-1;
                } else {
                    begin = mid;
                }
            }
            v.first = v.first + (1 << begin);
            v.second = ancestor[v.second][begin];
            u.first = u.first + (1 << begin);
            u.second = ancestor[u.second][begin];
            k = begin;
        }
        if (dist <= v.first) {
            print(anc(glade, dist));
        } else {
            print(anc(farthest[glade].second, farthest[glade].first - dist));
        }
    }
    return 0;
}
