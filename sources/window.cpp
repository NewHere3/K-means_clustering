#include "../headers/window.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "../headers/utils.hpp"
#include "../headers/constants.hpp"
#include "../headers/save_and_load.hpp"

#include <iostream>

MyWindow::MyWindow()
{
    display=XOpenDisplay(NULL);
    screen=DefaultScreen(display);
    black=BlackPixel(display, screen);
    white=WhitePixel(display, screen);
    red=0xff0000;
    green=0x00ff00;
    blue=0x0000ff;
    win=XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 5, white, black);
    XSetStandardProperties(display, win, "Howdy", NULL, None, NULL, 0, NULL);
    XSelectInput(display, win, ButtonPressMask | KeyPressMask);
    gc=XCreateGC(display, win, 0,0);
    XSetBackground(display,gc,white);
    XSetForeground(display,gc,black);
    XClearWindow(display, win);
    XFlush(display);
}

void MyWindow::show()
{
    XMapRaised(display, win);
    XFlush(display);
}

void MyWindow::hide()
{
    XUnmapWindow(display, win);
    XFlush(display);
}

MyWindow::~MyWindow()
{
    XFreeGC(display, gc);
    XDestroyWindow(display, win);
    XCloseDisplay(display);
}

void MyWindow::process_events(std::vector<point>& observations, std::vector<point>& means)
{
    XEvent event;
    std::ifstream load_file(LOAD_FILE);
    std::ofstream save_file(SAVE_FILE);
    while (1)
    {
        XNextEvent(display, &event);

        if(event.type==ButtonPress)         // left button == 1 ;; middle button == 2 ;; right button == 3
        {
            point p;
            p.x=event.xbutton.x, p.y=event.xbutton.y;

            if(event.xkey.keycode == 1)
            {
                observations.push_back(p);
            } else if(event.xkey.keycode == 2)
            {
                break;
            } else if (event.xkey.keycode == 3)
            {
                XSetForeground(display,gc,white);
                XFillArc(display, win, gc, p.x-(OUTLINE_SIZE/2), p.y-(OUTLINE_SIZE/2), OUTLINE_SIZE, OUTLINE_SIZE, 0, 360*64);
                means.push_back(p);
            }
            XSetForeground(display,gc,CIRCLE_COLOR);
            XFillArc(display, win, gc, p.x-(CIRCLE_SIZE/2), p.y-(CIRCLE_SIZE/2), CIRCLE_SIZE, CIRCLE_SIZE, 0, 360*64);
            XFlush(display);
        }


        if(event.type==KeyPress)
        {
            std::cout << event.xkey.keycode << std::endl;
            if(event.xkey.keycode ==9)
            {
                load_file.close();
                save_file.close();
                exit(1);
            } else if (event.xkey.keycode == 39)
            {
                save(observations, means, save_file);
            } else if (event.xkey.keycode == 46)
            {
                load(observations, means, load_file);
                draw(observations, means);
            }
        }
    }
    load_file.close();
    save_file.close();
}

void MyWindow::draw(std::vector<point>& observations, std::vector<point>& means)
{
    XClearWindow(display, win);
    for(size_t i = 0; i < observations.size(); i++)
    {
        XSetForeground(display,gc,observations[i].color);
        XFillArc(display, win, gc, observations[i].x-(CIRCLE_SIZE/2), observations[i].y-(CIRCLE_SIZE/2), CIRCLE_SIZE, CIRCLE_SIZE, 0, 360*64);
    }
    for(size_t i = 0; i < means.size(); i++)
    {
        XSetForeground(display,gc,white);
        XFillArc(display, win, gc, means[i].x-(OUTLINE_SIZE/2), means[i].y-(OUTLINE_SIZE/2), OUTLINE_SIZE, OUTLINE_SIZE, 0, 360*64);
        XSetForeground(display,gc,means[i].color);
        XFillArc(display, win, gc, means[i].x-(CIRCLE_SIZE/2), means[i].y-(CIRCLE_SIZE/2), CIRCLE_SIZE, CIRCLE_SIZE, 0, 360*64);
    }

    XFlush(display);
}

void MyWindow::clear()
{
    XClearWindow(display, win);
}

void MyWindow::connect(std::vector<point>& observations, std::vector<point>& means)
{
    for (size_t i = 0; i < means.size(); i++)
    {
        for (size_t j = 0; j < observations.size(); j++)
        {
            if(observations[j].cluster==i)
            {
                XSetForeground(display,gc,means[i].color);
                XDrawLine(display,win,gc,means[i].x,means[i].y,observations[j].x,observations[j].y);
            }
        }
    }
    XFlush(display);
}