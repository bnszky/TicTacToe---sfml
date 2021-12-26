export DISPLAY=:0.0
g++ -c main.cpp
g++ main.o -o sfml-game -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-window Field.cpp Game.cpp Bot.cpp
./sfml-game