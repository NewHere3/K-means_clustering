#pragma once
#include <time.h>
#include "constants.hpp"


inline void msleep(int mseconds)
{
    struct timespec request = { mseconds/1000, (mseconds%1000)*1000000};
    nanosleep(&request, NULL);
}

struct point
{
    unsigned long color = CIRCLE_COLOR;
    size_t cluster = 0;
    short int x = 0;
    short int y = 0;
};