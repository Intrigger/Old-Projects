#include <iostream>
#include <conio.h>

using namespace std;

namespace MyDLL {
	struct dll {
		int value;
		dll* next;
		dll* prev;
	};

	int getLength(dll* head) {
		int length = 0;
		while (head != nullptr) {
			head = head->next;
			length++;
		}
		return length;
	}

	void append(dll*& head, int value) {
		if (getLength(head) == 0) {
			head = new dll;
			head->prev = nullptr;
			head->value = value;
			head->next = nullptr;
		}
		else {
			dll* lastNotZero = head;
			dll* current = head;
			while (current != nullptr) {
				lastNotZero = current;
				current = current->next;
			}
			current = new dll;
			lastNotZero->next = current;
			current->prev = lastNotZero;
			current->value = value;
			current->next = nullptr;
		}
	}

	void print(dll* head) {
		while (head != nullptr) {
			printf("%d ", head->value);
			head = head->next;
		}
	}

	void deleteFromTo(dll*& head, int from, int to) { //[from; to]
		int length = getLength(head);
		if (from < 0) {
			cerr << "\"From\" index below zero!";
			return;
		}
		if (to > length - 1) {
			cerr << "\"To\" index too large!";
			return;
		}

		if (from > to) {
			swap(from, to);
		}

		if (from == 0) {

			int currentIndex = 0;
			while (currentIndex != to + 1) {
				dll* prev = head;
				head = head->next;
				delete prev;
				currentIndex++;
			}

			return;
		}

		//finding from
		int currentIndex = 0;
		dll* fromDLL = head;
		while (currentIndex != from) {
			fromDLL = fromDLL->next;
			currentIndex++;
		}
		
		dll* fromDLLprev = fromDLL->prev;
		
		dll* toDLL = fromDLL;
		while (currentIndex != to) {
			toDLL = toDLL->next;
			currentIndex++;
		}

		toDLL = toDLL->next;

		while (fromDLL != toDLL) {
			dll* prev = fromDLL;
			fromDLL = fromDLL->next;
			delete prev;
		}

		if (fromDLLprev != nullptr) {
			fromDLLprev->next = toDLL;
			if (toDLL != nullptr) toDLL->prev = fromDLLprev;
		}
		else {
			head = toDLL;
		}
	}

	void insertTo(dll*& head, int to, int* values, int size) {
		int current = 0;
		
		dll* leftDLL = head;
		if ((to > getLength(head)) || (to < 0)) {
			cerr << "Wrong \"to\" index!\n";
			return;
		}

		while (current < to - 1) {
			current++;
			leftDLL = leftDLL->next;
		}
		dll* rightDLL = leftDLL->next;
		if (to == 0) {
			rightDLL = head;
			leftDLL = new dll;
			head = leftDLL;
			leftDLL->prev = nullptr;
			leftDLL->value = values[0];
			for (int i = 1; i < size; i++) {
				leftDLL->next = new dll;
				leftDLL->next->prev = leftDLL;
				leftDLL = leftDLL->next;
				leftDLL->value = values[i];
			}
		}
		else {
			for (int i = 0; i < size; i++) {
				leftDLL->next = new dll;
				leftDLL->next->prev = leftDLL;
				leftDLL = leftDLL->next;
				leftDLL->value = values[i];
			}
		}
		
		leftDLL->next = rightDLL;
		
	}

	bool compare(dll* x1, dll* x2) {
		return x1->value > x2->value;
	}

	void sortAscending(dll*& head) {
		int length = getLength(head);
		dll* headCopy;
		for (int i = 0; i < length - 1; i++) {
			headCopy = head;
			for (int j = 0; j < length - 1 - i; j++) {
				if (headCopy->value > headCopy->next->value) {
					swap(headCopy->value, headCopy->next->value);
				}
				headCopy = headCopy->next;
			}
		}
	}

	void sortDescending(dll*& head) {
		int length = getLength(head);
		dll* headCopy;
		for (int i = 0; i < length - 1; i++) {
			headCopy = head;
			for (int j = 0; j < length - 1 - i; j++) {
				if (headCopy->value < headCopy->next->value) {
					swap(headCopy->value, headCopy->next->value);
				}
				headCopy = headCopy->next;
			}
		}
	}

}

