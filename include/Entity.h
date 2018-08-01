#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


class Entity
{
    public:
        Entity();
        Entity(std::string nam, int healt, int strengt, int spee, int moves, int rang);
        void setPos(int x, int y);
        std::string name;
        int health, strength, xpos, ypos, speed, mov, range;

    protected:

    private:
};

#endif // ENTITY_H
