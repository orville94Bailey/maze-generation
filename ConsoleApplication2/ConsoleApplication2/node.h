#pragma once
#include <vector>

class node
{
public:
	node(int, int);
	~node();
	bool north_is_open;
	bool east_is_open;
	bool south_is_open;
	bool west_is_open;
	bool has_been_visited;
	bool is_in_frontier;
	float f;
	int g;
	int x_coord;
	int y_coord;

	node* parent_node;
	std::vector<node *> children_nodes;
};

