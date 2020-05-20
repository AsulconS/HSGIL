#include <HSGIL/hsgil.hpp>

int main()
{
    gil::Window window(800, 600, "Key-Codes Testing");
    if(!window.isReady())
    {
        return -1;
    }

    gil::EventHandler defaultEventHandler;
    window.setEventHandler(defaultEventHandler);

    while(window.isActive())
    {
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
