#include "CornerGrocer.h"

//Read each item from the input file and stores the frequency in a map
void CornerGrocer::LoadDataFromFile(string fileName) {
	ifstream inputFile;
	string itemName;

	inputFile.open(fileName);

	if (!inputFile.is_open()) {
		cout << "Error: Could not open the input file." << endl;
		return;
	}
	while (inputFile >> itemName) {
		itemFrequency[itemName]++;
	}

	inputFile.close();
}

// Creates frequency.dat as a backup file with each item and its frequency
void CornerGrocer::CreateBackupFile(string fileName) {
    ofstream outputFile;

    outputFile.open(fileName);

    if (!outputFile.is_open()) {
        cout << "Error: Could not create the backup file." << endl;
        return;
    }

    for (auto const& item : itemFrequency) {
        outputFile << item.first << " " << item.second << endl;
    }

    outputFile.close();
}

// Returns the number of times a specific item appears
int CornerGrocer::GetItemFrequency(string itemName) {
    if (itemFrequency.count(itemName) == 1) {
        return itemFrequency[itemName];
    }

    return 0;
}

// Prints every item with its numeric frequency
void CornerGrocer::PrintAllFrequencies() {
    for (auto const& item : itemFrequency) {
        cout << item.first << " " << item.second << endl;
    }
}

// Prints every item with a text-based histogram
void CornerGrocer::PrintHistogram() {
    for (auto const& item : itemFrequency) {
        cout << item.first << " ";

        for (int i = 0; i < item.second; ++i) {
            cout << "*";
        }

        cout << endl;
    }
}