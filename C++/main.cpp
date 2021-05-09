#include <iostream>
#include <cstring>

using namespace std;


class LongNumber{
private:
	char* number = nullptr;
public:
	LongNumber(){
		number = new char[2];
		number[0] = 0;
		number[1] = -1;
	}
	LongNumber(const char* str){
		unsigned int lengthInput = strlen(str);
		number = new char[lengthInput + 1];
		number[lengthInput] = -1;
		for (int i = 0; i < lengthInput; i++) {
            number[i] = str[lengthInput - 1 - i] - 48;
        }
	}

	void print(){
		int length = getLength();
		for (int i = length-1; i >= 0; i--){
			printf("%d", number[i]);
		}
	}

	unsigned int getLength(){
		int i = 0;
		while (number[i] != -1){
			i++;
		}
		i -= 1;
		while ((i > 0) and (number[i] == 0)){
		    i--;
		}

		return i + 1;
	}

	char& operator[](unsigned int index){
	    if (index < this->getLength()){
            return number[index];
	    }
	    else{
	        char* newNumber = new char[index + 2];
	        memcpy(newNumber, number, this->getLength());
	        memset(newNumber + this->getLength(), 0, index + 1 - this->getLength());
	        newNumber[index + 1] = -1;
	        delete number;
	        number = newNumber;
	        return number[index];
	    }
	}
};

int compare(LongNumber n1, LongNumber n2){
    if (n1.getLength() < n2.getLength()) return 1;
    if (n1.getLength() > n2.getLength()) return 2;
    if (n1.getLength() == n2.getLength()){
        for (int i = n1.getLength() -  1; i >= 0; i--){
            if (n1[i] > n2[i]) return 2;
            if (n1[i] < n2[i]) return 1;
        }
    }
    return 0;
}

LongNumber substract(LongNumber n1, LongNumber n2){
    LongNumber max, min;
   if (compare(n1, n2) == 2){
       max = n1;
       min = n2;
   }
   else if (compare(n1, n2) == 1){
       max = n2;
       min = n1;
   }
   else{
       return LongNumber("0");
   }

   LongNumber res;
   res[max.getLength() - 1] = 0;
   for (int i = 0; i < max.getLength(); i++){
       if (max[i] >= min[i]){
           res[i] = max[i] - min[i];
       }
       else{
           if (res[i + 1] == 0){
               int start = i + 1;
               while (max[start] == 0){
                   max[start] = 9;
                   start++;
               }
           }
           max[i + 1] -= 1;
           max[i] += 10;
           res[i] = max[i] - min[i];
       }
   }
   return res;
}

LongNumber MUL_N

LongNumber divide(LongNumber n1, LongNumber n2){

}

int main(){

	LongNumber l1("90");
	LongNumber l2("9");

	cout << "Result: ";
	divide(l1, l2).print();


	return 0;
}