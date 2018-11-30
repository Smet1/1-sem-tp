#include <iostream>

int main() {
    int val = 0, stat = 0;
    int n = 0;

    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> val >> stat;
        if (val < 0) {
            // remove
            std::cout << "remove\n";
        } else {
            // add
            std::cout << "add\n";
        }
        // find stat
        std::cout << "stat\n\n";
    }

    return 0;
}