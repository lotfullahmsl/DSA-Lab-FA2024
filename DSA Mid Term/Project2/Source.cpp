#include <iostream>
using namespace std;

float Input_Scores(float& Number_Of_Tests, float& Sum_Of_Scores) {
	float Score;

	cout << "Enter Amount Of Tests: ";
	cin >> Number_Of_Tests;
	
	Sum_Of_Scores = 0;
	for (int i = 1; i <= Number_Of_Tests; i++) {
		cout << "Enter Test " << i << " Score: ";
		cin >> Score;
		Sum_Of_Scores = Sum_Of_Scores + Score;
	}
	cout << "Sum: " << Sum_Of_Scores;
	return Sum_Of_Scores;
	
}

float Average(float& Num_Of_Tests, float& Sum_Of_Scores, float& Avr) {
	Input_Scores(Num_Of_Tests, Sum_Of_Scores);
	Avr = Sum_Of_Scores / Num_Of_Tests;
	cout << "\nAvrage Marks is: " << Avr;

	return Avr;
}

void Grade() {
	float Sum_Of_Scores, Num_Of_Tests, Avr;
	char Grade = Average(Num_Of_Tests, Sum_Of_Scores, Avr);
	
	if (Avr >= 90) {
		cout << "\nYour Grade is: A";
	}
	else if (Avr >= 80 && Avr <90) {
		cout << "\nYour Grade is: B";
	}
	else if (Avr >= 70 && Avr < 80) {
		cout << "\nYour Grade is: C";
	}
	else if (Avr >= 50 && Avr < 70) {
		cout << "\nYour Grade is: D";
	}
	else {
		cout << "\nYour Grade is: F";
	}


}

int main() {
	char Choice;
	do {
		Grade();

		cout << "\nDo You Want to Calculate For others (Y/N): ";
		cin >> Choice;
	} while (Choice == 'Y' || Choice == 'y');
	cout << "\nYou Exited The Program.";
	
}