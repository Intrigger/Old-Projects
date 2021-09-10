#include <iostream>

using namespace std;


void setBit(int &value, int index){
	unsigned int x = 1;
	x <<= index;
	value = value ^ (1 << index);
}

void printBinary(int value){

	unsigned int x = 1;
	x <<= 31;
	for (int i = 0; i < 32; i++){
		
		cout << (((x & value) == 0) ? 0 : 1);
		x >>= 1;
	}

}


int main(){

	union u{
		int i;
		float f;
	};

	u element;
	cout << "Enter integer: ";
	cin >> element.i;
	cout << "Float: " << element.f << endl;
	cout << "Binary form " << element.i << ": ";
	printBinary(element.i);
	cout << endl;


	cout << "Enter bit index to change: ";
	int index;
	cin >> index;

	setBit(element.i, index);

	cout << "Element.i = " << element.i << endl;
	cout << "Float: " << element.f << endl;

	cout << "Binary form " << element.i << ": ";
	printBinary(element.i);
	cout << endl;

	return 0;
}