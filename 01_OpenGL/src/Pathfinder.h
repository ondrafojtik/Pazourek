#pragma once
#include "glm/vec2.hpp"
#include <vector>
#include <array>
#include <math.h>

#include <iostream>

struct Node
{
	bool collidable = false;
	bool visited = false;
	float global_cost = 0.0f;
	float local_cost = 0.0f;
	glm::vec2 position;
	//std::vector<Node> adj;
	std::vector<glm::vec2> adj;
	Node* parent = nullptr;
	//represents the "grid color" and whether its collidable or not
	char grid_type;
};

//this is an A* type pathFinder

static bool isCollidable(char c)
{
	if ((c == 'F') || (c == 'V'))
		return true;
	return false;
}

static int distance(Node* lhs, Node* rhs)
{
	return std::sqrtf(std::powf(lhs->position.x - rhs->position.x, 2) + std::powf(lhs->position.y - rhs->position.y, 2));
}

struct Pathfinder
{
	Pathfinder() { std::cout << "Pathfinder init!\n"; }

	void Init(std::array<Node, (15 * 8)>& grid)
	{
		for (Node& node : grid)
		{
			node.adj.reserve(4);
			if (isCollidable(node.grid_type))
				node.collidable = true;
			else
				node.collidable = false;
			node.global_cost = INFINITY;
			node.local_cost = INFINITY;
			node.parent = nullptr;
			node.visited = false;

			int x = node.position.x;
			int y = node.position.y;

			if (x > 0)
				node.adj.push_back(grid[(x - 1) + ((y + 0) * 15)].position);
			if (x < 15 - 1)
				node.adj.push_back(grid[(x + 1) + ((y + 0) * 15)].position);
			if (y > 0)
				node.adj.push_back(grid[(x + 0) + ((y - 1) * 15)].position);
			if (y < 8 - 1)
				node.adj.push_back(grid[(x + 0) + ((y + 1) * 15)].position);

		}
		
	}
	
	void Reset(std::array<Node, (15 * 8)>& grid)
	{
		for (auto node : grid)
		{
			if (isCollidable(node.grid_type))
				node.collidable = true;
			else
				node.collidable = false;
			node.global_cost = INFINITY;
			node.local_cost = INFINITY;
			node.parent = nullptr;
			node.visited = false;


			//if (y > 0)
			//	nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
			//if (y < nMapHeight - 1)
			//	nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
			//if (x > 0)
			//	nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
			//if (x < nMapWidth - 1)
			//	nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);
		}
	}
	
	//creates the path
	void Solve(std::array<Node, (15 * 8)>& grid, Node start, Node end)
	{
		

	}
	
};