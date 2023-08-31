#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdint.h>
#include <stdlib.h>
#include <sstream>
#include "headers/window.hpp"
#include "headers/utils.hpp"
#include "headers/constants.hpp"

void pick_colors(std::vector<point>& means, unsigned long colors[])
{
    if(means.size()>26) {std::cout << "too many means, not enough colors" << std::endl; exit(1);}
    for (size_t i = 0; i < means.size(); i++)
    {
        means[i].color = colors[i];
    }
}


bool brains(MyWindow& win, std::vector<point>& observations, std::vector<point>& means)
{
    for (size_t i = 0; i < observations.size(); i++)
    {
        size_t distance = SIZE_MAX;
        for (size_t j = 0; j < means.size(); j++)
        {
            size_t temp = sqrt( (observations[i].x-means[j].x) * (observations[i].x-means[j].x) + 
                                (observations[i].y-means[j].y) * (observations[i].y-means[j].y) );
            if(temp < distance)
            {
                distance = temp;
                observations[i].cluster = j;
                observations[i].color = means[j].color;
            }
        }
    }

    win.draw(observations, means);

    size_t maches = 0;

    for (size_t i = 0; i < means.size(); i++)
    {
        size_t count = 0, x = 0, y = 0;

        for (size_t j = 0; j < observations.size(); j++)
        {
            if(observations[j].cluster==i)
            {
                count++;
                x+=observations[j].x;
                y+=observations[j].y;
            }
        }

        if(count == 0)
        {
            means[i].x = rand() % (WINDOW_WIDTH - 10) + 5;
            means[i].y = rand() % (WINDOW_HEIGHT - 10) + 5;
        } else
        {
            size_t new_x = x/count;
            size_t new_y = y/count;
            if(means[i].x == new_x && means[i].y == new_y)
            { maches++; }
            means[i].x = new_x;
            means[i].y = new_y;
        }
    }
    msleep(1000);
    return maches == means.size();
}



int main()
{
    MyWindow win;
    win.show();
    unsigned long colors[26] = {0xff0000, 0xfffb00, 0x00ff51, 0x00a2ff, 0x9d00ff, 0xff0059,
                                0xff4400, 0xd4ff00, 0x00ff84, 0x007bff, 0xbf00ff,
                                0xff7300, 0xaeff00, 0x00ffb7, 0x002aff, 0xe600ff,
                                0xff9900, 0x6fff00, 0x00fffb, 0x4800ff, 0xff00e1,
                                0xffc400, 0x00ff08, 0x00ccff, 0x7700ff, 0xff00b7};
    std::vector<point> observations;
    std::vector<point> means;

    win.process_events(observations, means);

    pick_colors(means, colors);

    while(1)
    {
        if(brains(win, observations, means))
        { break; }
    }
    std::cout << "done" << std::endl;

    msleep(1000);
    std::stringstream txt;
    txt << "maim --hidecursor -i " << win.win << " ./assets/$(date +%s).png";
    system(txt.str().c_str());
    msleep(1000);
    win.connect(observations, means);

    msleep(1000);
    system(txt.str().c_str());
    msleep(1000);
    return 0;
}