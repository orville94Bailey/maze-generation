// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "node.h"
#include <list>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cassert>
#include <stack>
#include <vector>

using std::list;
using std::cout;
using std::endl;
using std::cin;
using std::vector;

const int SMALL_WIDTH = 80;
const int SMALL_HEIGHT = 25;
const int MEDIUM_DIM = 100;
const int LARGE_DIM = 500;
const int HUGE_DIM = 1000;

list<node*> prims_in_maze;
list<node*> prims_frontier_maze;
list<node*> prims_holder;

std::stack<node*> dfs_tracing_stack;

node* small_array[80][25];
node* medium_array[100][100];
node* large_array[500][500];
node* huge_array[1000][1000];
//testing

enum MAZE_SIZE
{
	SMALL,
	MEDIUM,
	LARGE,
	GIANT
};

void deconstruct_maze(MAZE_SIZE size);

void generate_prims(MAZE_SIZE);
void add_neighbors_to_frontier(node*, MAZE_SIZE);
void check_neighbors(node*, MAZE_SIZE);
void initialize_array(MAZE_SIZE);
void print_array(MAZE_SIZE);
void check_locations_of_frontier_nodes(MAZE_SIZE);
vector<int>  check_neighbors_dfs(int x, int y, MAZE_SIZE);

void generate_dfs_hori(MAZE_SIZE);



int main()
{

	srand(time(NULL));
	initialize_array(SMALL);
	generate_dfs_hori(SMALL);
	print_array(SMALL);
	cin.sync();
	cin.get();
	deconstruct_maze(SMALL);

    return 0;
}

void generate_prims(MAZE_SIZE map_size)
{
	initialize_array(map_size);

	switch (map_size)
	{
	case SMALL:
	{
		//generate prims maze on small
		//
		int start_x = rand() % SMALL_WIDTH;
		int start_y = rand() % SMALL_HEIGHT;

		prims_in_maze.push_front(small_array[start_x][start_y]);
		small_array[start_x][start_y]->has_been_visited = true;
		add_neighbors_to_frontier(small_array[start_x][start_y], map_size);

		while(!prims_frontier_maze.empty())
		{
			int location = rand() % prims_frontier_maze.size() - 1;

			if (location == -1)
			{
				location++;
			}

			for (int i = location; i > 0; i--)
			{
				prims_holder.push_back(prims_frontier_maze.back());
				prims_frontier_maze.pop_back();
			}

			prims_in_maze.push_back(prims_frontier_maze.back());
			prims_in_maze.back()->is_in_frontier = false;
			prims_in_maze.back()->has_been_visited = true;
			prims_frontier_maze.pop_back();

			while (!prims_holder.empty())
			{
				prims_frontier_maze.push_back(prims_holder.back());
				prims_holder.pop_back();
			}

			add_neighbors_to_frontier(prims_in_maze.back(), map_size);
			check_neighbors(prims_in_maze.back() , map_size);

		}
		break;
	}
	case MEDIUM:
	{
		//generate prims maze on med
		int start_x = rand() % MEDIUM_DIM;
		int start_y = rand() % MEDIUM_DIM;

		prims_in_maze.push_front(small_array[start_x][start_y]);
		medium_array[start_x][start_y]->has_been_visited = true;
		add_neighbors_to_frontier(small_array[start_x][start_y], map_size);

		while (!prims_frontier_maze.empty())
		{
			int location = rand() % prims_frontier_maze.size();

			for (int i = rand() % prims_frontier_maze.size(); i > 0; i--)
			{
				prims_holder.push_back(prims_frontier_maze.back());
				prims_frontier_maze.pop_back();
			}
			prims_in_maze.push_back(prims_frontier_maze.back());
			prims_frontier_maze.pop_back();
			while (!prims_holder.empty())
			{
				prims_frontier_maze.push_back(prims_holder.back());
				prims_holder.pop_back();
			}

			check_neighbors(prims_in_maze.back(), map_size);
			add_neighbors_to_frontier(prims_in_maze.back(), map_size);
		}
		break;
	}
	case LARGE:
	{
		//generate prims maze on large
		int start_x = rand() % LARGE_DIM;
		int start_y = rand() % LARGE_DIM;

		prims_in_maze.push_front(small_array[start_x][start_y]);
		large_array[start_x][start_y]->has_been_visited = true;
		add_neighbors_to_frontier(small_array[start_x][start_y], map_size);

		while (!prims_frontier_maze.empty())
		{
			int location = rand() % prims_frontier_maze.size();

			for (int i = rand() % prims_frontier_maze.size(); i > 0; i--)
			{
				prims_holder.push_back(prims_frontier_maze.back());
				prims_frontier_maze.pop_back();
			}
			prims_in_maze.push_back(prims_frontier_maze.back());
			prims_frontier_maze.pop_back();
			while (!prims_holder.empty())
			{
				prims_frontier_maze.push_back(prims_holder.back());
				prims_holder.pop_back();
			}

			check_neighbors(prims_in_maze.back(), map_size);
			add_neighbors_to_frontier(prims_in_maze.back(), map_size);
		}
		break;
	}
	case GIANT:
	{
		//generate prims on huge
		int start_x = rand() % HUGE_DIM;
		int start_y = rand() % HUGE_DIM;

		prims_in_maze.push_front(small_array[start_x][start_y]);
		huge_array[start_x][start_y]->has_been_visited = true;
		add_neighbors_to_frontier(small_array[start_x][start_y], map_size);

		while (!prims_frontier_maze.empty())
		{
			int location = rand() % prims_frontier_maze.size();

			for (int i = rand() % prims_frontier_maze.size(); i > 0; i--)
			{
				prims_holder.push_back(prims_frontier_maze.back());
				prims_frontier_maze.pop_back();
			}
			prims_in_maze.push_back(prims_frontier_maze.back());
			prims_frontier_maze.pop_back();
			while (!prims_holder.empty())
			{
				prims_frontier_maze.push_back(prims_holder.back());
				prims_holder.pop_back();
			}

			check_neighbors(prims_in_maze.back(), map_size);
			add_neighbors_to_frontier(prims_in_maze.back(), map_size);
		}
		break;
	}
	default:
		break;
	}
}

