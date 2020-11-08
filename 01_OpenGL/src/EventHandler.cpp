#include "EventHandler.h"

Camera* EventHandler::camera = nullptr;
bool EventHandler::mouseEnable = false;
MouseRay* EventHandler::mouseRay = new MouseRay();
glm::vec3 EventHandler::originPoint = glm::vec3(0.0f);
glm::vec3 EventHandler::destPoint = glm::vec3(0.0f);