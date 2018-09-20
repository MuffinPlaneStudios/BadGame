#include <Map.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <Tile.h>
#include <EmptyTile.h>
#include <iostream>
using namespace std;
using namespace sf;


Map::Map()
{
    mapFile.open("Map.txt");
    char mapChar;
    int x = 0;
    int y = 0;
    while(y!=(ysize-1)||x!=xsize)
    {
        mapFile.get(mapChar);
        switch(mapChar)
        {
            case '\n':
                x = 0;
                y++;
                break;
            case '.':
                tmap[x][y] = "BlankTile";
                x++;
                break;
            case '#':
                tmap[x][y] = "TestTile";
                x++;
                break;
            case 'N':
                tmap[x][y] = "NormalTile";
                x++;
                break;
            case 'S':
                tmap[x][y] = "ShopTile";
                x++;
                break;
            case 'R':
                tmap[x][y] = "RandTile";
                x++;
                break;
            case 'Z':
                tmap[x][y] = "RestTile";
                x++;
                break;
            case 'B':
                tmap[x][y] = "BossTile";
                x++;
                break;
            case '?':
                tmap[x][y] = "MysteryTile";
                x++;
                break;
            default:
                tmap[x][y] = "SHOULDNOT";
                x++;
                break;
        }
        cout<<mapChar;
        if(y==(ysize-1)&&x==(xsize-1)) {
            mapFile.close();
        }
    }
}
string Map::enter(int x, int y)
{
    return tmap[x][y];
}