int main(){

	setlocale(LC_ALL, "Russian");

	MyDLL::dll* head = nullptr;


	printf("Length: %d\n", MyDLL::getLength(head));

	for (int i = 0; i < 100; i++) {
		MyDLL::append(head, i + 1);
	}

	printf("Length: %d\n", MyDLL::getLength(head));

	cout << "\nList: \n";
	MyDLL::print(head);

	//MyDLL::deleteFromTo(head, 1, 4);
	//cout << "\nList: \n";
	//MyDLL::print(head);


	int* arr = new int[5];
	for (int i = 0; i < 5; i++) arr[i] = i + 1;

	
	MyDLL::sortDescending(head);
	cout << "\nList: \n";
	MyDLL::print(head);

	MyDLL::sortAscending(head);
	cout << "\nList: \n";
	MyDLL::print(head);

	bool exit = false;

	int curMenu = 0;

#define menuSize 8
	string menu[menuSize];
	menu[0] = "Создать элемент";
	menu[1] = "Удалить элемент";
	menu[2] = "Вывод длины списка";
	menu[3] = "Сортировка по возрастанию";
	menu[4] = "Сортировка по убыванию";
	menu[5] = "Добавить несколько элементов";
	menu[6] = "Удалить в диапазоне";
	menu[7] = "Выход";

	while (!exit) {

		system("cls");

		cout << "Список: \n";
		MyDLL::print(head);
		cout << "\n\n";

		for (int i = 0; i < menuSize; i++) {
			if (i == curMenu) printf("-->");
			else printf("   ");
			cout << " " << i << "). " << menu[i] << endl;
		}


		int c = _getch();
		if (c == 224) {
			c = _getch();
		}
#define TOP 72
#define BOT 80
#define ENTER 13
		
		if (c == TOP) {
			curMenu -= 1;
			if (curMenu < 0) curMenu = menuSize - 1;
		}
		if (c == BOT) {
			curMenu = (curMenu + 1) % menuSize;
		}
		if (c == ENTER){
			int value = 0;
			if (curMenu == 0) {

				cout << "Введите значение: ";
				value = 0;
				while (!(cin >> value)) {
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "Попробуйте снова: ";
				}

				MyDLL::append(head, value);
			}
			if (curMenu == 1) {
				cout << "Введите значение: ";
				value = 0;
				while (!(cin >> value)) {
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "Попробуйте снова: ";
				}
				MyDLL::deleteFromTo(head, value, value);
			}
			if (curMenu == 2) {
				cout << "Длина списка: " << MyDLL::getLength(head) << endl;
				_getch();
			}
			if (curMenu == 3) {
				MyDLL::sortAscending(head);
			}
			if (curMenu == 4) {
				MyDLL::sortDescending(head);
			}
			if (curMenu == 5) {
				int size = 0;

				cout << "Введите количество добавляемых чисел: ";

				while (!(cin >> size) || (size <= 0)) {
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "Попробуйте снова: ";
				}

				int* values = new int[size];
				for (int i = 0; i < size; i++) {
					printf("Введите значение №%d:", i + 1);
					while (!(cin >> values[i])) {
						cin.clear();
						cin.ignore(32767, '\n');
						printf("Попробуйте ввести значение №%d снова: ", i + 1);
					}
				}

				value = 0;
				printf("Введите, куда вставить элементы: ");
				while (!(cin >> value)) {
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "Попробуйте снова: ";
				}

				MyDLL::insertTo(head, value, values, size);
				delete[] values;

			}
			if (curMenu == 6) {
				cout << "Введите значения для удаления [от; до]: ";
				int from, to;
				while (!(cin >> from)) {
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "Попробуйте снова: ";
				}
				while (!(cin >> to)) {
					cin.clear();
					cin.ignore(32767, '\n');
					cout << "Попробуйте снова: ";
				}

				MyDLL::deleteFromTo(head, from, to);
			}
			if (curMenu == 7) {
				exit = true;
			}
		}
	}

	return 0;
}