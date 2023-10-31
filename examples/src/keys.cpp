#include <HSGIL/hsgil.hpp>

int main()
{
    gil::RenderingWindow window(800, 600, "Key-Codes Testing");
    if(!window.isReady())
    {
        return -1;
    }

    gil::InputHandler inputHandler;
    window.setInputHandler(inputHandler);

    while(window.isActive())
    {
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
