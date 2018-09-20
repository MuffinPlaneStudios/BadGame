#include <Tile.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
//Parent class for tiles

Tile::Tile()
{
    ID = "BlankTile";
}

Tile::Tile(string name)
{
    ID = name;
}

string Tile::enter()
{
    cout<<"NO";
    return "NO";
}
