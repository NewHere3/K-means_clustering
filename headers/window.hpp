#pragma once
#include <X11/Xlib.h>
#include <vector>
#include "../headers/utils.hpp"

struct MyWindow
{
    Display *display;
    int screen;
    Window win;
    GC gc;
    unsigned long black, white, red, green, blue;

    MyWindow();
    ~MyWindow();
    void show();
    void hide();
    void clear();
    void process_events(std::vector<point>& observations, std::vector<point>& means);
    void draw(std::vector<point>& observations, std::vector<point>& means);
    void connect(std::vector<point>& observations, std::vector<point>& means);
};

/*
    unsigned long colors[40] = {0x00ffff, 0xa52a2a, 0xe3d2cf, 0xcfe0e3, 0xc2d6dc, 0xc2d1ad, 0x5d478b, 0xe32636,
                                0x5d8aa8, 0x550551, 0x00ced1, 0x420420, 0xff4040, 0xff1493, 0xdb4648, 0xffff99,
                                0xfff68f, 0x7e2f47, 0x5d2747, 0xbada55, 0xfaa05e, 0xfa8b44, 0xfb9553, 0xe57374,
                                0xed9587, 0xf0c87b, 0xeab05e, 0xe48160, 0xde5262, 0x9fcdb0, 0x0a1509, 0xcc99cc,
                                0x05131c, 0x282010, 0x260e0c, 0x59c757, 0x2e8a57, 0x224f22, 0xa254d5, 0x4d2864};
*/