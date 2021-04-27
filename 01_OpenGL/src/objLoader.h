#pragma once

#include <iostream>
#include <filesystem>
#include "Model.h"

#include "OBJ_Loader.h"

struct objLoader
{
	std::vector<std::string> paths;
	std::vector<Model*> models;

	void init()
	{
		std::string path = "src/res/models/test/";
		std::filesystem::create_directories(path);
		for (std::filesystem::path path : std::filesystem::directory_iterator(path))
		{
			std::string _path = path.u8string();
			std::cout << _path << std::endl;
			paths.push_back(_path);
		}

		for (std::string s : paths)
		{
			//Model* _model = new Model(s, 1);
			//models.push_back(_model);
			objl::Loader loader{};
			// just loads the file into some mem inside
			loader.LoadFile(s);

			std::vector<Mesh> meshes;
			for (objl::Mesh mesh : loader.LoadedMeshes)
			{
				std::vector<Vertex> vertices_;
				for (objl::Vertex v : mesh.Vertices)
				{
					Vertex _v{};
					_v.position.x = v.Position.X;
					_v.position.y = v.Position.Y;
					_v.position.z = v.Position.Z;
					
					_v.normal.x = v.Normal.X;
					_v.normal.y = v.Normal.Y;
					_v.normal.z = v.Normal.Z;
					
					_v.texCoord.x = v.TextureCoordinate.X;
					_v.texCoord.y = v.TextureCoordinate.Y;
					
					vertices_.push_back(_v);
				}

				Mesh m(vertices_, mesh.Indices);
				meshes.push_back(m);
			}

			Model* model = new Model();
			model->meshes.swap(meshes);
			models.push_back(model);
		}

	}

};