#pragma once 

class Field{

std::vector<std::vector<bool>> line;
sf::Texture X;
sf::Texture O;
bool nextMove;
sf::Vertex comp_mid(int,int);
bool fast_check(int,int,int,int);
bool check_win();
bool check_draw();

protected:
    std::vector<std::vector<int>> arr;

public:
    Field();
    void draw(sf::RenderWindow&);
    int move(std::pair<int,int>);
    void reset();
};