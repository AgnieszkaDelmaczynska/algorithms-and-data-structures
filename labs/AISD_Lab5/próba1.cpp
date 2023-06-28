#include <iostream>

using namespace std;

char negate(char x) {
    if (x == 'f') {
        return 't';

    }
    else {
        return 'f';

    }
}

char conjuct(char x, char y) {
    if (x == 'f' || y == 'f') {
        return 'f';

    }
    else {
        return 't';

    }
}

char alternate(char x, char y) {
    if (x == 'f' && y == 'f') {
        return 'f';

    }
    else {
        return 't';

    }
}

int main() {
    int n;
    char t[1000] = { '\0'
    };
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> t;
        int j = 0;
        while (t[j] != '\0') {
            if (t[j] == 'K') {
                t[j - 2] = conjuct(t[j - 2], t[j - 1]);
                int k = j - 1;
                while (t[k] != '\0') {
                    t[k] = t[k + 2];
                    t[k + 1] = t[k + 3];
                    k += 2;

                }
                j -= 2;

            }
            else if (t[j] == 'A') {
                t[j - 2] = alternate(t[j - 2], t[j - 1]);
                int k = j - 1;
                while (t[k] != '\0') {
                    t[k] = t[k + 2];
                    t[k + 1] = t[k + 3];
                    k += 2;

                }
                j -= 2;

            }
            else if (t[j] == 'N') {
                t[j - 1] = negate(t[j - 1]);
                int k = j;
                while (t[k] != '\0') {
                    t[k] = t[k + 1];
                    k++;

                }
                j--;

            }
            j++;

        }
        cout << t << '\n';

    }
}