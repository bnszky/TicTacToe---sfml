#include <iostream>
#include <SFML/Graphics.hpp>
#include "Field.hpp"
#include "Constants.hpp"
#include "Game.hpp"

int main(){

srand(time(NULL));

sf::RenderWindow window(sf::VideoMode(PIXEL_SIZE, PIXEL_SIZE), "TicTacToe in sfml");
Game game(IMPOSSIBLE, MEDIUM, window);

while(window.isOpen()){
    sf::Event event;

    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::R){
                game.restart();
            }
        }
        if(event.type == sf::Event::MouseButtonReleased){
            if(event.mouseButton.button == sf::Mouse::Left){
                int mouse_x = sf::Mouse::getPosition(window).x / (CELL_SIZE_MARGIN + BORDER_THICKNESS/2);
                int mouse_y = sf::Mouse::getPosition(window).y / (CELL_SIZE_MARGIN + BORDER_THICKNESS/2);
                game.make_move(mouse_x, mouse_y);
            }
        }
    }
}

}