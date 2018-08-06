#ifndef FIGHTHANDLER_H
#define FIGHTHANDLER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <GraphicsHandler.h>

class FightHandler
{
    public:
        FightHandler();
        void init();
        const static int xsize = 25;
        const static int ysize = 15;
        char field[xsize][ysize];
        char infoMap[xsize][ysize];
        std::ifstream mapFile;
        void fight(GraphicsHandler &handler);
        bool attack(GraphicsHandler &handler,Entity &player, Entity (&enemy)[4], int x, int y);
        bool pBattle(Entity &player, Entity &enemy, GraphicsHandler &handler);
        std::string pickRandDefence(Entity &enemy);
        sf::Clock updateStep;

    protected:

    private:
};

#endif // FIGHTHANDLER_H
