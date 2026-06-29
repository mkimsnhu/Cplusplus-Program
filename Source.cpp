#include <iostream>
#include <string>
#include "CornerGrocer.h"

using namespace std;

int main() {

	CornerGrocer groceryTracker;

	int menuChoice = 0;
	string searchItem;

	groceryTracker.LoadDataFromFile("C:\\Users\\Administrator\\Documents\\CS210_Project_Three_Input_File.txt");
	groceryTracker.CreateBackupFile("frequency.dat");

	while (menuChoice != 4) {

		cout << "\nCorner Grocer Menu\n";
		cout << "1. Search for an item frequency\n";
		cout << "2. Print all item frequencies\n";
		cout << "3. Print histogram\n";
		cout << "4. Exit\n";
		cout << "Enter your choice: ";
		cin >> menuChoice;

		if (menuChoice == 1) {
			cout << "Enter item name: ";
			cin >> searchItem;

			cout << searchItem << " appears "
				<< groceryTracker.GetItemFrequency(searchItem)
				<< " time(s)." << endl;
		}

		else if (menuChoice == 2) {
			groceryTracker.PrintAllFrequencies();
		}

		else if (menuChoice == 3) {

			groceryTracker.PrintHistogram();
		}

		else if (menuChoice == 4) {
			cout << "Goodbye!" << endl;
		}

		else {
			cout << "Invalid option. Try again." << endl;
		}
	}

	return 0;
}