#include <iostream>
#include <vector>
#include <unistd.h>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Bot.hpp"
#include "Game.hpp"
#include "Constants.hpp"
#include "Field.hpp"

#define pii pair<int,int>

Game::Game(int player1, int player2, sf::RenderWindow& window) : players({player1, player2}), i_window(window){restart();}

void Game::restart(){

reset();
second_player = false;
block = false;
draw(i_window);
bot_move();

}

void Game::bot_move(){
    if(players[second_player] == HUMAN or block) return;
    block = true;

    //Timer
    float timer = 0;
    sf::Clock clock;
    while(timer < DELAY){
    float time = clock.getElapsedTime().asSeconds();
    timer+=time;
    clock.restart();
    }
    //

    switch(players[second_player]){
        case IDIOT:
            check_result(move(BOT::IDIOT::find_move(arr)));
        break;
        case EASY:
            check_result(move(BOT::EASY::find_move(arr, ((second_player) ? -1 : 1))));
        break;
        case MEDIUM:
            check_result(move(BOT::MEDIUM::find_move(arr, ((second_player) ? -1 : 1), 3)));
        break;
        case IMPOSSIBLE:
            check_result(move(BOT::IMPOSSIBLE::find_move(arr, ((second_player) ? -1 : 1), 100)));
        break;
    }

    second_player = !second_player;
    draw(i_window);
    bot_move();
    
}

void Game::make_move(int x, int y){
    if(!block){
        if(x < 0 and x >= 3 and y < 0 and y >= 3) return;
        if(arr[x][y] != 0) return;
        check_result(move({x, y}));
        second_player = !second_player;
        draw(i_window);
        bot_move();
    }
}

void Game::check_result(int res){
    if(res == 0) {block = false; return;}
    if(res == 3) std::cout << "Draw! [" << names[players[0]] << " vs " << names[players[1]] << "] \n";
    else std::cout << "Player " << res <<  " [" << names[players[res-1]] << 
    "] won with Player " << ((res%2) + 1) << " [" << names[players[res%2]] << "] !\n";
    block = true;
    return;
}