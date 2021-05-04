#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>


using namespace std;

class Game {

private:
    int WidthPx = 800, HeightPx = 800;
    int FieldWidthElements = 30, FieldHeightElements = 30;
    int CellSizePx = 16;

    //Textures
    sf::Texture square_16t;
    sf::Texture menu_background_t;
    sf::Texture menu_startGameButtonT;
    sf::Texture exit_game_t;
    sf::Texture create_map_t;
    sf::Texture map_creator_rightpart_t;

    //Sprites
    sf::Sprite square_16s;
    sf::Sprite menu_background_s;
    sf::Sprite menu_startGameButtonS;
    sf::Sprite menu_exit_game_s;
    sf::Sprite menu_create_map_s;
    sf::Sprite map_creator_rightpart_s;

    //Sounds
    sf::SoundBuffer start_sound_buffer;
    sf::Sound start_sound;
    

public:

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

    }

    void GameOperator() {

        loadAllData();
        start_sound.play();
        sf::RenderWindow window(sf::VideoMode(WidthPx, HeightPx), "Intrigger Labirint v1.0");

        Menu(window);

    }

    void MapCreator(sf::RenderWindow &window) {


        int screenWidthPx = 2 + CellSizePx * FieldWidthElements + FieldWidthElements - 1 + (300)/*Additional right menu width*/;
        int screenHeightPx = screenWidthPx - 300;


        window.setView(sf::View(sf::FloatRect(0, 0, screenWidthPx, screenHeightPx)));

        window.setSize(sf::Vector2u(screenWidthPx, screenHeightPx));

        map_creator_rightpart_s.setPosition(screenHeightPx, 0);

        sf::Sprite** blocks = new sf::Sprite * [FieldHeightElements];
        for (int i = 0; i < FieldHeightElements; i++) {
            blocks[i] = new sf::Sprite[FieldWidthElements];
        }
        for (int j = 0; j < FieldHeightElements; j++) {
            for (int i = 0; i < FieldWidthElements; i++) {
                blocks[j][i] = square_16s;
                blocks[j][i].setPosition(1 + i * (16 + 1), 1 + j * (16 + 1));
            }
        }
        
        
        printf("W: %d\tH:%d", screenWidthPx, screenHeightPx);



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
                    window.draw(blocks[j][i]);
                }
            }
            window.draw(map_creator_rightpart_s);
            window.display();
        }

    }

    void Menu(sf::RenderWindow &window) {

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

            if (startGameButton.contains(mouse.getPosition().x - 4 - window.getPosition().x, mouse.getPosition().y - 32 - window.getPosition().y)) {
                if (mouse.isButtonPressed(sf::Mouse::Left)) {
                    //
                    //TODO START GAME
                    //
                }
            }

            if (createMap.contains(mouse.getPosition().x - 4 - window.getPosition().x, mouse.getPosition().y - 32 - window.getPosition().y)) {
                if (mouse.isButtonPressed(sf::Mouse::Left)) {
                    MapCreator(window);
                }
            }

            if (exitButton.contains(mouse.getPosition().x - 4 - window.getPosition().x, mouse.getPosition().y - 32 -  window.getPosition().y)) {
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