void initialize_array(MAZE_SIZE map_size)
{
	switch (map_size)
	{
	case SMALL:
		{
			for (int i = 0;i < 25; i++)
				{
					for (int l = 0;l < 80; l++)
					{
						small_array[l][i] = new node(l,i);
					}
				}
		}
		break;

	case MEDIUM:
		{
			for (int i = 0;i < 100; i++)
			{
				for (int l = 0;l < 100; l++)
				{
					medium_array[l][i] = new node(l,i);
				}
			}
		}
		break;

	case LARGE:
		{
			for (int i = 0;i < 500; i++)
			{
				for (int l = 0;l < 500; l++)
				{
					large_array[l][i] = new node(l,i);
				}
			}
		}
	case GIANT:
		{
			for (int i = 0;i < 1000; i++)
			{
				for (int l = 0;l < 1000; l++)
				{
					cout << l<<","<<i << endl;
					huge_array[l][i] = new node(l,i);
				}
			}
		}
		break;

	default:
		break;
	}
}

void add_neighbors_to_frontier(node* home, MAZE_SIZE size)
{
	int current_x = home->x_coord;
	int current_y = home->y_coord;

	//always adds nodes to frontier list problem may be here

	switch (size)
	{
	case SMALL:
		if (current_x + 1 < SMALL_WIDTH && small_array[current_x + 1][current_y]->
			has_been_visited == false && small_array[current_x + 1][current_y]->
			is_in_frontier == false)
			{
				prims_frontier_maze.push_back(small_array[current_x + 1][current_y]);
				small_array[current_x + 1][current_y]->is_in_frontier = true;
			}
		if (current_x - 1 > -1 && small_array[current_x - 1][current_y]->
			has_been_visited == false && small_array[current_x - 1][current_y]->
			is_in_frontier == false)
			{
				prims_frontier_maze.push_back(small_array[current_x - 1][current_y]);
				small_array[current_x - 1][current_y]->is_in_frontier = true;
			}
		if (current_y + 1 < SMALL_HEIGHT && small_array[current_x][current_y + 1]->
			has_been_visited == false && small_array[current_x][current_y + 1]->
			is_in_frontier == false)
			{
				prims_frontier_maze.push_back(small_array[current_x][current_y + 1]);
				small_array[current_x][current_y + 1]->is_in_frontier = true;
			}
		if (current_y - 1 > -1 && small_array[current_x][current_y - 1]->
			has_been_visited == false && small_array[current_x][current_y - 1]->
			is_in_frontier == false)
			{
				prims_frontier_maze.push_back(small_array[current_x][current_y - 1]);
				small_array[current_x][current_y - 1]->is_in_frontier = true;
			}
		break;
	case MEDIUM:
		if (current_x + 1 < MEDIUM_DIM && medium_array[current_x + 1][current_y]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(medium_array[current_x + 1][current_y]);
				medium_array[current_x + 1][current_y]->is_in_frontier = true;
			}
		if (current_x - 1 > -1 && medium_array[current_x - 1][current_y]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(medium_array[current_x - 1][current_y]);
				medium_array[current_x - 1][current_y]->is_in_frontier = true;
			}
		if (current_y + 1 < MEDIUM_DIM && medium_array[current_x][current_y + 1]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(medium_array[current_x][current_y + 1]);
				medium_array[current_x][current_y + 1]->is_in_frontier = true;
			}
		if (current_y - 1 > -1 && medium_array[current_x][current_y - 1]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(medium_array[current_x][current_y - 1]);
				medium_array[current_x][current_y - 1]->is_in_frontier = true;
			}
		break;
	case LARGE:
		if (current_x + 1 < LARGE_DIM && large_array[current_x + 1][current_y]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(large_array[current_x + 1][current_y]);
				large_array[current_x + 1][current_y]->is_in_frontier = true;
			}
		if (current_x - 1 > -1 && large_array[current_x - 1][current_y]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(large_array[current_x - 1][current_y]);
				large_array[current_x - 1][current_y]->is_in_frontier = true;
			}
		if (current_y + 1 < LARGE_DIM && large_array[current_x][current_y + 1]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(large_array[current_x][current_y + 1]);
				large_array[current_x][current_y + 1]->is_in_frontier = true;
			}
		if (current_y - 1 > -1 && large_array[current_x][current_y - 1]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(large_array[current_x][current_y - 1]);
				large_array[current_x][current_y - 1]->is_in_frontier = true;
			}
		break;
	case GIANT:
		if (current_x + 1 < HUGE_DIM && huge_array[current_x + 1][current_y]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(huge_array[current_x + 1][current_y]);
				huge_array[current_x + 1][current_y]->is_in_frontier = true;
			}
		if (current_x - 1 > -1 && huge_array[current_x - 1][current_y]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(huge_array[current_x - 1][current_y]);
				huge_array[current_x - 1][current_y]->is_in_frontier = true;
			}
		if (current_y + 1 < HUGE_DIM && huge_array[current_x][current_y + 1]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(huge_array[current_x][current_y + 1]);
				huge_array[current_x][current_y + 1]->is_in_frontier = true;
			}
		if (current_y - 1 > -1 && huge_array[current_x][current_y - 1]->
			has_been_visited == false)
			{
				prims_frontier_maze.push_back(huge_array[current_x][current_y - 1]);
				huge_array[current_x][current_y - 1]->is_in_frontier = true;
			}
		break;
	default:
		break;
	}
}

