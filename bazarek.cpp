#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int product_count = -1;
    cin >> product_count;

    int product_prices[product_count];
    for (int i = product_count - 1; i >= 0; --i) {
        cin >> product_prices[i];
    }

    int day_count = -1;
    cin >> day_count;

    int daily_product_count[day_count];

    for (int i = 0; i < day_count; ++i) {
        cin >> daily_product_count[i];
    }

    long long product_sums[product_count];
    long long actual_sum = 0;
    int max_even[product_count], min_even[product_count],
        max_odd[product_count], min_odd[product_count];
    int max_even_c = -1, min_even_c = -1, max_odd_c = -1, min_odd_c = -1;

    for (int i = 0; i < product_count; ++i) {
        int product = product_prices[i];
        min_even[i] = product % 2 == 0 ? product : min_even_c;
        min_even_c = min_even[i];
        min_odd[i] = product % 2 == 1 ? product : min_odd_c;
        min_odd_c = min_odd[i];
        actual_sum += product;
        product_sums[i] = actual_sum;
    }

    for (int i = product_count - 1; i >= 0; --i) {
        int product = product_prices[i];
        max_even[i] = max_even_c;
        max_even_c = product % 2 == 0 ? product : max_even_c;
        max_odd[i] = max_odd_c;
        max_odd_c = product % 2 == 1 ? product : max_odd_c;
    }

    for (int today_count : daily_product_count) {
        long long max = product_sums[today_count - 1];
        if (max % 2 == 1) {
            cout << max << "\n";
        } else {
            if (today_count == product_count) {
                cout << "-1\n";
                continue;
            }

            int max_even_b = max_even[today_count - 1];
            int min_even_b = min_even[today_count - 1];
            int max_odd_b = max_odd[today_count - 1];
            int min_odd_b = min_odd[today_count - 1];

            int first_difference = max_even_b - min_odd_b;
            int second_difference = max_odd_b - min_even_b;
            if (max_even_b != -1 && min_even_b != -1 && max_odd_b != -1 && min_odd_b != -1) {
                max += first_difference > second_difference ? first_difference : second_difference;
            } else if (max_even_b != -1 && min_odd_b != -1) {
                max += first_difference;
            } else if (max_odd_b != -1 && min_even_b != -1) {
                max += second_difference;
            } else {
                max = -1;
            }
            cout << max << "\n";

        }
    }

    return 0;
}
