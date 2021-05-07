#pragma warning(disable : 4996)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>


namespace MyGraph {

	using namespace std;

	struct list;

	struct Vertex {
		int x;
		int y;
		int color;
		int length;
		list* l;
	};

	struct list {
		Vertex* v;
		list* next;
	};

	void AppendVertex(list*& l, Vertex* v) {
		if (l == nullptr) {
			l = new list;
			l->v = v;
			l->next = nullptr;
		}
		else {
			list* cur = l;
			while (cur->next != nullptr) {
				cur = cur->next;
			}
			cur->next = new list;
			cur = cur->next;
			cur->v = v;
			cur->next = nullptr;
		}
	}

	void PrintList(list* l) {
		int cur = 0;
		while (l != nullptr) {
			printf("[%d][%p] x:%d, y:%d, color:%d, length: %d\n", cur++, l->v ,l->v->x, l->v->y, l->v->color, l->v->length);
			if (l->next != nullptr) l = l->next;
			else break;
		}
	}

	int getListLength(list* l) {
		int length = 0;
		if (l == nullptr) return 0;
		else {
			length = 1;
			while (l->next != nullptr) {
				length++;
				l = l->next;
			}
			return length;
		}
	}

	void deleteFirst(list*& l) {
		if (l == nullptr) return;
		if (getListLength(l) == 1) l = nullptr;
		else {
			list* newL = l->next;
			delete l;
			l = newL;
		}
	}

	bool inList(list* l, Vertex* v) {
		if (l == nullptr) return false;
		while (l->next != nullptr) {
			if (l->v == v) {
				return true;
			}
			l = l->next;
		}
		if (l->v == v) return true;
		return false;
	}

	Vertex* getListElement(list* l, int index){
		while (index--) {
			if (l->next != nullptr) l = l->next;
		}
		return l->v;
	}

	list* ReverseList(list* l) {
		list* newList = nullptr;
		int length = getListLength(l);
		while (length--) {
			AppendVertex(newList, getListElement(l, length ));
		}
		return newList;
	}