void check_neighbors(node* home, MAZE_SIZE size)
{
	//check_locations_of_frontier_nodes(size);

	bool north_visited = false;
	bool east_visited = false;
	bool south_visited = false;
	bool west_visited = false;
	int visited_neighbors = 0;

	switch (size)
	{
	case 0:
		if (home->x_coord + 1 < SMALL_WIDTH && small_array[home->x_coord + 1][home->y_coord]->
			has_been_visited == true)
		{
			east_visited = true;
			visited_neighbors++;
		}
		if (home->x_coord - 1 > -1 && small_array[home->x_coord - 1][home->y_coord]->
			has_been_visited == true)
		{
			west_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord + 1 < SMALL_HEIGHT && small_array[home->x_coord][home->y_coord + 1]->
			has_been_visited == true)
		{
			north_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord - 1 > -1 && small_array[home->x_coord][home->y_coord - 1]->
			has_been_visited == true)
		{
			south_visited = true;
			visited_neighbors++;
		}
		break;
	case 1:
		if (home->x_coord + 1 < MEDIUM_DIM && medium_array[home->x_coord + 1][home->y_coord]->
			has_been_visited == true)
		{
			east_visited = true;
			visited_neighbors++;
		}
		if (home->x_coord - 1 > -1 && medium_array[home->x_coord - 1][home->y_coord]->
			has_been_visited == true)
		{
			west_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord + 1 < MEDIUM_DIM && medium_array[home->x_coord][home->y_coord + 1]->
			has_been_visited == true)
		{
			north_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord - 1 > -1 && medium_array[home->x_coord][home->y_coord - 1]->
			has_been_visited == true)
		{
			south_visited = true;
			visited_neighbors++;
		}
		break;
	case 2:
		if (home->x_coord + 1 < LARGE_DIM && large_array[home->x_coord + 1][home->y_coord]->
			has_been_visited == true)
		{
			east_visited = true;
			visited_neighbors++;
		}
		if (home->x_coord - 1 > -1 && large_array[home->x_coord - 1][home->y_coord]->
			has_been_visited == true)
		{
			west_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord + 1 < LARGE_DIM && large_array[home->x_coord][home->y_coord + 1]->
			has_been_visited == true)
		{
			north_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord - 1 > -1 && large_array[home->x_coord][home->y_coord - 1]->
			has_been_visited == true)
		{
			south_visited = true;
			visited_neighbors++;
		}
		break;
	case 3:
		if (home->x_coord + 1 < HUGE_DIM && huge_array[home->x_coord + 1][home->y_coord]->
			has_been_visited == true)
		{
			east_visited = true;
			visited_neighbors++;
		}
		if (home->x_coord - 1 > -1 && huge_array[home->x_coord - 1][home->y_coord]->
			has_been_visited == true)
		{
			west_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord + 1 < HUGE_DIM && huge_array[home->x_coord][home->y_coord + 1]->
			has_been_visited == true)
		{
			north_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord - 1 > -1 && huge_array[home->x_coord][home->y_coord - 1]->
			has_been_visited == true)
		{
			south_visited = true;
			visited_neighbors++;
		}
		break;
	default:
		break;
	}


	if (visited_neighbors == 1)
	{
		if (north_visited == true)
		{
			home->north_is_open = true;
			small_array[home->x_coord][home->y_coord + 1]->south_is_open = true;
		}

		if (east_visited == true)
		{
			home->east_is_open = true;
			small_array[home->x_coord + 1][home->y_coord]->west_is_open = true;
		}

		if (south_visited == true)
		{
			home->south_is_open = true;
			small_array[home->x_coord][home->y_coord - 1]->north_is_open = true;
		}

		if (west_visited == true)
		{
			home->west_is_open = true;
			small_array[home->x_coord - 1][home->y_coord]->east_is_open = true;
		}
	}
	else
	if(visited_neighbors > 1){
		while (home->north_is_open == false && home->east_is_open == false && home->south_is_open == false && home->west_is_open == false)
		{
			switch (rand() % 4)
				{
				case 0:
					if (north_visited == true)
					{
						home->north_is_open = true;
						small_array[home->x_coord][home->y_coord + 1]->south_is_open = true; //sets the walls for the home cell and the neighboring cell to open
					}
					break;
				case 1:
					if (east_visited == true)
					{
						home->east_is_open = true;
						small_array[home->x_coord + 1][home->y_coord]->west_is_open = true; //sets the walls for the home cell and the neighboring cell to open
					}
					break;
				case 2:
					if (south_visited == true)
					{
						home->south_is_open = true;
						small_array[home->x_coord][home->y_coord - 1]->north_is_open = true; //sets the walls for the home cell and the neighboring cell to open
					}
					break;
				case 3:
					if (west_visited == true)
					{
						home->west_is_open = true;
						small_array[home->x_coord - 1][home->y_coord]->east_is_open = true; //sets the walls for the home cell and the neighboring cell to open
					}
					break;
				}
		}

	}
}

