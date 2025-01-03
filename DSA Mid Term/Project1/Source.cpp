#include <iostream>
using namespace std;

bool prime(int a) {
    if (a <= 1) {
        return false;
    }

    for (int j = 2; j < a; j++) {
        if (a % j == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int num;
    cout << "Enter an number: " << endl;
    cin >> num;

    if (prime(num)) {
        cout << "True" << endl;
    }
    else {
        cout <<"False" << endl;
    }

    return 0;
}