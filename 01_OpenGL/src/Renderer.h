#pragma once
#include "GL/glew.h"

#include <memory>
#include <string>

#include "RenderData.h"

#include "Camera.h"
#include "ParticleSystem.h"

#include "SubTexture.h"
#include <unordered_map>
#include "Model.h"
#include "Enemy.h"

#include "RandomMap.h"

#include "Light.h"

#include "FontSheet.h"

class Renderer
{
private:
	Camera* m_Camera;
	RenderData data;

	Texture* blank = new Texture("src/res/textures/Blank.png");
	Texture* grid = new Texture("src/res/textures/grid.png");
public:
	Renderer(Camera* camera);

    // draw a light component
	void DrawObject(Object& object);
	void DrawLight(Light& light);
    // skyBox
	void DrawCube(Texture& texture, glm::vec3 position, glm::vec3 scale,
                  float rotation, float xAxes, float yAxes, float zAxes);
    // plain color / light
	void DrawColor(const glm::vec4& color, glm::vec3 position,
                   float rotation, float xAxes, float yAxes, float zAxes);
    // model
	void DrawModel(Texture& diffuse, Texture& specular, Texture& normals,
					Texture& AO, Texture& roughness, glm::vec3 position,
					Light* lights, float ambientStrength,
					float Shininess, Model model);
    // procedural map
    void DrawMap(const RandomMap& map, glm::vec3 position, Light* lights, bool drawNormals);
	void DrawLine(glm::vec3 p1, glm::vec3 p2);
    // draw font
    void DrawChar(FontSheet& font, char32_t character, glm::vec3 position, glm::vec3 color);
    void DrawFont(FontSheet& font, std::string text, glm::vec3 position, glm::vec3 color);

	void Clear() const;
};
