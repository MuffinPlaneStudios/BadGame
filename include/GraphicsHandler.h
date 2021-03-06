#ifndef GRAPHICSHANDLER_H
#define GRAPHICSHANDLER_H
#include <SFML/Graphics.hpp>
#include <Map.h>
#include <Entity.h>


class GraphicsHandler
{
    public:
        sf::Sprite getSprite(std::string a, int x = 0, int y = 0);
        Map m;
        std::map<std::string, sf::Texture> texts;
        sf::RenderWindow &getWindow();
        void updateMap(int xpos, int ypos);
        void init();
        void loadAttack(std::string charName, char slot);
        void drawBattleMap(char field[25][15]);
        void updateBattle(int state, int moves[2],char infoMap[25][15], int mov, char field[25][15], int xpos, int ypos, Entity party[4], Entity enemy[4]);
        void updateAttack(Entity enemy[4], int selection);
        void updateBattle(char infoMap[25][15],char field[25][15], Entity party[4], Entity enemy[4], int selection);

    protected:

    private:
        int tcount;

};

#endif // GRAPHICSHANDLER_H