	list* solve(const int H, const int W, int** fieldStr, const int startX, const int startY, const int destX, const int destY) {


		printf("StartX: %d\tStartY: %d\nDestX: %d\tDestY: %d\n", startX, startY, destX, destY);

		auto* arr = new Vertex[H * W];

		for (int j = 0; j < H; j++) {
			for (int i = 0; i < W; i++) {
				printf("%d", fieldStr[j][i]);
				if (fieldStr[j][i] != 1) {
					arr[j * W + i] = { i, j, 0, INT32_MAX, nullptr };
				}
			}
			printf("\n");
		}

		list* l = nullptr;

		//Appending the 1-st vertex (starting vertex)
		arr[W * startY + startX].color = 1;
		AppendVertex(l, &arr[W * startY + startX]);


		int listLength = getListLength(l);

		list* current = l;

		for (int i = 0; i < listLength; i++) {
			current = l;
			int curX = current->v->x;
			int curY = current->v->y;
			//top
			if ((curY - 1 >= 0) && (fieldStr[curY - 1][curX] != 1)) {
				if (arr[(curY - 1) * W + curX].color != 2) {
					arr[(curY - 1) * W + curX].color = 1;
					if (!inList(current->v->l, &arr[(curY - 1) * W + curX])) {
						AppendVertex(current->v->l, &arr[(curY - 1) * W + curX]);
					}
					if (!inList(arr[(curY - 1) * W + curX].l, current->v)) {
						AppendVertex(arr[(curY - 1) * W + curX].l, current->v);
					}
					if (!inList(l, &arr[(curY - 1) * W + curX])) {
						AppendVertex(l, &arr[(curY - 1) * W + curX]);
					}
				}
			}
			if ((curY + 1 < H) && (fieldStr[curY + 1][curX] != 1)) {
				if (arr[(curY + 1) * W + curX].color != 2) {
					arr[(curY + 1) * W + curX].color = 1;
					if (!inList(current->v->l, &arr[(curY + 1) * W + curX])) {
						AppendVertex(current->v->l, &arr[(curY + 1) * W + curX]);
					}
					if (!inList(arr[(curY + 1) * W + curX].l, current->v)) {
						AppendVertex(arr[(curY + 1) * W + curX].l, current->v);
					}
					if (!inList(l, &arr[(curY + 1) * W + curX])) {
						AppendVertex(l, &arr[(curY + 1) * W + curX]);
					}
				}
			}
			if ((curX - 1 >= 0) && (fieldStr[curY][curX - 1] != 1)) {
				if (arr[curY * W + (curX - 1)].color != 2) {

					arr[curY * W + (curX - 1)].color = 1;
					if (!inList(current->v->l, &arr[curY * W + (curX - 1)])) {
						AppendVertex(current->v->l, &arr[curY * W + (curX - 1)]);
					}
					if (!inList(arr[curY * W + (curX - 1)].l, current->v)) {
						AppendVertex(arr[curY * W + (curX - 1)].l, current->v);
					}
					if (!inList(l, &arr[curY * W + (curX - 1)])) {
						AppendVertex(l, &arr[curY * W + (curX - 1)]);
					}
				}
			}
			if ((curX + 1 < W) && (fieldStr[curY][curX + 1] != 1)) {
				if (arr[curY * W + (curX + 1)].color != 2) {

					arr[curY * W + (curX + 1)].color = 1;
					if (!inList(current->v->l, &arr[curY * W + (curX + 1)])) {
						AppendVertex(current->v->l, &arr[curY * W + (curX + 1)]);
					}
					if (!inList(arr[curY * W + (curX + 1)].l, current->v)) {
						AppendVertex(arr[curY * W + (curX + 1)].l, current->v);
					}
					if (!inList(l, &arr[curY * W + (curX + 1)])) {
						AppendVertex(l, &arr[curY * W + (curX + 1)]);
					}
				}
			}
			(*current->v).color = 2;
			deleteFirst(l);
			if (i == listLength - 1) {
				i = -1;
				listLength = getListLength(l);
				current = l;
				PrintList(l);
			}
		}


		for (int j = 0; j < H; j++) {
			for (int i = 0; i < W; i++) {
				if (fieldStr[j][i] != 1) {
					arr[j * W + i].color = 0;
				}
			}
		}
		arr[W * startY + startX].color = 1;
		arr[W * startY + startX].length = 0;
		AppendVertex(l, &arr[W * startY + startX]);
		current = l;
		listLength = getListLength(l);
		for (int i = 0; i < listLength; i++) {
			current = l;
			list* cur = current->v->l;
			while (cur != nullptr) {
				(*cur->v).length = min(cur->v->length, current->v->length + 1);
				if ((!inList(l, cur->v)) && (cur->v->color != 2)) {
					AppendVertex(l, cur->v);
				}
				cur = cur->next;
			}

			(*current->v).color = 2;
			deleteFirst(l);
			if (i == listLength - 1) {
				i = -1;
				listLength = getListLength(l);
				current = l;
			}
		}


		for (int j = 0; j < H; j++) {
			for (int i = 0; i < W; i++) {
				printf("%d\t", arr[j * W + i].length);
			}
			printf("\n");
		}

		Vertex* cur = &arr[destY * W + destX];
		list* path = nullptr;
		AppendVertex(path, cur);
		while (cur->length != 0) {
			while (cur->l != nullptr) {
				if (cur->l->v->length == cur->length - 1) {
					AppendVertex(path, cur->l->v);
					cur = cur->l->v;
					break;
				}
				cur->l = cur->l->next;
			}
		}

		printf("Path: \n");
		PrintList(path);

		return ReverseList(path);
	}

}

using namespace std;

struct list {
	int value;
	list* next;
};

class Vector {
private:
	int length;
	list *head = nullptr;
public:
	Vector() {
		length = 0;
	}
	void Append(int value) {
		if (length == 0) {
			head = new list;
			head->value = value;
			head->next = nullptr;
		}
		else {
			list* cur = head;
			while (cur->next != nullptr) {
				cur = cur->next;
			}
			cur->next = new list;
			cur = cur->next;
			cur->value = value;
			cur->next = nullptr;
		}
		length++;
	}
	int getLength() {
		return length;
	}
};


