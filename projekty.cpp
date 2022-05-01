#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    int weight[n+1];
    int edge_count[n+1];
    for (int i = 1; i <= n; ++i) {
        cin >> weight[i];
        edge_count[i] = 0;
    }
    vector<int> graph[n+1];
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[b].push_back(a);
        ++edge_count[a];
    }
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<>> q;
    for (int i = 1; i <= n; ++i) {
        if (edge_count[i] == 0) {
            q.push(pair<int, int>(weight[i], i));
        }
    }
    int max = 0;
    int chosen = 0;
    while (chosen < k) {
        pair<int, int> v = q.top();
        q.pop();
        ++chosen;
        if (v.first > max) {
            max = v.first;
        }
        for (int w : graph[v.second]) {
            --edge_count[w];
            if (edge_count[w] == 0) {
                q.push(pair<int, int>(weight[w], w));
            }
        }
    }
    cout << max << "\n";
    return 0;
}
