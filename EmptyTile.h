#ifndef EMPTYTILE_H
#define EMPTYTILE_H
#include <SFML/Graphics.hpp>
#include <Tile.h>


class EmptyTile : public Tile
{
    public:
        EmptyTile(std::string name);
        std::string enter();

    protected:

    private:
};

#endif // EMPTYTILE_H