class Game {

private:
	
	vector<std::pair<sf::Texture, sf::Sprite>> maps;

	int WidthPx = 800, HeightPx = 800;
	int FieldWidthElements = 20, FieldHeightElements = 20;
	int CellSizePx = 16;

	int** field = nullptr;

	bool mapCreated = false;


	//Textures
	sf::Texture square_16t;
	sf::Texture menu_background_t;
	sf::Texture menu_startGameButtonT;
	sf::Texture exit_game_t;
	sf::Texture create_map_t;
	sf::Texture map_creator_rightpart_t;
	sf::Texture square_16_selected_t;
	sf::Texture choose_size_background_t;
	sf::Texture red_square16t;
	sf::Texture green_square16t;
	sf::Texture black_square16t;
	sf::Texture viewMapsButtonT;
	sf::Texture backToMenuButtonT;

	//Sprites
	sf::Sprite square_16s;
	sf::Sprite menu_background_s;
	sf::Sprite menu_startGameButtonS;
	sf::Sprite menu_exit_game_s;
	sf::Sprite menu_create_map_s;
	sf::Sprite map_creator_rightpart_s;
	sf::Sprite square_16_selected_s;
	sf::Sprite choose_size_background_s;
	sf::Sprite red_square16s;
	sf::Sprite green_square16s;
	sf::Sprite black_square16s;
	sf::Sprite viewMapsButtonS;
	sf::Sprite backToMenuButtonS;

	//Sounds
	sf::SoundBuffer start_sound_buffer;
	sf::Sound start_sound;


public:

	

	enum { DEFAULT, BLACK, RED, GREEN};
	void loadAllData() {
		square_16t.loadFromFile("Data/Textures/square_16.png");
		square_16s.setTexture(square_16t);

		menu_background_t.loadFromFile("Data/Textures/menu_background.png");
		menu_background_s.setTexture(menu_background_t);

		menu_startGameButtonT.loadFromFile("Data/Textures/start_game.png");
		menu_startGameButtonS.setTexture(menu_startGameButtonT);

		exit_game_t.loadFromFile("Data/Textures/exit_game.png");
		menu_exit_game_s.setTexture(exit_game_t);

		create_map_t.loadFromFile("Data/Textures/create_map.png");
		menu_create_map_s.setTexture(create_map_t);

		start_sound_buffer.loadFromFile("Data/Sounds/start_sound.ogg");
		start_sound.setBuffer(start_sound_buffer);

		map_creator_rightpart_t.loadFromFile("Data/Textures/map_creator_rightpart.png");
		map_creator_rightpart_s.setTexture(map_creator_rightpart_t);

		square_16_selected_t.loadFromFile("Data/Textures/square_16_selected.png");
		square_16_selected_s.setTexture(square_16_selected_t);

		choose_size_background_t.loadFromFile("Data/Textures/choose_size_background.png");
		choose_size_background_s.setTexture(choose_size_background_t);

		red_square16t.loadFromFile("Data/Textures/red_square_16.png");
		red_square16s.setTexture(red_square16t);

		green_square16t.loadFromFile("Data/Textures/green_square_16.png");
		green_square16s.setTexture(green_square16t);


		black_square16t.loadFromFile("Data/Textures/black_square_16.png");
		black_square16s.setTexture(black_square16t);

		viewMapsButtonT.loadFromFile("Data/Textures/viewMapsButton.png");
		viewMapsButtonS.setTexture(viewMapsButtonT);

		backToMenuButtonT.loadFromFile("Data/Textures/back_to_menu.png");
		backToMenuButtonS.setTexture(backToMenuButtonT);

	}

