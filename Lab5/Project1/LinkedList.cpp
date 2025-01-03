#include <iostream>
using namespace std;

int main() {

	int n, sum = 0;
	cout << "Enter Value of N: ";
	cin >> n;
	
	int temp = n;
	do {
		sum = sum + n;
		n--;
		
		

	} while (n != 0);
	cout << "Sum is : " << sum << endl;


}