#include <vector>
#include <random>
#include "Bot.hpp"

#define tab std::vector<std::vector<int>>

namespace BOT{

bool check(tab arr){
    for(int i = 0; i < 3; i++){
        if(arr[i][0] == arr[i][1] and arr[i][1] == arr[i][2] and arr[i][0] != 0) return true;
        if(arr[0][i] == arr[1][i] and arr[1][i] == arr[2][i] and arr[2][i] != 0) return true;
    }
    if(arr[0][0] == arr[1][1] and arr[1][1] == arr[2][2] and arr[0][0] != 0) return true;
    if(arr[2][0] == arr[1][1] and arr[1][1] == arr[0][2] and arr[1][1] != 0) return true;
    return false;
}

bool check_draw(tab arr){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++) if(arr[i][j] == 0) return false;
    }
    return true;
}

int best_move_rec(tab arr, int who, int depth){

    int best_move_val = -1;
    depth --;
    if(depth >= 0)
    for(int a = 0; a < 3; a++){
        for(int b = 0; b < 3; b++){
            if(arr[a][b] == 0){
                arr[a][b] = who;
                best_move_val = std::max(best_move_val, best_move_rec(arr, ((who == 1) ? -1 : 1), depth));
                arr[a][b] = 0;
            }
        }
    }
    if(best_move_val != 0) best_move_val = ((best_move_val == -1) ? 1 : -1);
    if(depth < 0) best_move_val = -1;
    if(check_draw(arr)) best_move_val = 0;
    if(check(arr)) best_move_val = 1;
    return best_move_val;
}

namespace IDIOT{

std::pair<int,int> find_move(tab arr){

int counter = 0; 
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++) if(arr[i][j] == 0) counter++; 
}

int place = rand()%counter;
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++) if(arr[i][j] == 0) {
        if(place == 0) return {i, j};
        else place --;
    }
}


}

}

namespace EASY{

std::pair<int,int> find_move(tab arr, int who){

for(int a = 0; a < 3; a++){
    for(int b = 0; b < 3; b++){
        if(arr[a][b] == 0) {
            arr[a][b] = who;
            if(check(arr)) return {a, b};
            arr[a][b] = 0;
        }
    }
}

for(int a = 0; a < 3; a++){
    for(int b = 0; b < 3; b++){
        if(arr[a][b] == 0) {
            arr[a][b] = ((who == 1) ? -1 : 1);
            if(check(arr)) return {a, b};
            arr[a][b] = 0;
        }
    }
}

if(arr[1][1] == 0) return {1,1};

return IDIOT::find_move(arr);

}

}

namespace MEDIUM{

std::pair<int,int> improve_rand_result(tab arr, int a, int b, int who, int *opt_val, std::pair<int,int> opt, int depth){

        if(arr[a][b] == 0) {
            arr[a][b] = who;
            int best_move_val = best_move_rec(arr, ((who == 1) ? -1 : 1), depth);
            if(best_move_val > *opt_val or (best_move_val == *opt_val and rand()%2)){
              *opt_val = best_move_val;
              opt = {a,b};  
            }
            arr[a][b] = 0;
        }
        return opt;

}  

std::pair<int,int> find_move(tab arr, int who, int depth){

bool flag = true;
for(int a = 0; a < 3; a++){
    for(int b = 0; b < 3; b++) if(arr[a][b] != 0) flag = false;  
}
if(flag) return {1,1};

std::pair<int,int> opt1;
int opt_val1 = -2;

opt1 = improve_rand_result(arr, 1, 1, who, &opt_val1, opt1, depth);

std::pair<int,int> opt2;
int opt_val2 = -2;
for(int a = 0; a < 3; a+=2){
    opt2 = improve_rand_result(arr, a, 0, who, &opt_val2, opt2, depth);
    opt2 = improve_rand_result(arr, a, 2, who, &opt_val2, opt2, depth);
}

std::pair<int,int> opt3;
int opt_val3 = -2;
for(int a = 0; a < 3; a++){
    for(int b = 0; b < 3; b++){
        opt3 = improve_rand_result(arr, a, b, who, &opt_val3, opt3, depth);
    }
}

int opt_val = std::max(std::max(opt_val1, opt_val2), opt_val3);
if(opt_val == opt_val1) return opt1;
if(opt_val == opt_val2) return opt2;
if(opt_val == opt_val3) return opt3;

}

}

namespace IMPOSSIBLE{

std::pair<int,int> improve_result(tab arr, int a, int b, int who, int *opt_val, std::pair<int,int> opt, int depth){

        if(arr[a][b] == 0) {
            arr[a][b] = who;
            int best_move_val = best_move_rec(arr, ((who == 1) ? -1 : 1), depth);
            if(best_move_val > *opt_val){
              *opt_val = best_move_val;
              opt = {a,b};  
            }
            arr[a][b] = 0;
        }
        return opt;

}

std::pair<int,int> find_move(tab arr, int who, int depth){

bool flag = true;
for(int a = 0; a < 3; a++){
    for(int b = 0; b < 3; b++) if(arr[a][b] != 0) flag = false;  
}
if(flag) return {1,1};

std::pair<int,int> opt;
int opt_val = -2;

opt = improve_result(arr, 1, 1, who, &opt_val, opt, depth);

for(int a = 0; a < 3; a+=2){
    opt = improve_result(arr, a, 0, who, &opt_val, opt, depth);
    opt = improve_result(arr, a, 2, who, &opt_val, opt, depth);
}

for(int a = 0; a < 3; a++){
    for(int b = 0; b < 3; b++){
        opt = improve_result(arr, a, b, who, &opt_val, opt, depth);
    }
}

return opt;
  
}

}


}