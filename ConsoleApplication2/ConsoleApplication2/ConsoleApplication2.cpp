// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "node.h"
#include <list>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using std::list;
using std::cout;
using std::endl;
using std::cin;

const int SMALL_WIDTH = 80;
const int SMALL_HEIGHT = 25;
const int MEDIUM_DIM = 100;
const int LARGE_DIM = 500;
const int HUGE_DIM = 1000;

list<node*> prims_in_maze;
list<node*> prims_frontier_maze;
list<node*> prims_holder;

node* small_array[80][25];
node* medium_array[100][100];
node* large_array[500][500];
node* huge_array[1000][1000];


enum MAZE_SIZE
{
	SMALL,
	MEDIUM,
	LARGE,
	GIANT
};

void generate_prims(MAZE_SIZE);
void add_neighbors_to_frontier(node*, MAZE_SIZE);
void check_neighbors(node*, MAZE_SIZE);
void initialize_array(MAZE_SIZE);
void print_array(MAZE_SIZE);

int main()
{
	srand(time(NULL));

	generate_prims(SMALL);
	print_array(SMALL);

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

		cout << start_x << " " <<start_y << endl;
		cout << prims_frontier_maze.size() << endl;


		while(!prims_frontier_maze.empty())
		{
			int location = rand() % prims_frontier_maze.size() - 1;

			cout << "location: " << location << endl;

			for (int i = location; i > 0; i--)
			{
				prims_holder.push_back(prims_frontier_maze.back());
				prims_frontier_maze.pop_back();
				cout << prims_frontier_maze.size() << endl;
			}

			prims_in_maze.push_back(prims_frontier_maze.back());
			prims_frontier_maze.pop_back();

			while (!prims_holder.empty())
			{
				cout << prims_holder.size() << endl;
				prims_frontier_maze.push_back(prims_holder.back());
				prims_holder.pop_back();
			}

			check_neighbors(prims_in_maze.back() , map_size);
			add_neighbors_to_frontier(prims_in_maze.back(), map_size);
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
						cout << l << "," << i << endl;
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
	bool north_visited = false;
	bool east_visited = false;
	bool south_visited = false;
	bool west_visited = false;
	int visited_neighbors = 0;

	switch (size)
	{
	case 0:
		cout << "case 0" << endl;
		if (home->x_coord + 1 < SMALL_WIDTH && small_array[home->x_coord + 1][home->y_coord]->
			has_been_visited == true)
		{
			cout << "east visited" << endl;
			east_visited = true;
			visited_neighbors++;
		}
		if (home->x_coord - 1 < -1 && small_array[home->x_coord - 1][home->y_coord]->
			has_been_visited == true)
		{
			cout << "west visited" << endl;
			west_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord + 1 < SMALL_HEIGHT && small_array[home->x_coord][home->y_coord + 1]->
			has_been_visited == true)
		{
			cout << "north visited" << endl;
			north_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord - 1 < -1 && small_array[home->x_coord][home->y_coord - 1]->
			has_been_visited == true)
		{
			cout << "south visited" << endl;
			south_visited = true;
			visited_neighbors++;
		}
		break;
	case 1:
		cout << "case 1" << endl;
		if (home->x_coord + 1 < MEDIUM_DIM && small_array[home->x_coord + 1][home->y_coord]->
			has_been_visited == true)
		{
			east_visited = true;
			visited_neighbors++;
		}
		if (home->x_coord - 1 < -1 && small_array[home->x_coord - 1][home->y_coord]->
			has_been_visited == true)
		{
			west_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord + 1 < MEDIUM_DIM && small_array[home->x_coord][home->y_coord + 1]->
			has_been_visited == true)
		{
			north_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord - 1 < -1 && small_array[home->x_coord][home->y_coord - 1]->
			has_been_visited == true)
		{
			south_visited = true;
			visited_neighbors++;
		}
		break;
	case 2:
		cout << "case 2" << endl;
		if (home->x_coord + 1 < LARGE_DIM && small_array[home->x_coord + 1][home->y_coord]->
			has_been_visited == true)
		{
			east_visited = true;
			visited_neighbors++;
		}
		if (home->x_coord - 1 < -1 && small_array[home->x_coord - 1][home->y_coord]->
			has_been_visited == true)
		{
			west_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord + 1 < LARGE_DIM && small_array[home->x_coord][home->y_coord + 1]->
			has_been_visited == true)
		{
			north_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord - 1 < -1 && small_array[home->x_coord][home->y_coord - 1]->
			has_been_visited == true)
		{
			south_visited = true;
			visited_neighbors++;
		}
		break;
	case 3:
		cout << "case 3" << endl;
		if (home->x_coord + 1 < HUGE_DIM && small_array[home->x_coord + 1][home->y_coord]->
			has_been_visited == true)
		{
			east_visited = true;
			visited_neighbors++;
		}
		if (home->x_coord - 1 < -1 && small_array[home->x_coord - 1][home->y_coord]->
			has_been_visited == true)
		{
			west_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord + 1 < HUGE_DIM && small_array[home->x_coord][home->y_coord + 1]->
			has_been_visited == true)
		{
			north_visited = true;
			visited_neighbors++;
		}
		if (home->y_coord - 1 < -1 && small_array[home->x_coord][home->y_coord - 1]->
			has_been_visited == true)
		{
			south_visited = true;
			visited_neighbors++;
		}
		break;
	default:
		break;
	}

	cout << prims_frontier_maze.size() << endl;
	cout << visited_neighbors << endl;
	cin.sync();
	cin.get();

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
			cout << "while loop" << endl;
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
	cout << "inside the print" << endl;
	switch (size)
	{
	case SMALL:
		for (int i = 0; i < SMALL_HEIGHT;i++)
		{
			for (int l = 0;i < SMALL_WIDTH;i++)
			{
				if (small_array[l][i]->north_is_open && !small_array[l][i]->east_is_open &&
					!small_array[l][i]->south_is_open && !small_array[l][i]->west_is_open )
				{
					cout << 1 << " ";
				}
				if (!small_array[l][i]->north_is_open && small_array[l][i]->east_is_open &&
					!small_array[l][i]->south_is_open && !small_array[l][i]->west_is_open)
				{
					cout << 2 << " ";
				}
				if (!small_array[l][i]->north_is_open && !small_array[l][i]->east_is_open &&
					small_array[l][i]->south_is_open && !small_array[l][i]->west_is_open)
				{
					cout << 3 << " ";
				}
				if (!small_array[l][i]->north_is_open && !small_array[l][i]->east_is_open &&
					!small_array[l][i]->south_is_open && small_array[l][i]->west_is_open)
				{
					cout << 4 << " ";
				}
				if (small_array[l][i]->north_is_open && small_array[l][i]->east_is_open &&
					!small_array[l][i]->south_is_open && !small_array[l][i]->west_is_open)
				{
					cout << 5 << " ";
				}
				if (small_array[l][i]->north_is_open && !small_array[l][i]->east_is_open &&
					small_array[l][i]->south_is_open && !small_array[l][i]->west_is_open)
				{
					cout << 6 << " ";
				}
				if (small_array[l][i]->north_is_open && !small_array[l][i]->east_is_open &&
					!small_array[l][i]->south_is_open && small_array[l][i]->west_is_open)
				{
					cout << 7 << " ";
				}
				if (!small_array[l][i]->north_is_open && small_array[l][i]->east_is_open &&
					small_array[l][i]->south_is_open && !small_array[l][i]->west_is_open)
				{
					cout << 8 << " ";
				}
				if (!small_array[l][i]->north_is_open && small_array[l][i]->east_is_open &&
					!small_array[l][i]->south_is_open && small_array[l][i]->west_is_open)
				{
					cout << 9 << " ";
				}
				if (!small_array[l][i]->north_is_open && !small_array[l][i]->east_is_open &&
					small_array[l][i]->south_is_open && small_array[l][i]->west_is_open)
				{
					cout << 0 << " ";
				}
				if (small_array[l][i]->north_is_open && small_array[l][i]->east_is_open &&
					small_array[l][i]->south_is_open && !small_array[l][i]->west_is_open)
				{
					cout << "A" << " ";
				}
				if (small_array[l][i]->north_is_open && small_array[l][i]->east_is_open &&
					!small_array[l][i]->south_is_open && small_array[l][i]->west_is_open)
				{
					cout << "B" << " ";
				}
				if (small_array[l][i]->north_is_open && !small_array[l][i]->east_is_open &&
					small_array[l][i]->south_is_open && small_array[l][i]->west_is_open)
				{
					cout << "C" << " ";
				}
				if (!small_array[l][i]->north_is_open && small_array[l][i]->east_is_open &&
					small_array[l][i]->south_is_open && small_array[l][i]->west_is_open)
				{
					cout << "D" << " ";
				}
				if (small_array[l][i]->north_is_open && small_array[l][i]->east_is_open &&
					small_array[l][i]->south_is_open && small_array[l][i]->west_is_open)
				{
					cout << "E" << " ";
				}
				if (!small_array[l][i]->north_is_open && !small_array[l][i]->east_is_open &&
					!small_array[l][i]->south_is_open && !small_array[l][i]->west_is_open)
				{
					cout << "broken" << " ";
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
	cin.sync();
	cin.get();
}