#pragma once
#include <string>
class Game;

class FileHandler {
public:
    char FilePath[256];
    bool CheckPath(const std::string& _path);
    FileHandler(Game* _game);
private:
    Game* game;
};



