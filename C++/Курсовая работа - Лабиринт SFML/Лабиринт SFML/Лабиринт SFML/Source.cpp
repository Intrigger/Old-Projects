#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;

class Game {

private:
    int WidthPx = 800, HeightPx = 800;
    int FieldWidthElements = 50, FieldHeightElements = 50;
    int CellSizePx = 16;

    //Textures
    sf::Texture square_16t;
    sf::Texture menu_background_t;
    sf::Texture menu_startGameButtonT;
    sf::Texture exit_game_t;
    sf::Texture create_map_t;

    //Sprites
    sf::Sprite square_16s;
    sf::Sprite menu_background_s;
    sf::Sprite menu_startGameButtonS;
    sf::Sprite exit_game_s;
    sf::Sprite create_map_s;

    //Sounds
    sf::SoundBuffer start_sound_buffer;
    sf::Sound start_sound;
    

public:

    void loadData() {
        square_16t.loadFromFile("Data/Textures/square_16.bmp");
        square_16s.setTexture(square_16t);
               
        menu_background_t.loadFromFile("Data/Textures/menu_background.png");
        menu_background_s.setTexture(menu_background_t);

        menu_startGameButtonT.loadFromFile("Data/Textures/start_game.png");
        menu_startGameButtonS.setTexture(menu_startGameButtonT);

        exit_game_t.loadFromFile("Data/Textures/exit_game.png");
        exit_game_s.setTexture(exit_game_t);
        
        create_map_t.loadFromFile("Data/Textures/create_map.png");
        create_map_s.setTexture(create_map_t);

        start_sound_buffer.loadFromFile("Data/Sounds/start_sound.ogg");
        start_sound.setBuffer(start_sound_buffer);

    }

    void Menu() {
        loadData();

        start_sound.play();

        menu_background_s.setPosition(0, 0);
        sf::RenderWindow window(sf::VideoMode(WidthPx, HeightPx), "Intrigger Labirint v1.0");

        window.getDefaultView();

        sf::Mouse mouse;

        int startMouseX = mouse.getPosition().x, startMouseY = mouse.getPosition().y;
        int newMouseX, newMouseY;

        sf::IntRect startGameButton = sf::IntRect(400 - 150, 100, 300, 75);
        sf::IntRect exitButton = sf::IntRect(400 - 150, 600, 300, 75);
        sf::IntRect createMap = sf::IntRect(400 - 150, 100 + startGameButton.height + 50, 300, 75);
        //
        menu_startGameButtonS.setPosition(startGameButton.left, startGameButton.top);
        exit_game_s.setPosition(exitButton.left, exitButton.top);
        create_map_s.setPosition(createMap.left, createMap.top);

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
            window.draw(exit_game_s);
            window.draw(create_map_s);
            window.display();

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

    game.Menu();

    return 0;
}