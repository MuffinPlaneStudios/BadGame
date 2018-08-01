#include <Event.h>
using namespace std;
//BlankEvent
Event::Event()
{
    name = "BlankEvent";
}
Event::Event(string nam)
{
    name = nam;
}

bool Event::dew()
{
    return true;
}
