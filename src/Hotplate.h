#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

class Hotplate {

private:
	char** _plate;
	int _length;
	char* _prev_row;
	char* _curr_row;
	char* _next_row;

	// float calcMaxDiffForCell() {

	// }

	void calcSteadyStateForCell(int row, int col, float max_change) {
		char val = (_prev_row[col] + _curr_row[col-1] + _curr_row[col+1] + _next_row[col] + (_curr_row[col]*4)) / 8;
		_plate[row][col] = val;
		printf("%d\n", _plate[row][col]);
		//Check for steady state
		if (row == 1);
		else if (row == _length - 2) {
			char new_cell = _plate[row-1][col];

		}
	}

	void calcSteadyStateForEntirePlate() {
		float max_change = 100;
		while (max_change > 0.1) {
			_prev_row = new char[_length];
			_curr_row = new char[_length];
			_next_row = new char[_length];
			memcpy(_prev_row, _plate[0], _length);
			memcpy(_curr_row, _plate[1], _length);
			memcpy(_next_row, _plate[2], _length);
			for (int i = 1; i < _length - 1; i++) {
				for (int j = 1; j < _length - 1; j++) {
					calcSteadyStateForCell(i, j, max_change);
				}
				memcpy(_prev_row, _curr_row, _length);
				memcpy(_curr_row, _next_row, _length);
				memcpy(_next_row, _plate[i+2], _length);
			}
		}
	}

public:
	string toString() {
		stringstream output;
		for (int i = 0; i < _length; i++) {
			for (int j = 0; j < _length; j++) {
				output << (int)_plate[i][j] << "\t";
			}
			output << "\n";
		}
		return output.str();
	}

	Hotplate(int length) {
		_length = length;
		_plate = new char*[_length];

		for (int i = 0; i < _length; i++) {
			char* row = new char[_length];
			for (int j = 0; j < _length; j++) {
				char temp;
				if (i == _length - 1) {
					temp = 100;
				}
				else if (i == 0 || j == 0 || j == _length - 1) {
					temp = 0;
				}
				else {
					temp = 50;
				}
				row[j] = temp;
			}
			_plate[i] = row;
		}
	}

	~Hotplate() {
		for (int i = 0; i < _length; i++) {
			delete _plate[i];
		}
		delete _plate;
	}
};
