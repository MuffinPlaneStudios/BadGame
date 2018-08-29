#include <Entity.h>
#include <SFML/Graphics.hpp>
using namespace std;

Entity::Entity()
{
    name = "N";
    health = -1;
    strength = -1;
    speed = 0;
    xpos = -1;
    ypos = -1;
    hasMoved = true;
    isAlive = false;
}
Entity::Entity(string nam, int healt, int strengt, int def, int pir, int har, int spee, int moves, int rang)
{
    name = nam;
    health = healt;
    strength = strengt;
    speed = spee;
    mov = moves;
    range = rang;
    hasMoved = false;
    pierce = pir;
    hard = har;
    defence = def;
    isAlive = true;
}
void Entity::setPos(int x, int y)
{
    xpos = x;
    ypos = y;
}
void Entity::attack(Entity &enemy, string a, string d)
{
    double mult = 1;
    bool bbreak = false;
    if(pierce>enemy.hard)
    {
        bbreak = true;
    }
    if(a == "DL")
    {
        if(d == "DL")
        {
            mult = .25;
        } else if(d == "L")
        {
            mult = .5;
        } else if(d == "UL")
        {
            mult = 1;
        } else if(d == "D")
        {
            mult = 1.5;
        } else if(d == "U")
        {
            mult = 0;
        } else if(d == "R")
        {
            mult = 1.1;
        }
    } else if(a == "L")
    {
        if(d == "DL")
        {
            mult = .25;
        } else if(d == "L")
        {
            mult = .5;
        } else if(d == "UL")
        {
            mult = 1;
        } else if(d == "D")
        {
            mult = 1.5;
        } else if(d == "U")
        {
            mult = 0;
        } else if(d == "R")
        {
            mult = 1.1;
        }
    }
}
