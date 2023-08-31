#pragma once
#include "utils.hpp"
#include <vector>
#include <fstream>
#include <string>

void save(std::vector<point>& observations, std::vector<point>& means, std::ofstream& file)
{
    file << "m:" << '\n';
    file << observations.size() << '\n';
    for (size_t i = 0; i < observations.size(); i++)
    {
        file << observations[i].x << ' ' << observations[i].y << '\n';
    }
    file << "K:" << '\n';
    file << means.size() << '\n';
    for (size_t i = 0; i < means.size(); i++)
    {
        file << means[i].x << ' ' << means[i].y << '\n';
    }
}

void load(std::vector<point>& observations, std::vector<point>& means, std::ifstream& file)
{
    std::string dummy;
    size_t count;
    point temp;

    file >> dummy;
    file >> count;
    for (size_t i = 0; i < count; i++)
    {
        file >> temp.x >> temp.y;
        observations.push_back(temp);
    }

    file >> dummy;
    file >> count;
    for (size_t i = 0; i < count; i++)
    {
        file >> temp.x >> temp.y;
        means.push_back(temp);
    }
}