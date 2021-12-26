#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "Field.hpp"

#define umin(a, b) (a)=min((a), (b))

Field::Field(){

if(!X.loadFromFile("Graphics/X.png")){
    std::cerr << "Couldn't load X.png\n";
}
if(!O.loadFromFile("Graphics/O.png")){
    std::cerr << "Couldn't load O.png\n";
}

arr.resize(3);
line.resize(3);
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++) {arr[i].push_back(0); line[i].push_back(0);}
}

}

void Field::reset(){

nextMove = true;
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++) {arr[i][j] = 0; line[i][j] = 0;}
}

}

void Field::draw(sf::RenderWindow& i_window){

sf::RectangleShape cell(sf::Vector2f(CELL_SIZE_MARGIN, CELL_SIZE_MARGIN));
cell.setFillColor(sf::Color(255, 255, 255));
i_window.clear(sf::Color(0,0,0));

for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        cell.setPosition(sf::Vector2f(i * (CELL_SIZE_MARGIN + BORDER_THICKNESS), j * (CELL_SIZE_MARGIN + BORDER_THICKNESS)));
        cell.setFillColor(sf::Color(255, 255, 255));
        if(line[i][j]) cell.setFillColor(sf::Color(255, 0, 0));
        i_window.draw(cell);
    }
}

cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        cell.setPosition(sf::Vector2f(i * (CELL_SIZE_MARGIN + BORDER_THICKNESS) + MARGIN, 
                                      j * (CELL_SIZE_MARGIN+BORDER_THICKNESS) + MARGIN));
        if(arr[i][j] != 0){
            if(arr[i][j] ==  1) cell.setTexture(&X);
            if(arr[i][j] == -1) cell.setTexture(&O);
            i_window.draw(cell);
        }
    }
}

i_window.display();

}

sf::Vertex Field::comp_mid(int x, int y){
    return {
        sf::Vector2f(CELL_SIZE_MARGIN/2 + x*(CELL_SIZE_MARGIN + BORDER_THICKNESS), 
        CELL_SIZE_MARGIN/2 + y*(CELL_SIZE_MARGIN + BORDER_THICKNESS)), 
        sf::Color(255, 0, 0)
    };
}

bool Field::fast_check(int x1, int y1, int x2, int y2){

int x3 = (x1+x2)/2;
int y3 = (y1+y2)/2;
if(arr[x1][y1] == arr[x3][y3] and arr[x3][y3] == arr[x2][y2] and arr[x1][y1] != 0){
    line[x1][y1] = line[x2][y2] = line[x3][y3] = 1;
    return true;
}
return false;

}

bool Field::check_win(){

for(int i = 0; i < 3; i++){
    if(fast_check(i, 0, i, 2)) return true;
    if(fast_check(0, i, 2, i)) return true;
}
if(fast_check(0,0, 2,2)) return true;
if(fast_check(2,0, 0,2)) return true;

return false;
}

bool Field::check_draw(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++) if(arr[i][j] == 0) return false;
    }
    return true;
}

int Field::move(std::pair<int,int> point){

int x = point.first;
int y = point.second;

if(x < 0 or x >= 3 or y < 0 or y>=3) {
    std::cerr << "Player " << !nextMove + 1 << " " << "makes an incorrect move!\n"; 
    std::cerr << "x = " << x << " or y = " << y << " coordinate is outside the array\n";
    exit(0);
}

if(arr[x][y] == 0){
    arr[x][y] = ((nextMove) ? 1 : -1);
    if(check_win()) return !nextMove + 1; 
    if(check_draw()) return 3;
    nextMove = !nextMove;
}  
else {
std::cerr << "Player " << !nextMove + 1 << " " << "makes an incorrect move!\n";
std::cerr << "This cell is already taken: " << x << " " << y << "\n";
exit(0);
}
return 0;

}