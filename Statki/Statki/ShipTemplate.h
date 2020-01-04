#pragma once
#include <vector>
#include <math.h>
#include "Field.h"
#include "Utils.h"
using namespace std;
class ShipTemplate
{
private:
	vector<int> temp;
public:
	ShipTemplate(char pattern);
	vector<int> getTemplateVector() { return temp; }
	void setTemplateVector(vector<int> vector) { temp = vector; }
	void setElementByIndex(int index, int value) { temp[index] = value; }
	void rotate();
	vector<Field*>* createFields();
	bool isStraight();
	int& operator[] (int);
	bool operator==(const ShipTemplate&);
	bool operator!=(const ShipTemplate&);
	void print();
};

