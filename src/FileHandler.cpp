#include "FileHandler.h"
#include <fstream>
#include <string>
#include <filesystem>
#include "Game.h"

//returns true if file found at path
bool FileHandler::CheckPath(const std::string& _path)
{
    std::filesystem::path path(_path);
    // Check if the path exists and is a regular file (not a directory)
    if(_path.find(':') == std::string::npos) {game->AddError("Path does not exist!"); return false;}
    if(exists(path) && std::filesystem::is_regular_file(path))
    {
        game->RemoveError("Path does not exist!");
        return true;
    }
    game->AddError("Path does not exist!");
    return false;
}

FileHandler::FileHandler(Game* _game)
{
    game = _game;
}

