#include <iostream>
#include <set>

using namespace std;

#define sect pair<int, int>

auto previous(set<sect > &sections, int x) {
    if (sections.empty()) {
        return sections.end();
    }
    return prev(sections.lower_bound(sect(x, x)), 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;

    int m = 0;
    cin >> m;

    set<sect> sections;
    int counter = 0;

    for (int i = 0; i < m; ++i) {
        int begin = 0;
        cin >> begin;
        int end = 0;
        cin >> end;
        char c = '0';
        cin >> c;
        bool found_lp = false;
        bool found_pp = false;
        auto it_lp = previous(sections, begin);
        if (it_lp != sections.end() && it_lp->first <= begin - 1 &&
            it_lp->second >= begin - 1) {
            found_lp = true;
        }
        auto it_pp = previous(sections, end + 2);
        if (it_pp != sections.end() && it_pp->first <= end + 1 &&
            it_pp->second >= end + 1) {
            found_pp = true;
        }

        bool correct = true;
        auto temp1 = sections.lower_bound(sect(begin, begin));
        if (temp1 == sections.end() || temp1->second > end) {
            correct = false;
        }
        auto temp2 = previous(sections, end + 1);
        if (temp2 == sections.end() || temp2->first < begin) {
            correct = false;
        }
        if (temp2->second > end) {
            temp2 = prev(temp2, 1);
        }
        if (temp2 != sections.end()) {
            temp2 = next(temp2, 1);
        }
        if (correct) {
            if (distance(temp1, temp2) > 0) {
                for (auto it = temp1; it != temp2; ++it) {
                    counter -= it->second - it->first + 1;
                }
                sections.erase(temp1, temp2);
            }
        }

        if (found_lp && found_pp) {
            if (c == 'C') {
                if (*it_lp == *it_pp) {
                    counter -= end - begin + 1;
                } else {
                    counter -= it_lp->second - begin + 1;
                    counter -= end - it_pp->first + 1;
                }
                sect pair1(it_lp->first, begin - 1);
                sect pair2(end + 1, it_pp->second);
                sections.erase(it_lp);
                if (*it_lp != *it_pp) {
                    sections.erase(it_pp);
                }
                sections.insert(pair1);
                sections.insert(pair2);
            } else if (c == 'B' && *it_lp != *it_pp) {
                counter += it_pp->first - it_lp->second - 1;
                sect pair(it_lp->first, it_pp->second);
                sections.erase(it_lp);
                sections.erase(it_pp);
                sections.insert(pair);
            }
        } else if (found_lp) {
            if (c == 'C') {
                counter -= it_lp->second - begin + 1;
                sect pair(it_lp->first, begin - 1);
                sections.erase(it_lp);
                sections.insert(pair);
            } else {
                counter += end - it_lp->second;
                sect pair(it_lp->first, end);
                sections.erase(it_lp);
                sections.insert(pair);
            }
        } else if (found_pp) {
            if (c == 'C') {
                counter -= end - it_pp->first + 1;
                sect pair(end + 1, it_pp->second);
                sections.erase(it_pp);
                sections.insert(pair);
            } else {
                counter += it_pp->first - begin;
                sect pair(begin, it_pp->second);
                sections.erase(it_pp);
                sections.insert(pair);
            }
        } else if (c == 'B') {
            counter += end - begin + 1;
            sect pair(begin, end);
            sections.insert(pair);
        }
        cout << counter << "\n";

    }
    return 0;
}