void print_array(MAZE_SIZE size)
{
	switch (size)
	{
	case SMALL:
		for (int i = 0; i < SMALL_HEIGHT;i++)
		{
			for (int l = 0;l < SMALL_WIDTH;l++)
			{
				if (small_array[i][l]->north_is_open && !small_array[i][l]->east_is_open &&
					!small_array[i][l]->south_is_open && !small_array[i][l]->west_is_open )
				{
					cout<<1;
				}
				else if (!small_array[i][l]->north_is_open && small_array[i][l]->east_is_open &&
					!small_array[i][l]->south_is_open && !small_array[i][l]->west_is_open)
				{
					cout << 2;
				}
				else if (!small_array[i][l]->north_is_open && !small_array[i][l]->east_is_open &&
					small_array[i][l]->south_is_open && !small_array[i][l]->west_is_open)
				{
					cout << 3;
				}
				else if (!small_array[i][l]->north_is_open && !small_array[i][l]->east_is_open &&
					!small_array[i][l]->south_is_open && small_array[i][l]->west_is_open)
				{
					cout << 4;
				}
				else if (small_array[i][l]->north_is_open && small_array[i][l]->east_is_open &&
					!small_array[i][l]->south_is_open && !small_array[i][l]->west_is_open)
				{
					cout << 5;
				}
				else if (small_array[i][l]->north_is_open && !small_array[i][l]->east_is_open &&
					small_array[i][l]->south_is_open && !small_array[i][l]->west_is_open)
				{
					cout << 6;
				}
				else if (small_array[i][l]->north_is_open && !small_array[i][l]->east_is_open &&
					!small_array[i][l]->south_is_open && small_array[i][l]->west_is_open)
				{
					cout << 7;
				}
				else if (!small_array[i][l]->north_is_open && small_array[i][l]->east_is_open &&
					small_array[i][l]->south_is_open && !small_array[i][l]->west_is_open)
				{
					cout << 8;
				}
				else if (!small_array[i][l]->north_is_open && small_array[i][l]->east_is_open &&
					!small_array[i][l]->south_is_open && small_array[i][l]->west_is_open)
				{
					cout << 9;
				}
				else if (!small_array[i][l]->north_is_open && !small_array[i][l]->east_is_open &&
					small_array[i][l]->south_is_open && small_array[i][l]->west_is_open)
				{
					cout << 0;
				}
				else if (small_array[i][l]->north_is_open && small_array[i][l]->east_is_open &&
					small_array[i][l]->south_is_open && !small_array[i][l]->west_is_open)
				{
					cout << 'A';
				}
				else if (small_array[i][l]->north_is_open && small_array[i][l]->east_is_open &&
					!small_array[i][l]->south_is_open && small_array[i][l]->west_is_open)
				{
					cout << 'B';
				}
				else if (small_array[i][l]->north_is_open && !small_array[i][l]->east_is_open &&
					small_array[i][l]->south_is_open && small_array[i][l]->west_is_open)
				{
					cout << 'C';
				}
				else if (!small_array[i][l]->north_is_open && small_array[i][l]->east_is_open &&
					small_array[i][l]->south_is_open && small_array[i][l]->west_is_open)
				{
					cout << 'D';
				}
				else if (small_array[i][l]->north_is_open && small_array[i][l]->east_is_open &&
					small_array[i][l]->south_is_open && small_array[i][l]->west_is_open)
				{
					cout << 'E';
				}
				else if (!small_array[i][l]->north_is_open && !small_array[i][l]->east_is_open &&
					!small_array[i][l]->south_is_open && !small_array[i][l]->west_is_open)
				{
					cout << ' ';
				}
				else
				{
					cout << ' ';
				}
			}
		}
		break;
	case MEDIUM:
		break;
	case LARGE:
		break;
	case GIANT:
		break;
	default:
		break;
	}
}

