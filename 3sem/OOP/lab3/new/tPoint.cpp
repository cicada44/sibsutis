#include "tPoint.hpp"

void tPoint::start(char r) 
{
    this->posX = WIDTH / 2;
    this->posY = HEIGHT / 2;
    while (true) {
        set_field(this->field);
        print_field(this->field);
        this->posX += orientationX;
        this->posY += orientationY;
        if (this->posX == WIDTH - 2 || this->posX == 1) 
            this->orientationX *= -1;
        if (this->posY == HEIGHT - 2 || this->posY == 1) 
            this->orientationY *= -1;
        sleep(1);
        system("clear");
    }
}

void tPoint::print_field(char (*field)[WIDTH]) 
{
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << field[i][j];
        }
        std::cout << std::endl;
    }
}

void tPoint::set_field(char (*field)[WIDTH]) 
{
    for (int i = 1; i < HEIGHT - 1; ++i) {
        for (int j = 1; j < WIDTH - 1; ++j) {
            field[i][j] = j == posX && i == posY ? '*' : ' ';
        }
    }
}

int tPoint::get_posX() 
{
    return this->posX;
}

int tPoint::get_posY()
{
    return this->posY;
}

int tPoint::get_orientationX() 
{
    return this->orientationX;
}

int tPoint::get_orientationY() 
{
    return this->orientationY;
}

tPoint::tPoint()
{
    this->posX = rand() % WIDTH;
    this->posY = rand() % HEIGHT;
    int rtmp = rand() % 101;
    orientationX = rtmp <= 50 ? 1 : -1;
    orientationY = rtmp >= 50 ? 1 : -1;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) 
                this->field[i][j] = '#';
            else 
                this->field[i][j] = ' ';
        }
    }
}

tPoint::~tPoint()
{
    this->posY = this->posX = 0;
}