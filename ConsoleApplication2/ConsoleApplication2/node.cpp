#include "stdafx.h"
#include "node.h"


node::node(int x, int y)
{
	north_is_open = false;
	east_is_open = false;
	south_is_open = false;
	west_is_open = false;
	has_been_visited = false;
	is_in_frontier = false;
	x_coord = x;
	y_coord = y;

	children_nodes.resize(4);
	for (int i = 0; i < children_nodes.size(); i++)
	{
		children_nodes[i] = NULL;
	}
}


node::~node()
{
}
