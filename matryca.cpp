#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    string wallpaper;
    cin >> wallpaper;

    int i = 0;
    for (; i < wallpaper.size(); ++i) {
        if (wallpaper[i] != '*') {
            break;
        }
    }

    if (i == wallpaper.size()) {
        cout << "1\n";
        return 0;
    }

    char last = wallpaper[i];

    bool two_distinct = false;
    int j = i + 1;
    for (; j < wallpaper.size(); ++j) {
        if (wallpaper[j] == '*') {
            continue;
        }
        if (wallpaper[j] != last) {
            two_distinct = true;
            break;
        }
    }

    if (!two_distinct) {
        cout << "1\n";
        return 0;
    }

    int min = j - i - 1;
    int len = 0;

    for (; i < wallpaper.size(); ++i) {
        if (wallpaper[i] == '*') {
            ++len;
        } else if (wallpaper[i] != last) {
            if (len < min) {
                min = len;
            }
            len = 0;
            last = wallpaper[i];
        } else {
            len = 0;
        }
    }
    cout << wallpaper.size() - min << "\n";

    return 0;
}
