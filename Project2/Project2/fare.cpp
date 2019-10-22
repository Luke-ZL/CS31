#include<iostream>
#include<string>
using namespace std;

int main()
{
	cout << "age of rider: ";
	int age;
	cin >> age;
	cout << "Student? (y/n): ";
	char status;
	cin >> status;
	cin.ignore(10000, '\n');
	cout << "Destination ";
	string destination;
	getline(cin, destination);
	cout << "Number of zone boundaries crossed: ";
	int number;
	cin >> number;
	cout << "---" << endl;
	cout.precision(2);
	cout.setf(ios::fixed);  //collect all needed information
	if (age < 0)                                              //see if the age input is negative
		cout << "The age must not be negative" << endl;   
	else if ((status != 'y') && (status != 'n'))             // see if the status is "y" or "n"
		cout << "You must enter y or n" << endl;
	else if (destination == "")                             // see if the string is empty
		cout << "You must enter a destination" << endl;
	else if (number < 0)                                   // see if the number of zone crossed is negative
		cout << "The number of zone boundaries crossed must not be negative" << endl;
	else if (age >= 65)                                   // see if the passenger is a senior citizen
	{
		cout << "The fare to " << destination << " is $";
		if (number == 0)                                
			cout << "0.45" << endl;
		else if ((number == 1) && (status == 'y')) cout << "0.65" << endl;
		else cout << (0.55 + 0.25*number) << endl;
	}
	else if (((age < 18) || (status == 'y')) && (number <= 1)) //see if the passenger is a student
		cout << "The fare to " << destination << " is $0.65" << endl;
		else cout << "The fare to " << destination << " is $" << (1.35 + 0.55*number) << endl;
}