#include <att85/ssd1306/display.hpp>

using namespace att85::ssd1306;

int main() {
    display_128x32<> disp;
    disp.commands([](auto&& disp) {
        disp.inverse();
        disp.contrast(1);
        disp.on();
    });
}
