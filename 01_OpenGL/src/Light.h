#include "glm/vec3.hpp"

enum LightType
{
    Point = 0,
    Directional,
    Reflector
};

struct Light
{
    LightType type = LightType::Point;
    
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 color = glm::vec3(1.0f);

};
