#include <HSGIL/hsgil.hpp>

int main()
{
    gil::RenderingWindow window01(800, 600, "Window 1");
    gil::RenderingWindow window02(1024, 768, "Window 2");
    if(!(window01.isReady() && window02.isReady()))
    {
        return -1;
    }

    gil::InputHandler inputHandler01;
    gil::InputHandler inputHandler02;
    window01.setInputHandler(inputHandler01);
    window02.setInputHandler(inputHandler02);

    while(window01.isActive() || window02.isActive())
    {
        if(window01.isActive())
        {
            window01.pollEvents();
            window01.swapBuffers();
        }
        if(window02.isActive())
        {
            window02.pollEvents();
            window02.swapBuffers();
        }
    }

    return 0;
}
