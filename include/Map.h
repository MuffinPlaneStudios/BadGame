#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <Tile.h>

class Map
{
    public:
        Map();
        std::string enter(int x, int y);
        static const int xsize = 16;
        static const int ysize = 16;
        std::string tmap[xsize][ysize];

    protected:

    private:
        std::ifstream mapFile;
};

#endif // MAP_H
