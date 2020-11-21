#include <iostream>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Camera.h"
#include "math.h"

#include "glm/ext/matrix_projection.hpp"

static glm::vec3 normalize(glm::vec3 vec)
{
    float XY = sqrt((vec.x * vec.x) + (vec.y * vec.y));
    float final = sqrt((XY * XY) + (vec.z * vec.z));
    return glm::vec3(vec.x / final, vec.y / final, vec.z / final);
};

struct MouseRay
{
    glm::vec3 originPoint;
    glm::vec3 destPoint;

    glm::vec3 get_normalized_ray()
    {
        return normalize(destPoint - originPoint);
    }
    
    Camera* camera = nullptr;
    MouseRay() { ; }

    void init()
    {
        mousePos.x = 0.0f;
        mousePos.y = 0.0f;
        //this->camera = camera;
        std::cout << "Norm: x: " << normalize({ 2, 1, 2 }).x << "y: " << normalize({ 2, 1, 2 }).y << "z: " << normalize({ 2, 1, 2 }).z << std::endl;
    }

    void set_mouse_position(glm::dvec2 pos)
    {
        mousePos.x = (float)pos.x;
        mousePos.y = (float)pos.y;
    }

    void update_camera(Camera* camera)
    {
        this->camera = camera;
    }

    void update()
    {

        // TODO: do some class, where I could actually get the "application" info
        // (such as windowWidth, ..)
        float windowWidth = 960.0f;
        float windowHeight = 540.0f;

        // right now, changing the z-value makes no sence.. (theres an error smwhere..) might aswell remove it 
        float _depth;
        glReadPixels(mousePos.x, glm::abs(windowHeight - mousePos.y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &_depth);
        // normalize to OpenGL space
        float x = (2.0f * mousePos.x) / windowWidth - 1.0f;
        float y = (2.0f * mousePos.y) / windowHeight - 1.0f;
        float z = (2.0f * _depth) - 1.0f;
        glm::vec3 ray_nds = glm::vec3(x, -y, 1.0f);

        // clip space (homogeneous)
        glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

        // camera space (projection matrix)
        glm::vec4 ray_eye = glm::inverse(camera->GetProjection()) * ray_clip;
        ray_eye.z = -1.0f;
        ray_eye.w = 0.0f;

        // world coords (view)
        glm::vec4 ray_wor = glm::inverse(camera->GetView()) * ray_eye;
        glm::vec3 ray_world = glm::vec3(ray_wor.x, ray_wor.y, ray_wor.z);

        // normalize (just to make sure)
        mouseRay = normalize(ray_world);

        // getting correct Z value
        glm::vec3 _destPoint = glm::unProject(glm::vec3(mousePos.x, glm::abs(windowHeight - mousePos.y), _depth), camera->GetView(), camera->GetProjection(), glm::vec4(0, 0, windowWidth, windowHeight));

        // result
        originPoint.x = camera->GetPosition().x + camera->GetForward().x;
        originPoint.y = camera->GetPosition().y + camera->GetForward().y;
        originPoint.z = camera->GetPosition().z + camera->GetForward().z;
#if 0
        float distance = 100;
        destPoint.x = originPoint.x + (mouseRay.x * distance);
        destPoint.y = originPoint.y + (mouseRay.y * distance);
        destPoint.z = originPoint.z + (mouseRay.z * distance);
#else
        destPoint.x = _destPoint.x;
        destPoint.y = _destPoint.y;
        destPoint.z = _destPoint.z;
#endif

    }


private:
    glm::vec2 mousePos; 
    glm::vec3 mouseRay; // this is the final product after all conversions

    glm::mat4 view;
    glm::mat4 projection;
    
    


};
