#pragma once
#include <string>
class Game;

class FileHandler {
public:
    char FilePath[256];
    bool CheckPath(const std::string& _path);
    bool OutputText(std::string& lineout);
    FileHandler(Game* _game);
private:
    Game* game;
};



