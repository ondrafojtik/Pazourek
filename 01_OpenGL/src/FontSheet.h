#pragma once
#include "glm/vec2.hpp"
#include "Texture.h"


struct FontSheet
{
    Texture* texture = nullptr;

    FontSheet(const char* file_path)
    {
        texture = new Texture(file_path);
    }

    // returns coords for given char..
    glm::vec2* get_coords(char c)
    {
        int32_t x = c - ' ';

        glm::vec2* coords = new glm::vec2[4];
        // defining sprite size (for now, its just 32x32 for each char)
        glm::vec2 sprite_size = glm::vec2(32.0f, 32.0f);
        coords[0] = { (x * sprite_size.x) / (texture->GetWidth()), 0.0f };
        coords[1] = { ((x + 1) * sprite_size.x) / (texture->GetWidth()), 0.0f };
        coords[2] = { ((x + 1) * sprite_size.x) / (texture->GetWidth()), 1.0f };
        coords[3] = { (x * sprite_size.x) / (texture->GetWidth()), 1.0f };

        return coords;
    }


};
