#include "font.h"
#include "font_manager.h"
#include "renderer.h"

#include <print>

int main()
{
    std::println("---Flyweight Pattern---");

    FontManager fontManager;
    Renderer    renderer(fontManager);

    renderer.drawText("test", "font1");
    renderer.drawText("cat", "font2");
    renderer.drawText("party", "font1");

    return 0;
}
