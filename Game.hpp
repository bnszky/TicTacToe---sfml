#pragma once
#include "Field.hpp"

class Game : public Field{

int players[2];
bool second_player;
bool block;
sf::RenderWindow& i_window;
void bot_move();
void check_result(int);

public:
    Game(int, int, sf::RenderWindow&);
    void make_move(int,int);
    void restart();
};