#pragma once
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
	int x_coord;
	int y_coord;
};

