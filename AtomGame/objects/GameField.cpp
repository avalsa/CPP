//
// Created by sl on 06.04.17.
//

#include <ctime>
#include <cstdlib>
#include "GameField.h"

GameField::GameField(int width, int height): GameObject(), width_(width), height_(height)
{
    srand(time(0));
    field_ = new char* [height_];
    for (int i = 0; i < height_; i++)
        field_[i] = new char [width_];
    for (int i = 0; i < height_; ++i)
        for (int j = 0; j < width_; ++j) {
            field_[i][j] = 0;           //for ex 0 - emplty block

            if (abs(rand()) < 100000000)
                field_[i][j] = 1;       //1 - wall, etc,, and so on
        }
}

int GameField::getWidth() const {
    return width_;
}

int GameField::getHeight() const {
    return height_;
}

char GameField::getCell(int x, int y) {
    return field_[x][y];
}
