#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

#include "glm/gtx/compatibility.hpp"

#include "Random.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#define MAP_HEIGHT 0
#define X_DIMENSION 10
#define Z_DIMENSION 10

#define SCALE 1.5

struct Point
{
    float x, y, z;
    unsigned int index;
    Point(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z) {} 
};

struct VertexInfo
{
    float x, y, z;
};

static float real_y_position(float y)
{
    float value = y;
    y = y * SCALE;
    y = y + MAP_HEIGHT;

    return y;
}

// returns 0 if theres no such point
static bool find_from_coords(std::vector<Point> points ,Point point_to_test)
{
    for (Point p : points)
        if (p.x == point_to_test.x && p.z == point_to_test.z)
            return 1;
    
    return 0;
}

static Point find_point(std::vector<Point> points, float x, float z)
{
    for (Point p : points)
        if (p.x == x && p.z == z)
            return p;
    std::cout  << "(Method: find_point - RandomMap.h)Couldnt find point with given coords" << std::endl;
}

// standart inverse lerp..
static float inverse_lerp(float value, float min, float max)
{
    float val = (value - min) / (max - min);
    return val;
}


struct RandomMap
{
    int seed = 0;
    int step = 0;
    float scale = SCALE;
    std::vector<Point> buffer;
    std::vector<VertexInfo> vertices;
    std::vector<unsigned int> indices;
    std::string seed_origin;

    // render data
    unsigned int vao;
    VertexBuffer* vb = nullptr;
    VertexBufferLayout layout;
    VertexArray* va = nullptr;
    IndexBuffer* ib = nullptr;

    
    void Init()
    {
        std::ifstream file("src/vendor/pi.txt");
        std::getline(file, seed_origin);
        file.close();

        layout.Push<float>(3);
        
        Recalc();

    }

    void Recalc()
    {
        //clear
        buffer.erase(buffer.begin(), buffer.begin() + buffer.size());
        vertices.erase(vertices.begin(), vertices.begin() + vertices.size());
        indices.erase(indices.begin(), indices.begin() + indices.size());
        seed = 0;
        step = 0;


        srand((unsigned)std::time(NULL));
        float random = (float)rand() / RAND_MAX;
        random = random - Random::Float();
        random = glm::abs(random);
        seed = random * seed_origin.size();
        std::cout << "seed: " << seed << std::endl;

        float difference = 0.5f;

        unsigned int index0;
        unsigned int index1;
        unsigned int index2;
        unsigned int index3;


        for (int z = 0; z < Z_DIMENSION; z++)
            for (int x = 0; x < X_DIMENSION; x++)
            {
                if (seed + step > seed_origin.size())
                    seed = 0;

                // do the 4 points
                //  *--*
                //  |  |
                //  *--*
                // increase value, so that I get random value for each
                // point(vertex)

                // FILLING THE ARRAY UP, NOW THERE ARENT ANY DUPLICATES!



                float y = (char)seed_origin[seed + step] - '0';
                Point point = Point(x - difference, real_y_position(y), z - difference);
                if (!find_from_coords(buffer, point))
                {
                    point.index = step;
                    buffer.push_back(point);
                    index0 = step;
                    step += 1;
                }
                else
                {
                    index0 = find_point(buffer, point.x, point.z).index;
                }

                y = (char)seed_origin[seed + step] - '0';
                point = Point(x - difference, real_y_position(y), z + difference);
                if (!find_from_coords(buffer, point))
                {
                    point.index = step;
                    buffer.push_back(point);
                    index1 = step;
                    step += 1;
                }
                else
                {
                    index1 = find_point(buffer, point.x, point.z).index;
                }

                y = (char)seed_origin[seed + step] - '0';
                point = Point(x + difference, real_y_position(y), z + difference);
                if (!find_from_coords(buffer, point))
                {
                    point.index = step;
                    buffer.push_back(point);
                    index2 = step;
                    step += 1;
                }
                else
                {
                    index2 = find_point(buffer, point.x, point.z).index;
                }

                y = (char)seed_origin[seed + step] - '0';
                point = Point(x + difference, real_y_position(y), z - difference);
                if (!find_from_coords(buffer, point))
                {
                    point.index = step;
                    buffer.push_back(point);
                    index3 = step;
                    step += 1;
                }
                else
                {
                    index3 = find_point(buffer, point.x, point.z).index;
                 }

                //add normal triangles here to render and do the "hard ones" later? 
                indices.push_back(index0);
                indices.push_back(index1);
                indices.push_back(index2);
                indices.push_back(index2);
                indices.push_back(index3);
                indices.push_back(index0);

            }
        // find maximum values (so that u can transform all vertex info into values
        // from 0 to 1
        float min_x = 0 - difference;
        float max_x = X_DIMENSION - difference;
        float min_z = 0 - difference;
        float max_z = Z_DIMENSION - difference;
        float min_y = real_y_position(0);
        float max_y = real_y_position(9);

        //fill the "vertices" with bufferData

        for (Point p : buffer)
        {
            VertexInfo vertex;
            vertex.x = inverse_lerp(p.x, min_x, max_x) * 2.0f - 1.0f;
            vertex.y = inverse_lerp(p.y, min_y, max_y) * 2.0f - 1.0f;
            vertex.z = inverse_lerp(p.z, min_z, max_z) * 2.0f - 1.0f;
            vertices.push_back(vertex);
        }
        // creating render data
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(VertexInfo));
        
        va = new VertexArray();
        va->AddBuffer(*vb, layout);
        ib = new IndexBuffer(&indices[0], indices.size());

    }

};
