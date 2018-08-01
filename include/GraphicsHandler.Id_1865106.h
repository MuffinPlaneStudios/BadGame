#ifndef GRAPHICSHANDLER_H
#define GRAPHICSHANDLER_H
#include <SFML/Graphics.hpp>
#include <Map.h>


class GraphicsHandler
{
    public:
        sf::Sprite getSprite(std::string a, int x = 0, int y = 0);
        Map m;
        std::map<std::string, sf::Texture> texts;
        sf::RenderWindow window;
        void init();

    protected:

    private:
        int tcount;

};

#endif // GRAPHICSHANDLER_H
