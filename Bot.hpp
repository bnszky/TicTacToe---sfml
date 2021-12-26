namespace BOT{
    bool check(std::vector<std::vector<int>>);
    bool check_draw(std::vector<std::vector<int>>);
    int best_move_rec(std::vector<std::vector<int>>, int, int);
    namespace IDIOT{
        std::pair<int,int> find_move(std::vector<std::vector<int>>);
    };
    namespace EASY{
        std::pair<int,int> find_move(std::vector<std::vector<int>>, int);
    };
    namespace MEDIUM{
        std::pair<int,int> improve_rand_result(std::vector<std::vector<int>>, int, int, int, int*, std::pair<int,int>, int);
        std::pair<int,int> find_move(std::vector<std::vector<int>>, int, int);
    };
    namespace IMPOSSIBLE{
        std::pair<int,int> improve_result(std::vector<std::vector<int>>, int, int, int, int*, std::pair<int,int>, int);
        std::pair<int,int> find_move(std::vector<std::vector<int>>, int, int);
    };
};