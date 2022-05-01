#include <iostream>
#include <algorithm>

#define INF (1u << 30u)
#define pt std::pair<int, int>

class fibonacci_heap {
public:
    void insert(int distance, int island) {
        node *n = new node;
        n->next = n;
        n->prev = n;
        n->child = nullptr;
        n->distance = distance;
        n->island = island;
        n->degree = 0;
        heap = merge(heap, n);
    }

    bool is_empty() {
        return heap == nullptr;
    }

    pt pop_minimum() {
        node *prev = heap;
        pt temp(prev->distance, prev->island);
        heap = get_minimum(heap);
        delete prev;
        return temp;
    }

private:
    struct node {
        node *prev;
        node *next;
        node *child;
        int distance;
        int island;
        int degree;
    };

    node *heap = nullptr;

    static node *merge(node *a, node *b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (a->distance > b->distance) {
            node *temp = a;
            a = b;
            b = temp;
        }
        node *an = a->next;
        node *bp = b->prev;
        a->next = b;
        b->prev = a;
        an->prev = bp;
        bp->next = an;
        return a;
    }

    static node *get_minimum(node *n) {
        if (n->child != nullptr) {
            node *c = n->child;
            do {
                c = c->next;
            } while (c != n->child);
        }
        if (n->next == n) {
            n = n->child;
        } else {
            n->next->prev = n->prev;
            n->prev->next = n->next;
            n = merge(n->next, n->child);
        }
        if (n == nullptr)return n;
        node *trees[60] = {nullptr};

        while (true) {
            if (trees[n->degree] != nullptr) {
                node *t = trees[n->degree];
                if (t == n)break;
                trees[n->degree] = nullptr;
                if (n->distance < t->distance) {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;
                    t->prev = t->next = t;
                    n->degree++;
                    n->child = merge(n->child, t);
                } else {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;
                    if (n->next == n) {
                        t->next = t->prev = t;
                        n->prev = n->next = n;
                        t->degree++;
                        t->child = merge(t->child, n);
                        n = t;
                    } else {
                        n->prev->next = t;
                        n->next->prev = t;
                        t->next = n->next;
                        t->prev = n->prev;
                        n->prev = n->next = n;
                        t->degree++;
                        t->child = merge(t->child, n);
                        n = t;
                    }
                }
                continue;
            } else {
                trees[n->degree] = n;
            }
            n = n->next;
        }
        node *min = n;
        node *begin = n;
        do {
            if (n->distance < min->distance)min = n;
            n = n->next;
        } while (n != begin);
        return min;
    }

};

bool sort1(const int *arr1, const int *arr2) {
    return arr1[0] < arr2[0];
}

bool sort2(const int *arr1, const int *arr2) {
    return arr1[1] < arr2[1];
}

inline int distance(int x1, int y1, int x2, int y2) {
    return std::min(abs(x2 - x1), abs(y2 - y1));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    int **islands = new int *[n];
    for (int i = 0; i < n; ++i) {
        islands[i] = new int[3];
    }
    int x[n + 1];
    int y[n + 1];
    for (int i = 1; i <= n; ++i) {
        std::cin >> x[i] >> y[i];
        islands[i - 1][0] = x[i];
        islands[i - 1][1] = y[i];
        islands[i - 1][2] = i;
    }
    int neighbours[n + 1][4];
    std::sort(islands, islands + n, sort1);
    for (int i = 0; i < n; ++i) {
        neighbours[islands[i][2]][0] = islands[i - (i > 0)][2];
        neighbours[islands[i][2]][1] = islands[i + (i < n - 1)][2];
    }
    std::sort(islands, islands + n, sort2);
    for (int i = 0; i < n; ++i) {
        neighbours[islands[i][2]][2] = islands[i - (i > 0)][2];
        neighbours[islands[i][2]][3] = islands[i + (i < n - 1)][2];
    }
    for (int i = 0; i < n; ++i) {
        delete[] islands[i];
    }
    delete[] islands;
    int dist[n + 1];
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }

    fibonacci_heap queue;
    dist[1] = 0;
    queue.insert(dist[1], 1);
    while (!queue.is_empty()) {
        pt temp = queue.pop_minimum();
        int u = temp.second;
        if (dist[u] < temp.first) {
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            int v = neighbours[u][i];
            if (dist[u] + distance(x[u], y[u], x[v], y[v]) < dist[v]) {
                dist[v] = dist[u] + distance(x[u], y[u], x[v], y[v]);
                queue.insert(dist[v], v);
            }
        }
    }
    std::cout << dist[n];
    return 0;
}