#include <iostream>
#include <string>
#include "tads/HashIntCerrado.h"

using namespace std;

int hashFunc(int x) {
    return x;
}

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    HashInt h(26, hashFunc);
    int extras = 0;

    for (int i = 0; i < 2 * n - 2; i += 2) {
        int key = s[i] - 'a';
        int door = s[i + 1] - 'A';

        h.addOne(key);

        if (h.contains(door)) {
            h.removeOne(door);
        } else {
            extras++;
        }
    }

    cout << extras << '\n';
    return 0;
}