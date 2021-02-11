#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <iomanip>

using namespace std;
// task 2098
int main() {
    long long b, c, d, k, p;
    cin >> b >> c >> d >> k >> p;
    long long s = 0;
    for (int i = 1; i <= k; i++) {
        s += (c + d * i) * p;
    }
    long long sb = b * 100;
    if (s > sb) {
        std::cout << "Cash" << std::endl << fixed << std::setprecision(2) << double(s - sb) / 100;
    }
    else {
        std::cout << "Insurance" << std::endl << fixed << std::setprecision(2) << double(sb - s) / 100;
    }
    return 0;
}