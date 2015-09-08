#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Hotplate {
private:
	float** _plate;
	int _length;
	
	class SteadyStateCreater {
	private:
		float** _plate;
		int _length;
		float* _prev_row;
		float* _curr_row;
		float* _next_row;
		float _max_change;

		void calcMaxDiffForCell(int row, int col) {
			 _max_change = max(_max_change, (float)abs(_plate[row][col] - (_plate[row-1][col] + _plate[row][col-1] + _plate[row][col+1] + _plate[row+1][col])/4));
		}

		void calcNewCellValue(int row, int col) {
			float val = (_prev_row[col] + _curr_row[col-1] + _curr_row[col+1] + _next_row[col] + (_curr_row[col]*4)) / 8;
			_plate[row][col] = val;
			cout << (int)val << "\t";
			//Check for steady state
			if (row == 1);
			else if (row > 1 && row < _length-2) {
				calcMaxDiffForCell(row-1, col);
			}
			if (row == _length-2) {
				if (col == 1);
				else if (col > 1 && col < _length-2) {
					calcMaxDiffForCell(row, col-1);
				}
				if (col == _length - 2) {
					calcMaxDiffForCell(row, col);
				}
			}
		}

	public:
		SteadyStateCreater(float** plate, int length) {
			_plate = plate;
			_length = length;
			float max_change = 100;
			_prev_row = new float[_length];
			_curr_row = new float[_length];
			_next_row = new float[_length];
		}

		~SteadyStateCreater() {
			delete _prev_row;
			delete _curr_row;
			delete _next_row;
		}

		void createSteadyState() {
			int steps = 0;
			while (_max_change > 0.1 && steps < 100) {
				steps++;
				_max_change = 0;
				memcpy(_curr_row, _plate[0], _length);
				memcpy(_next_row, _plate[1], _length);
				for (int i = 1; i < _length-1; i++) {
					memcpy(_prev_row, _curr_row, _length);
					memcpy(_curr_row, _next_row, _length);
					memcpy(_next_row, _plate[i+1], _length);
					for (int j = 1; j < _length-1; j++) {
						calcNewCellValue(i, j);
					}
					cout << "\n";
				}
				cout << "Max diff: " << setprecision(3) << _max_change << "\n";
			}
			cout << "Steps: " << steps << "\n";
		}
	};

public:
	string toString(string separater) {
		stringstream output;
		for (int i = 0; i < _length; i++) {
			for (int j = 0; j < _length; j++) {
				output << (int)_plate[i][j] << separater;
			}
			output << "\n";
		}
		return output.str();
	}

	string toString() {
		return toString("\t");
	}

	void printToFile(string fileName) {
		ofstream outfile;
		outfile.open(fileName);
		outfile << toString(", ");
		outfile.close();
	}

	Hotplate(int length) {
		_length = length;
		_plate = new float*[_length];

		for (int i = 0; i < _length; i++) {
			float* row = new float[_length];
			for (int j = 0; j < _length; j++) {
				float temp;
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

	void createSteadyState() {
		SteadyStateCreater creater(_plate, _length);
		creater.createSteadyState();
	}
};
