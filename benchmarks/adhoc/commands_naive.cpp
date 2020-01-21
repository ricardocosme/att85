#include <att85/ssd1306/display.hpp>

using namespace att85::ssd1306;

int main() {
    display_128x32<> disp;
    //When we have a sequence of commands to be sent we can use
    //disp.commands() to a better performance. The approach below is
    //inneficient because we're starting and ending a command context
    //for each command to be sent. With disp.commands() we can reuse a
    //single command context to send all the commands.
    disp.inverse();
    disp.contrast(1);
    disp.on();
}
