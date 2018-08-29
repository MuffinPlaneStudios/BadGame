#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


class Entity
{
    public:
        Entity();
        Entity(std::string nam, int healt, int strengt, int def, int pir, int har, int spee, int moves, int rang);
        void setPos(int x, int y);
        std::string name;
        int health, strength, xpos, ypos, speed, mov, range, pierce, hard, defence;
        bool hasMoved, isAlive;
        void attack(Entity &enemy, std::string a, std::string d);

    protected:

    private:
};

#endif // ENTITY_H
