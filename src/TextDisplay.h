#pragma once
#include "FileHandler.h"

class TextDisplay
{
public:
    TextDisplay(FileHandler _fh);
    void DisplayText();
private:
    FileHandler fileHandler;
};