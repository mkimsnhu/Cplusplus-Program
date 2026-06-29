#ifndef CORNERGROCER_H
#define CORNERGROCER_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class CornerGrocer {
private:
	map<string, int> itemFrequency;

public:
	void LoadDataFromFile(string fileName);
	void CreateBackupFile(string fileName);
	int GetItemFrequency(string itemName);
	void PrintAllFrequencies();
	void PrintHistogram();
};

#endif