#ifndef TPOINT_H
#define TPOINT_H

#include <iostream>
#include <string>
#include <unistd.h>

#define WIDTH 41
#define HEIGHT 11

class tPoint
{
private:
    int posX;
    int posY;
    int orientationX;
    int orientationY;
    char field[HEIGHT][WIDTH];
    void print_field(char (*field)[WIDTH]);
    void set_field(char (*field)[WIDTH]);
public:
    tPoint();
    ~tPoint();
    void start(char r);
    int get_posX();
    int get_posY();
    int get_orientationX();
    int get_orientationY();
};

#endif // TPOINT_H