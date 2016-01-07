#include "stdafx.h"
#include "node.h"


node::node(int x, int y)
{
	north_is_open = false;
	east_is_open = false;
	south_is_open = false;
	west_is_open = false;
	has_been_visited = false;
	x_coord = x;
	y_coord = y;
}


node::~node()
{
}