	void GameOperator() {

		sf::Music backgroundMusic;

		backgroundMusic.openFromFile("Data/background_music.ogg");
		backgroundMusic.setLoop(1);


		loadAllData();
		
		backgroundMusic.play();
		sf::RenderWindow window(sf::VideoMode(WidthPx, HeightPx), "Intrigger Labirint v1.0", sf::Style::None);
		window.setPosition(sf::Vector2i(0, 0));

		Menu(window);

	}

	void StartGame(sf::RenderWindow &window) {

		sf::Vector2i redPos;
		sf::Vector2i greenPos;

		int screenWidthPx = 2 + CellSizePx * FieldWidthElements + FieldWidthElements - 1;/*Additional right menu width*/;
		int screenHeightPx = 2 + CellSizePx * FieldHeightElements + FieldHeightElements - 1;

		window.setView(sf::View(sf::FloatRect(0, 0, screenWidthPx, screenHeightPx)));

		window.setSize(sf::Vector2u(screenWidthPx, screenHeightPx));

		for (int j = 0; j < FieldHeightElements; j++) {
			for (int i = 0; i < FieldWidthElements; i++) {
				if (field[j][i] == RED) {
					redPos.x = i;
					redPos.y = j;
				}
				if (field[j][i] == GREEN) {
					greenPos.x = i;
					greenPos.y = j;
				}
			}
			printf("\n");
		}

		int** fieldCopy = new int* [FieldHeightElements];

		for (int j = 0; j < FieldHeightElements; j++) {
			fieldCopy[j] = new int[FieldWidthElements];
			for (int i = 0; i < FieldWidthElements; i++) {
				fieldCopy[j][i] = field[j][i];
			}
		}



		sf::Sprite** blocks = new sf::Sprite * [FieldHeightElements];
		for (int i = 0; i < FieldHeightElements; i++) {
			blocks[i] = new sf::Sprite[FieldWidthElements];
		}
		for (int j = 0; j < FieldHeightElements; j++) {
			for (int i = 0; i < FieldWidthElements; i++) {
				if (fieldCopy[j][i] == DEFAULT) {
					blocks[j][i] = square_16s;
				}
				else if (fieldCopy[j][i] == RED) {
					blocks[j][i] = red_square16s;
				}
				else if (fieldCopy[j][i] == GREEN) {
					blocks[j][i] = green_square16s;
				}
				else if (fieldCopy[j][i] == BLACK) {
					blocks[j][i] = black_square16s;
				}
				blocks[j][i].setPosition(i * 17 + 1, j * 17 + 1);
			}
		}

		MyGraph::list* cur = MyGraph::solve(FieldHeightElements, FieldWidthElements, fieldCopy, redPos.x, redPos.y, greenPos.x, greenPos.y);


		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			window.clear(sf::Color(115, 79, 0));

			if (cur != nullptr) {
				blocks[cur->v->y][cur->v->x].setTexture(green_square16t);
				cur = cur->next;
				sf::sleep(sf::seconds(0.1));
			}

			for (int j = 0; j < FieldHeightElements; j++) {
				for (int i = 0; i < FieldWidthElements; i++) {
					window.draw(blocks[j][i]);
				}
			}

			window.display();
		}

	}

	void ChooseSize(sf::RenderWindow& window) {

		choose_size_background_s.setPosition(0, 0);

		sf::FloatRect WidthMinus(414, 329, 498 - 414, 559 - 477);
		sf::FloatRect WidthPlus(628, 329, 498 - 414, 559 - 477);

		sf::FloatRect HeightMinus(414, 477, 498 - 414, 559 - 477);
		sf::FloatRect HeightPlus(628, 477, 498 - 414, 559 - 477);

		sf::FloatRect NextButton(283, 649, 518 - 283, 758 - 649);

		sf::Text widthText;
		sf::Text heightText;

		widthText.setPosition(414 + 135, 349);
		heightText.setPosition(414 + 135, 349 + 150);

		sf::Font font;
		font.loadFromFile("Data/font.ttf");


		widthText.setFont(font);
		widthText.setFillColor(sf::Color::Black);

		heightText.setFont(font);
		heightText.setFillColor(sf::Color::Black);

		int width = 20, height = 20;

		while (window.isOpen()) {

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			widthText.setString(to_string(width));
			heightText.setString(to_string(height));

			int mouseX = sf::Mouse::getPosition().x - window.getPosition().x;
			int mouseY = sf::Mouse::getPosition().y - window.getPosition().y;


			if (WidthMinus.contains(mouseX, mouseY)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					width = std::max(10, width - 1);
					sf::sleep(sf::Time(sf::seconds(0.2)));
				}
			}
			if (WidthPlus.contains(mouseX, mouseY)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					width = std::min(50, width + 1);
					sf::sleep(sf::Time(sf::seconds(0.2)));
				}
			}

			if (HeightMinus.contains(mouseX, mouseY)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					height = std::max(10, height - 1);
					sf::sleep(sf::Time(sf::seconds(0.2)));
				}
			}
			if (HeightPlus.contains(mouseX, mouseY)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					height = std::min(50, height + 1);
					sf::sleep(sf::Time(sf::seconds(0.2)));
				}
			}

			if (NextButton.contains(mouseX, mouseY)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					FieldWidthElements = width;
					FieldHeightElements = height;
					MapCreator(window);
					return;
				}
			}

			window.clear();
			window.draw(choose_size_background_s);
			window.draw(widthText);
			window.draw(heightText);
			window.display();
		}

	}

	void MapCreator(sf::RenderWindow& window) {


		int screenWidthPx = 2 + CellSizePx * FieldWidthElements + FieldWidthElements - 1 + (300)/*Additional right menu width*/;
		int screenHeightPx = 2 + CellSizePx * FieldHeightElements + FieldHeightElements - 1;

		sf::FloatRect redColor(21 + screenWidthPx - 300, 14, 80 - 21, 80 - 21);
		sf::FloatRect greenColor(87 + screenWidthPx - 300, 14, 80 - 21, 80 - 21);
		sf::FloatRect blackColor(153 + screenWidthPx - 300, 14, 80 - 21, 80 - 21);
		sf::FloatRect defaultColor(219 + screenWidthPx - 300, 14, 80 - 21, 80 - 21);

		sf::FloatRect nextButton(22 + screenWidthPx - 300, 91, 277 - 22, 130 - 91);

		window.setView(sf::View(sf::FloatRect(0, 0, screenWidthPx, screenHeightPx)));

		window.setSize(sf::Vector2u(screenWidthPx, screenHeightPx));

		map_creator_rightpart_s.setPosition(screenWidthPx - 300, 0);

		sf::Sprite** blocks = new sf::Sprite * [FieldHeightElements];

		field = new int* [FieldHeightElements];

		for (int i = 0; i < FieldHeightElements; i++) {
			blocks[i] = new sf::Sprite[FieldWidthElements];
			field[i] = new int[FieldWidthElements];
		}
		for (int j = 0; j < FieldHeightElements; j++) {
			for (int i = 0; i < FieldWidthElements; i++) {
				blocks[j][i] = square_16s;
				blocks[j][i].setPosition(1 + i * (16 + 1), 1 + j * (16 + 1));
				field[j][i] = 0;
			}
		}

		printf("W: %d\tH:%d", screenWidthPx, screenHeightPx);

		string curColor = "";

		bool redUsed = false;
		bool greenUsed = false;

		while (window.isOpen()) {

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			window.clear(sf::Color(115, 79, 0));

			for (int j = 0; j < FieldHeightElements; j++) {
				for (int i = 0; i < FieldWidthElements; i++) {
					blocks[j][i].setPosition(1 + i * (16 + 1), 1 + j * (16 + 1));
					window.draw(blocks[j][i]);
				}
			}

			int currentX = sf::Mouse().getPosition().x - window.getPosition().x;
			int currentY = sf::Mouse().getPosition().y - window.getPosition().y;

			if (redColor.contains(currentX, currentY)) {
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					curColor = "red";
					printf("Now your color is red!\n");
				}
			}
			if (greenColor.contains(currentX, currentY)) {
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					curColor = "green";
					printf("Now your color is green!\n");
				}
			}
			if (blackColor.contains(currentX, currentY)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					curColor = "black";
					printf("Now your color is black!\n");
				}
			}
			if (defaultColor.contains(currentX, currentY)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					curColor = "default";
					printf("Now your color is default!\n");
				}
			}

			if (nextButton.contains(currentX, currentY)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					redUsed = false;
					for (int j = 0; j < FieldHeightElements; j++) {
						for (int i = 0; i < FieldWidthElements; i++) {
							if (field[j][i] == RED) {
								redUsed = true;
							}
						}
					}
					greenUsed = false;
					for (int j = 0; j < FieldHeightElements; j++) {
						for (int i = 0; i < FieldWidthElements; i++) {
							if (field[j][i] == GREEN) {
								greenUsed = true;
							}
						}
					}
					if (greenUsed && redUsed) {
						mapCreated = true;
						sf::Image img = window.capture();
						
						std::pair<sf::Texture, sf::Sprite> p;
						p.first.loadFromImage(img);
						p.second.setTexture(p.first);
						p.second.setTextureRect(sf::IntRect(0, 0, screenWidthPx - 300, screenHeightPx));

						maps.push_back(p);

						return;
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if ((currentX / 17 < FieldWidthElements) and (currentY / 17 < FieldHeightElements)) {
					if (curColor != "") {
						
						if (curColor == "red") {
							redUsed = false;
							for (int j = 0; j < FieldHeightElements; j++) {
								for (int i = 0; i < FieldWidthElements; i++) {
									if (field[j][i] == RED) {
										redUsed = true;
									}
								}
							}
							if (!redUsed) {
								blocks[currentY / 17][currentX / 17].setTexture(red_square16t);
								field[currentY / 17][currentX / 17] = RED;
							}
							
 						}
						if (curColor == "green") {
							greenUsed = false;
							for (int j = 0; j < FieldHeightElements; j++) {
								for (int i = 0; i < FieldWidthElements; i++) {
									if (field[j][i] == GREEN) {
										greenUsed = true;
									}
								}
							}
							if (!greenUsed) {
								blocks[currentY / 17][currentX / 17].setTexture(green_square16t);
								field[currentY / 17][currentX / 17] = GREEN;
							}

						}
						if (curColor == "black") {
							blocks[currentY / 17][currentX / 17].setTexture(black_square16t);
							field[currentY / 17][currentX / 17] = BLACK;
						}
						if (curColor == "default") {
							blocks[currentY / 17][currentX / 17].setTexture(square_16t);
							field[currentY / 17][currentX / 17] = DEFAULT;
						}
					}
				}
			}

			window.draw(map_creator_rightpart_s);
			window.display();
		}

	}

	void ViewMaps(sf::RenderWindow& window) {

		sf::Mouse mouse;

		int startMouseX = mouse.getPosition().x, startMouseY = mouse.getPosition().y;
		int newMouseX, newMouseY;

		vector<sf::Text> names(maps.size());

		for (int i = 0; i < maps.size(); i++) {
			maps[i].second.setTexture(maps[i].first);
			if (i == 0) maps[i].second.setPosition(100, 100);
			else maps[i].second.setPosition(maps[i - 1].second.getPosition() + sf::Vector2f(0, 100 + maps[i-1].second.getTexture()->getSize().y));
		}

		bool wasPressed = false;

		sf::Vector2i mouseStart;

		vector<sf::Vector2f> origins(maps.size());

		for (int i = 0; i < origins.size(); i++) {
			origins[i] = maps[i].second.getPosition();
		}

		sf::FloatRect backToMenuButton = sf::FloatRect(400 - 150, 50, 300, 75);
		backToMenuButtonS.setPosition(backToMenuButton.left, backToMenuButton.top);

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				mouseStart = sf::Mouse::getPosition();
				wasPressed = true;
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				wasPressed = false;
				for (int i = 0; i < origins.size(); i++) {
					origins[i] = maps[i].second.getPosition();
				}
			}

			if (wasPressed) {
				for (int i = 0; i < maps.size(); i++) {
					maps[i].second.setPosition(origins[i] + sf::Vector2f(sf::Mouse::getPosition() - mouseStart));
				}
			}

			newMouseX = mouse.getPosition().x, newMouseY = mouse.getPosition().y;

			menu_background_s.setTextureRect(sf::IntRect(max(0.0, 400 + (startMouseX - newMouseX) * 0.125), max(0.0, 200 + (startMouseY - newMouseY) * 0.125), 800, 800));

			if (event.type == sf::Event::MouseButtonPressed) {
				if (backToMenuButton.contains(sf::Vector2f(sf::Mouse::getPosition() - window.getPosition()))) {
					for (int i = 0; i < origins.size(); i++) {
						origins[i] = maps[i].second.getPosition();
					}
					return;
				}
			}
			
			window.clear();
			window.draw(menu_background_s);
			for (int i = 0; i < maps.size(); i++) {
				window.draw(maps[i].second);
			}

			window.draw(backToMenuButtonS);

			window.display();
		}
	}

	void Menu(sf::RenderWindow& window) {

		menu_background_s.setPosition(0, 0);

		sf::Mouse mouse;

		int startMouseX = mouse.getPosition().x, startMouseY = mouse.getPosition().y;
		int newMouseX, newMouseY;

		sf::IntRect startGameButton = sf::IntRect(400 - 150, 100, 300, 75);
		sf::IntRect exitButton = sf::IntRect(400 - 150, 600, 300, 75);
		sf::IntRect createMap = sf::IntRect(400 - 150, 100 + startGameButton.height + 50, 300, 75);
		sf::IntRect viewMaps = sf::IntRect(400 - 150, 100 + createMap.top + createMap.height, 300, 75);
		//
		menu_startGameButtonS.setPosition(startGameButton.left, startGameButton.top);
		menu_exit_game_s.setPosition(exitButton.left, exitButton.top);
		menu_create_map_s.setPosition(createMap.left, createMap.top);
		viewMapsButtonS.setPosition(viewMaps.left, viewMaps.top);

		sf::Vector2u windowSize = window.getSize();
		sf::Vector2i mousePos;

		while (window.isOpen()) {

			newMouseX = mouse.getPosition().x, newMouseY = mouse.getPosition().y;

			menu_background_s.setTextureRect(sf::IntRect(max(0.0, 400 + (startMouseX - newMouseX) * 0.125), max(0.0, 200 + (startMouseY - newMouseY) * 0.125), 800, 800));

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
			window.clear();
			window.draw(menu_background_s);
			window.draw(menu_startGameButtonS);
			window.draw(menu_exit_game_s);
			window.draw(menu_create_map_s);
			window.draw(viewMapsButtonS);
			window.display();


			if (startGameButton.contains(mouse.getPosition().x  - window.getPosition().x, mouse.getPosition().y - window.getPosition().y)) {
				if (mouse.isButtonPressed(sf::Mouse::Left)) {
					if (mapCreated) {
						StartGame(window);
					}
				}
			}

			if (viewMaps.contains(mouse.getPosition().x - window.getPosition().x, mouse.getPosition().y - window.getPosition().y)) {
				if (mouse.isButtonPressed(sf::Mouse::Left)) {
					ViewMaps(window);
				}
			}


			if (createMap.contains(mouse.getPosition().x - window.getPosition().x, mouse.getPosition().y  - window.getPosition().y)) {
				if (mouse.isButtonPressed(sf::Mouse::Left)) {
					ChooseSize(window);
					window.setView(sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y)));
					window.setSize(windowSize);
				}
				
			}

			if (exitButton.contains(mouse.getPosition().x - window.getPosition().x, mouse.getPosition().y - window.getPosition().y)) {
				if (mouse.isButtonPressed(sf::Mouse::Left)) {
					printf("%d %d\n", mouse.getPosition().x, mouse.getPosition().y);
					return;
				}
			}
		}

	}
};

int main()
{
	Game game;

	game.GameOperator();

	return 0;
}