void check_locations_of_frontier_nodes(MAZE_SIZE size)
{
	switch (size)
	{
	case SMALL:
		for (int i = 0; i < SMALL_HEIGHT;i++)
		{
			for (int l = 0; l < SMALL_WIDTH; l++)
			{
				if (small_array[l][i]->is_in_frontier == true)
				{
					cout <<"x:" <<small_array[l][i]->x_coord <<" y: "<< small_array[l][i]->y_coord << endl;
				}

			}
		}
		break;
	case MEDIUM:
		break;
	case LARGE:
		break;
	case GIANT:
		break;
	default:
		break;
	}
	cout << "end list of frontier locations" << endl;
}

void generate_dfs_hori(MAZE_SIZE size)
{
	int numberOfNodes,
		numberOfAddedNodes = 0,
		focusedX,
		focusedY;
	vector<int> neighbor_info;
	list<node*> nodes_in_maze;

	//stack<node*> dfs_tracing_stack  //Identified here for quick reference

	switch (size)
		{
		case SMALL:
			numberOfNodes = SMALL_HEIGHT * SMALL_WIDTH;
			//select random start point
			focusedX = rand() % SMALL_WIDTH;
			focusedY = rand() % SMALL_HEIGHT;
			dfs_tracing_stack.push(small_array[focusedX][focusedY]);
			nodes_in_maze.push_back(small_array[focusedX][focusedY]);

			//loop until the number of nodes in the maze equals the number of nodes in the array
			while (nodes_in_maze.size() != numberOfNodes)
			{
				neighbor_info = check_neighbors_dfs(dfs_tracing_stack.top()->x_coord, dfs_tracing_stack.top()->y_coord, size);
				if (neighbor_info[0] >= 1)
				{
					//here we will choose which direction to go
					//our weighting will also be inserted here
					//weighting will be done dynamically where if a direction is unavailable it will not be able to be chosen

					int north_weight = 0,
						east_weight = 0,
						south_weight = 0,
						west_weight = 0;

					if (neighbor_info[1] == 1)
					{
						north_weight = 2;
					}
					if (neighbor_info[2] == 1)
					{
						east_weight = 6;
					}
					if (neighbor_info[3] == 1)
					{
						south_weight = 2;
					}
					if (neighbor_info[4] == 1)
					{
						west_weight = 6;
					}

					int total_weight = north_weight + east_weight +
						south_weight + west_weight;

					int determinite_weight,//determinite weight is a number >= 0 && <total weight
						weighted_direction;//weighted direction will be an integer where 0 <= i < 4
										   //0 will represent north, then ascending and clockwise i.e. 1 == east	

					determinite_weight = rand() % total_weight;

					for (int i = 0; i < 4;i++)//this for loop is ugly, 4 is the number of directions (choices we have)
					{
						if (i == 0)
						{
							if (determinite_weight < 2)
							{
								weighted_direction = 0;
								i = 4;//this breaks out of the for loop TEST to see if a break will work here once it's working
							}
							else
							{
								determinite_weight -= 2;
							}
						}
						else if (i == 1)
						{
							if (determinite_weight < 6)
							{
								weighted_direction = 1;
								i = 4;//TEST
							}
							else
							{
								determinite_weight -= 6;
							}
						}
						else if (i == 2)
						{
							if (determinite_weight < 2)
							{
								weighted_direction = 2;
								i = 4;//TEST
							}
							else
							{
								determinite_weight -= 2;
							}
						}
						else if (i == 3)
						{
							if (determinite_weight < 6)
							{
								weighted_direction = 3;
								i = 4;//TEST
							}
							else
							{
								cout << "BROKEN IN THE WEIGHT RESOLUTION LINE 811 ConsoleApplication2.cpp" << endl;
							}
						}
					}

					switch (weighted_direction)
					{
					case 0:
						small_array[focusedX][focusedY]->north_is_open = true;
						small_array[focusedX][focusedY + 1]->south_is_open = true;
						dfs_tracing_stack.push(small_array[focusedX][focusedY + 1]);
						focusedY++;
						break;
					case 1:
						small_array[focusedX][focusedY]->east_is_open = true;
						small_array[focusedX + 1][focusedY]->west_is_open = true;
						dfs_tracing_stack.push(small_array[focusedX + 1][focusedY]);
						focusedX++;
						break;
					case 2:
						small_array[focusedX][focusedY]->south_is_open = true;
						small_array[focusedX][focusedY - 1]->north_is_open = true;
						dfs_tracing_stack.push(small_array[focusedX][focusedY - 1]);
						focusedY--;
						break;
					case 3:
						small_array[focusedX][focusedY]->west_is_open = true;
						small_array[focusedX - 1][focusedY]->east_is_open = true;
						dfs_tracing_stack.push(small_array[focusedX - 1][focusedY]);
						focusedX--;
						break;
					default:
						cout << "BROKEN IN LINE 859 ConsoleApplication2" << endl;
						break;
					}//breaks the walls between current node and next node then adds the next node to the traceback stack and sets the focused node to the next node

					nodes_in_maze.push_back(small_array[focusedX][focusedY]);
					dfs_tracing_stack.push(small_array[focusedX][focusedY]);		//changing the values of focused x and y was done in the switch statement above.
					neighbor_info.clear();
				}
				else
				{
					dfs_tracing_stack.pop();
				}
			}

			break;
		case MEDIUM:
			break;
		case LARGE:
			break;
		case GIANT:
			break;
		default:
			break;
		}
}

