#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "MFraction.h"

int main() {
	int total = 0;												 //total questions
	int correct = 0;											 //correct answers
	bool again = true;
	char operation;
	int add = 0;
	int sub = 0;
	int mult = 0;
	int div = 0;
	string input;
	MFraction mixedFract1;
	MFraction mixedFract2;
	MFraction answer;
	MFraction userGuess;
	MFraction endProgram(0, 0, 1);

	cout << "Please follow instructions carefully." << endl;
	cout << "Enter your operation like 1 1/2 + 1/4." << endl;
	cout << "Enter 0/1 % 0/1 to stop the program." << endl;
	cout << endl;

	while (again) {
		cout << "Please enter your operation --> ";
		cin >> mixedFract1 >> operation >> mixedFract2;       //reads input for w n/d (operation) w n/d
		if (mixedFract1 == endProgram && operation == '%' && mixedFract2 == endProgram) {                          
			again = false;
			cout << endl;
			cout << "You got " << correct << " out of " << total << " questions correct." << endl;
			break;
		}
		//program should stop if any denominators are 0

		//execute operation only after confirming no denominators are 0
		if (mixedFract1.getDenominator() != 0 && mixedFract2.getDenominator() != 0) {
			if (operation == '+') {
				answer = mixedFract1 + mixedFract2;
			}
			else if (operation == '-') {
				answer = mixedFract1 - mixedFract2;
			}
			else if (operation == '*') {
				answer = mixedFract1 * mixedFract2;
			}
			else if (operation == '/') {
				answer = mixedFract1 / mixedFract2;
			}
			else {												   //only valid operations are (+, -, *, /)
				cout << operation << " is an invalid operator." << endl;
			}
		}
		else if (mixedFract1.getDenominator() == 0) {
			cout << mixedFract1 << " is an invalid operand" << endl;
		}
		else if (mixedFract2.getDenominator() == 0) {
			cout << mixedFract2 << " is an invalid operand" << endl;
		}
		//the body of loop only continues if operation is valid
		if (((operation == '+') || (operation == '-') || (operation == '*') || (operation == '/')) && ((mixedFract1.getDenominator() != 0)&& (mixedFract2.getDenominator() != 0))) {
			cout << "Please enter your result --> ";
			cin >> userGuess;                                  //reads the input in w n/d form and creates a mixed fraction object
			total++;										   //increment total questions
			//check if users answer matches that programs answer
			if (userGuess == answer) {
				cout << "Congratualtions! It is correct. " << mixedFract1 << " " << operation << " " << mixedFract2 << " = " << answer << endl;
				answer.printFloat(); 
				correct++;									   //increment correct answers
			}
			else {
				cout << "It is incorrect. The correct answer is " << answer << endl;
				answer.printFloat();
			}
		}
		cout << endl;
	}
}
