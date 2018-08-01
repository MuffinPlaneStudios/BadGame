#ifndef EVENTS_H
#define EVENTS_H
#include <stdlib.h>
#include <SFML/Graphics.hpp>

class Events
{
    public:
        Events();
        Events(std::string eve, int i);
        std::string name;
        int ID;
        bool dew();
    protected:

    private:
};

#endif // EVENTS_H
