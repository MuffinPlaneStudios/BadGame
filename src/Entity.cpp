#include <Entity.h>
#include <SFML/Graphics.hpp>



Entity::Entity()
{
    name = "N";
    health = -1;
    strength = -1;
    speed = 0;
    xpos = -1;
    ypos = -1;
}
Entity::Entity(std::string nam, int healt, int strengt, int spee, int moves, int rang)
{
    name = nam;
    health = healt;
    strength = strengt;
    speed = spee;
    mov = moves;
    range = rang;
}
void Entity::setPos(int x, int y)
{
    xpos = x;
    ypos = y;
}
