#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <SFML/Graphics.hpp>
#include <Events.h>
#include <FightHandler.h>
#include <GraphicsHandler.h>


class EventHandler
{
    public:
        EventHandler();
        EventHandler(GraphicsHandler &handler);
        int event(std::string eve);
        FightHandler fhandler;

    protected:

    private:
        std::map<std::string, Events> events;
        void init();
};

#endif // EVENTHANDLER_H
