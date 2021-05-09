#include <iostream>
#include <cstring>
#include <string>


using namespace std;


class LongNumber {


public:
	char* number = nullptr;
	LongNumber() {
		number = new char[2];
		number[0] = 0;
		number[1] = -1;
	}
	LongNumber(const char* str) {
		unsigned int lengthInput = strlen(str);
		number = new char[lengthInput + 1];
		number[lengthInput] = -1;
		for (int i = 0; i < lengthInput; i++) {
			number[i] = str[lengthInput - 1 - i] - 48;
		}
		  
	}
	

	void print() {
		int length = getLength();
		for (int i = length - 1; i >= 0; i--) {
			printf("%d", number[i]);
		}
	}

	unsigned int getLength() {
		int i = 0;
		while (number[i] != -1) {
			i++;
		}
		i -= 1;
		while ((i > 0) and (number[i] == 0)) {
			i--;
		}

		return i + 1;
	}



	char& operator[](unsigned int index) {
		if (index < this->getLength()) {
			printf("ok!\n");
			return number[index];
		}
		else {
			char* newNumber = new char[index + 2];
			memcpy(newNumber, number, this->getLength());
			memset(newNumber + this->getLength(), 0, index + 1 - this->getLength());
			newNumber[index + 1] = -1;
			delete this->number;
			this->number = newNumber;
			printf("not ok!\n");
			return number[index];
		}
	}

	const char* getString() {
		return (const char*)number;
	}

};

int compare(LongNumber n1, LongNumber n2) {
	if (n1.getLength() < n2.getLength()) return 1;
	if (n1.getLength() > n2.getLength()) return 2;
	if (n1.getLength() == n2.getLength()) {
		for (int i = n1.getLength() - 1; i >= 0; i--) {
			if (n1[i] > n2[i]) return 2;
			if (n1[i] < n2[i]) return 1;
		}
	}
	return 0;
}

LongNumber substract(LongNumber n1, LongNumber n2) {
	cout << "\nsubstract\n";
	LongNumber max, min;
	if (compare(n1, n2) == 2) {
		max = n1;
		min = n2;
	}
	else{
		max = n2;
		min = n1;
	}

	cout << endl;
	LongNumber res;
	res[max.getLength() - 1] = 0;

	cout << "max: ";
	max.print();
	cout << endl << "min: ";
	min.print();
	cout << endl;

	cout << max.getLength() - 1 << endl;
	cout << int(max[max.getLength() - 1]) << endl;
	cout << int(min[max.getLength() - 1]) << endl;

	for (int i = 0; i < max.getLength(); i++) {
		cout << "max[" << i << "] = " << int(max[i]) << endl;
		cout << "min[" << i << "] = " << int(min[i]) << endl;
		if (max[i] >= min[i]) {
			res[i] = max[i] - min[i];
		}
		else {
			if ((i + 1 < max.getLength()) and (max[i + 1] == 0)) {
				int start = i + 1;
				while ((start < max.getLength()) and (max[start] == 0)) {
					max[start] = 9;
					start++;
				}
				max[start] -= 1;
			}
			else {
				max[i + 1] -= 1;
			}
			max[i] += 10;
			res[i] = max[i] - min[i];
		}
	}
	
	return res;
}

LongNumber MUL_Nk_N(LongNumber n, unsigned int k) {
	cout << "\nMUL_Nk_N\n";
	LongNumber result;
	result[n.getLength() + k - 1] = 0;
	for (int i = 0; i < k; i++) {
		result[i] = 0;
	}
	int nLen = n.getLength();
	for (int i = k; i < k + nLen; i++) {
		result[i] = n[i - k];
	}
	return result;
}

int DIV_NN_Dk(LongNumber n1, LongNumber n2, int& K) {
	LongNumber newN1;
	cout << "\DIV_NN_Dk\n";
	newN1[n2.getLength() - 1] = 0;
	for (int i = 0; i < n2.getLength(); i++) {
		newN1[i] = n1[n1.getLength() - n2.getLength() + i];
	}
	if (compare(newN1, n2) == 1) {
		newN1[n2.getLength()] = 0;
		for (int i = 0; i < n2.getLength() + 1; i++) {
			newN1[i] = n1[n1.getLength() - n2.getLength() - 1 + i];
		}
	}

	K = n1.getLength() - newN1.getLength();
	int counter = 0;
	while (compare(newN1, n2) != 1) {
		newN1 = substract(newN1, n2);
		counter++;
	}
	return counter;
}

LongNumber MUL_ND_N(LongNumber n, unsigned int d) {
	cout << "\nMUL_ND_N\n";
	LongNumber res;
	res[n.getLength()] = 0;
	int additional = 0;
	for (int i = 0; i < n.getLength(); i++) {
		res[i] = (n[i] * d + additional) % 10;
		additional = (n[i] * d + additional) / 10;
	}
	res[n.getLength()] = additional;

	return res;
}

LongNumber SUM_NN_N(LongNumber n1, LongNumber n2) {
	cout << "\nSUM_NN_N\n";
	LongNumber max, min;
	if (compare(n1, n2) == 2) {
		max = n1;
		min = n2;
	}
	else {
		max = n2;
		min = n1;
	}
	LongNumber res;
	res[max.getLength()] = 0;
	int additional = 0;
	for (int i = 0; i < max.getLength(); i++) {
		res[i] = (max[i] + min[i] + additional) % 10;
		additional = (max[i] + min[i] + additional) / 10;
	}
	res[max.getLength()] = additional;

	return res;

}

LongNumber DIV_NN_N(LongNumber n1, LongNumber n2) {
	cout << "\nDIV_NN_N\n";
	LongNumber result;
	LongNumber temp;
	LongNumber temp2;
	while (compare(n1, n2) != 1) {
		int K = 0;
		int counter = DIV_NN_Dk(n1, n2, K);
		cout << "counter: " << counter << endl;
		
		cout << "k: " << K << endl;

		delete temp.number;
		temp = MUL_Nk_N(MUL_ND_N(n2, counter), K);
		delete temp2.number;
		temp2 = LongNumber(to_string(counter).c_str());
		result = SUM_NN_N(result, MUL_Nk_N(temp2, K));

		cout << "to substract: ";
		n1.print();
		cout << " ";
		temp.print();
		cout << endl;
		n1 = substract(n1, temp);
		cout << "n1: ";
		n1.print();
		cout << "\n";
	}

	return result;
}

int main() {

	LongNumber l1("1000000000000000000000000");
	LongNumber l2("2000");
	
	DIV_NN_N(l1, l2).print();


	return 0;
}
