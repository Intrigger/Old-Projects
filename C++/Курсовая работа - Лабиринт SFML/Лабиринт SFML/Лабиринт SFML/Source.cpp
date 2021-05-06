#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>



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

	//Sounds
	sf::SoundBuffer start_sound_buffer;
	sf::Sound start_sound;


public:

	

	enum { DEFAULT, RED, GREEN, BLACK };
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
			for (int i = 0; i < FieldWidthElements; i++) {
				fieldCopy[j][i] = field[j][i];
			}
		}


		system("pause");
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

	void Menu(sf::RenderWindow& window) {

		menu_background_s.setPosition(0, 0);

		sf::Mouse mouse;

		int startMouseX = mouse.getPosition().x, startMouseY = mouse.getPosition().y;
		int newMouseX, newMouseY;

		sf::IntRect startGameButton = sf::IntRect(400 - 150, 100, 300, 75);
		sf::IntRect exitButton = sf::IntRect(400 - 150, 600, 300, 75);
		sf::IntRect createMap = sf::IntRect(400 - 150, 100 + startGameButton.height + 50, 300, 75);
		//
		menu_startGameButtonS.setPosition(startGameButton.left, startGameButton.top);
		menu_exit_game_s.setPosition(exitButton.left, exitButton.top);
		menu_create_map_s.setPosition(createMap.left, createMap.top);

		sf::Vector2u windowSize = window.getSize();

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
			window.display();

			if (startGameButton.contains(mouse.getPosition().x  - window.getPosition().x, mouse.getPosition().y - window.getPosition().y)) {
				if (mouse.isButtonPressed(sf::Mouse::Left)) {
					if (mapCreated) {
						StartGame(window);
					}
				}
			}

			if (createMap.contains(mouse.getPosition().x - window.getPosition().x, mouse.getPosition().y  - window.getPosition().y)) {
				if (mouse.isButtonPressed(sf::Mouse::Left)) {
					ChooseSize(window);
					//MapCreator(window);
					
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