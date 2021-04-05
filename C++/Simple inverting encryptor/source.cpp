#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>


using namespace std;

void decToBinary(unsigned char value, unsigned  char *temp){
	for (int i = 0; i < 8; i++) temp[i] = 0;
	int current = 7;
	while (value != 0){
		temp[current] = value % 2;
		value /= 2;
		current--;
	}
}

void binaryToDec(unsigned char &value, unsigned char* temp){
	value = 1;
	int c = 0;
	while(temp[c] == 0){
		c += 1;
	}
	c++;
	while (c < 8){
		if (temp[c] == 1) value = value * 2 + 1;
		else value *= 2;
		c++;
	}
}


int main(int argc, char* argv[]){

	setlocale(LC_ALL, "Russian");

	string filename;

	cout << "Simple encoding program by Intrigger\n";

    FILE* inp;

    if (argc != 3){
        cout << "Enter filename: ";
        cin >> filename;
        inp = fopen(filename.c_str(), "rb");
    }

    else{
        for (int i = 0; i < argc; i++){
            cout << "argv[" << i << "] = " << argv[i] << endl;
        }
        inp = fopen(argv[1], "rb");
    }


	vector<unsigned char> s;

	unsigned char symbol;


	while (!feof(inp)){
		s.push_back(getc(inp));
	}
	s.pop_back();
	unsigned char *bin = new unsigned char[s.size() * 8];
	unsigned char *binOrigin = new unsigned char[s.size() * 8];

	unsigned char temp[8];

	for (int i = 0; i < s.size(); i++){
		decToBinary(s[i], temp);
		for (int j = 7; j >= 0; j--){
			bin[j + (s.size() - i - 1) * 8] = temp[7 - j];
		}
		for (int j = 0; j < 8; j++){
			binOrigin[i * 8 + j] = temp[j];
		}
	}

	fclose(inp);

	if (argc == 3) inp = fopen(argv[2], "wb");
    else inp = fopen(filename.c_str(), "wb");

	for (int i = 0; i < s.size(); i++){
		unsigned char value = 0;
		binaryToDec(value, bin + i * 8);
		fwrite(&value, 1, 1, inp);
	}

	fclose(inp);

	return 0;
}
