#include<iostream>
#include<stack>
#include<string>

using namespace std;
bool ispalindrome(string word) {
	stack<char>s;

	// loop for push string to stack
	string str1 = "";
	for (int i = 0; i < word.length(); i++) {
		s.push(word[i]);
	}

	// loop for pop char from stacks
	for (int i = 0; i < word.length(); i++) {
		char topcharc = s.top();
		s.pop();
		str1 += s.top();
	}
	if (str1 == word) {
		return true;
	}
	else
	{
		return false;
	}

}
int main() {
	string word;
	cout << "Enter the Word :";
	cin >> word;
	if (ispalindrome(word)) {
		cout << word << " is palindrome." << endl;
	}
	else {
		cout << word << " is not palindrome." << endl;
	}

	return 0;
}
