#include "ShipTemplate.h"
ShipTemplate::ShipTemplate(char pattern) 
{
	if (pattern == '1') temp = vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 };
	else if (pattern == '2') temp = vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 };
	else if (pattern == '3') temp = vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 };
	else if (pattern == '4') temp = vector<int>{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0 };
	else if (pattern == '5') temp = vector<int>{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 };
	else temp = vector<int>{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
}
void ShipTemplate::rotate(){
	unsigned width = sqrt(temp.size());

	vector<int>* rotatedVec = new vector<int>();
	for (int y = width - 1; y >= 0; --y)
		for (int x = 0; x < width; ++x)
			rotatedVec->push_back(temp.at(x * 5 + y));

	temp = *rotatedVec;
	delete rotatedVec;
}
vector<Field*>* ShipTemplate::createFields() {
	int width = sqrt(temp.size());
	int xmin = width, ymin = width;
	vector<Field*>* fields = new vector<Field*>();
	for (int y = 0; y < width; y++)
		for (int x = 0; x < width; x++) 
			if (temp[y * width + x]) {
				if (y < ymin) ymin = y;
				if (x < xmin) xmin = x;
			}
		
	for (int y = 0; y < width; y++)
		for (int x = 0; x < width; x++) 
			if (temp[y * width + x]) {
				Field* f = new Field(x - xmin, y - ymin, 0, 0, 0);
				fields->push_back(f);
			}
	
		
	return fields;
}

bool ShipTemplate::isStraight() {
	vector<Field*>* fields = createFields();
	bool vertical = true;
	bool horizontal = true;
	int checkedX = fields->at(0)->x;
	int checkedY = fields->at(0)->y;
	for (Field* f : *fields) {
		if (f->x != checkedX) horizontal = false;
		if (f->y != checkedY) vertical = false;
	}
	delete fields;
	return (vertical or horizontal);
}

int& ShipTemplate::operator[] (int x) {
	return temp[x];
}
bool ShipTemplate::operator==(const ShipTemplate& t) {
	for (unsigned i = 0; i < temp.size(); i++) {
		if (temp[i] != t.temp[i])
			return false;
	}
	return true;
}
bool ShipTemplate::operator!=(const ShipTemplate& t) {
	return !operator==(t);
}
void ShipTemplate::print() {
	cout << endl;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++)
			cout << temp[y * 5 + x];
		cout << endl;
	}
	cout << endl;
}