#pragma once
#include "Square.h"
#include <vector>
#include "Field.h"
using namespace std;
class Icon
{
private:
	int x, y, w;
	vector<Field> fields;
	vector<Square> squares;
	vector<int> pattern;
	void parseToBinary();
	void createSquares();
public:
	Icon(vector<Field>);
	void render();
};