vector<int> check_neighbors_dfs(int x, int y, MAZE_SIZE size)
{
	vector<int> holder(5,0);
	vector<int>::iterator it = holder.begin();

	//Holder describes how many viable neighbors there are and their locations
	//holder[0] is the number of neighbors holder[1] is the north position
	//the other cardinal directions follow in a clockwise manner

	switch (size)
	{
	case SMALL:
		if (x + 1 < SMALL_WIDTH)
		{
			if (small_array[x + 1][y]->has_been_visited == false)
			{
				holder[0]++;
				holder[2]++;
			}
		}

		if (x - 1 > -1)
		{
			if (small_array[x - 1][y]->has_been_visited == false)
			{
				holder[0]++;
				holder[4]++;
			}
		}

		if (y + 1 < SMALL_HEIGHT)
		{
			if (small_array[x][y + 1]->has_been_visited == false)
			{
				holder[0]++;
				holder[1]++;
			}
		}

		if (y - 1 > -1)
		{
			if (small_array[x][y - 1]->has_been_visited == false)
			{
				holder[0]++;
				holder[3]++;
			}
		}
		break;
	case MEDIUM:
		
		break;
	case LARGE:
		
		break;
	case GIANT:
		
		break;
	default:
		break;
	}
/*       Used to see how the neighbors of the cell
	for (vector<int>::const_iterator it = holder.begin();
	it != holder.end(); it++)
	{
		cout << *it << endl;
	}
	cin.sync();
	cin.get();
	*/
	return holder;
}

void deconstruct_maze(MAZE_SIZE size)
{
	switch (size)
	{
	case SMALL:
		for (int i = 0; i < SMALL_HEIGHT; i++)
		{
			for (int l = 0; l < SMALL_WIDTH; l++)
			{
				small_array[l][i]->~node();
			}
		}
		break;
	case MEDIUM:
		for (int i = 0; i < MEDIUM_DIM; i++)
		{
			for (int l = 0; l < MEDIUM_DIM; i++)
			{
				medium_array[l][i]->~node();
			}
		}
		break;
	case LARGE:
		for (int i = 0; i < LARGE_DIM; i++)
		{
			for (int l = 0; l < LARGE_DIM; i++)
			{
				large_array[l][i]->~node();
			}
		}
		break;
	case GIANT:
		for (int i = 0; i < HUGE_DIM; i++)
		{
			for (int l = 0; l < HUGE_DIM; i++)
			{
				huge_array[l][i]->~node();
			}
		}
		break;
	default:
		break;
	}
}
