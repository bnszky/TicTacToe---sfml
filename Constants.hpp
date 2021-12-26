const int BORDER_THICKNESS = 6;
const int CELL_SIZE = 128;
const int MARGIN = 10;
const int CELL_SIZE_MARGIN = CELL_SIZE + 2*MARGIN;
const int PIXEL_SIZE = 3*CELL_SIZE_MARGIN + 2*BORDER_THICKNESS;

enum PLAYERS{
    HUMAN, IDIOT, EASY, MEDIUM, IMPOSSIBLE
};

const std::string names[5] = {
    "HUMAN", "IDIOT-BOT", "EASY-BOT", "MEDIUM-BOT", "IMPOSSIBLE-BOT"
};
const float DELAY = 0;