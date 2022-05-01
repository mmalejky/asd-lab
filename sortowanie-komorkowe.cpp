#include <iostream>
using namespace std;

#define NUMBER 1000000000

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    int elements[n];
    for (int i = 0; i < n; ++i) {
        cin >> elements[i];
    }

    int num[n][n][2];
    enum way {to_left, to_right};
    for (int i = 0; i < n; ++i) {
        num[i][i][to_left] = 0;
        num[i][i][to_right] = 1;
    }

    for (int end = 1; end < n; ++end) {
        for (int begin = end - 1; begin >= 0; --begin) {
            num[end][begin][to_right] = 0;
            num[end][begin][to_left] = 0;
            if (elements[begin + 1] > elements[begin]) {
                num[end][begin][to_left] += num[end][begin + 1][to_left];
                if (num[end][begin][to_left] >= NUMBER) {
                    num[end][begin][to_left] %= NUMBER;
                }
            }
            if (elements[end] > elements[begin]) {
                num[end][begin][to_left] += num[end][begin + 1][to_right];
                if (num[end][begin][to_left] >= NUMBER) {
                    num[end][begin][to_left] %= NUMBER;
                }
            }
            if (elements[begin] < elements[end]) {
                num[end][begin][to_right] += num[end - 1][begin][to_left];
                if (num[end][begin][to_right] >= NUMBER) {
                    num[end][begin][to_right] %= NUMBER;
                }
            }
            if (elements[end - 1] < elements[end]) {
                num[end][begin][to_right] += num[end - 1][begin][to_right];
                if (num[end][begin][to_right] >= NUMBER) {
                    num[end][begin][to_right] %= NUMBER;
                }
            }
        }
    }

    cout << (num[n - 1][0][to_right] + num[n - 1][0][to_left]) % NUMBER << "\n";
    return 0;
}
