#pragma once

#include <vector>
#include "Random.h"

#include <fstream>
#include <string>
#include <ctime>

struct Point
{
    float x, y, z;
    Point(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z) {} 
};


struct RandomMap
{
    int seed = 0;
    int step = 0;
    std::vector<Point> buffer;
    std::string seed_origin;
    
    void Init()
    {
        std::ifstream file("src/vendor/pi.txt");
        std::getline(file, seed_origin);
        file.close();
        
        srand((unsigned)std::time(NULL));
        float random =  (float)rand() / RAND_MAX;
        seed = random * seed_origin.size();
        std::cout << "seed: " << seed << std::endl;

        for(int i = seed; i < seed + 5; i++)
            std::cout << "z from first loop: " << seed_origin[i] << std::endl;
        
        for(int y = 0; y < 50; y++)
            for(int x = 0; x < 50; x++)
                {
                    if (seed + step > seed_origin.size())
                        seed = 0;
                    
                    int z = seed_origin[seed + step];
                    std::cout << "z from internal loop: " << z << std::endl;
                    
                    step += 1;
                    Point point(x, y, (float)z);
                    buffer.push_back(point);
                    
                }

    }

};
