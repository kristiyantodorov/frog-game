/*
 * graph.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: devteam
 */

#include "graph.hpp"
#include <iostream>
#include <stdlib.h>

graph::graph() {
	input();
	initialize_graph();
}

/**
 * Get the current configuration of frogs as a string.
 * '>' means looking right,
 * '<' means looking left,
 * '_' means empty slot
 */
std::string graph::current_setup()
{
	std::string str = "";

	for(int i = 0; i < 2*n + 1; i++)
	{
		if ( g[i] == DIRECTION_BACKWARDS )
			str += "< ";
		else if (g[i] == EMPTY )
			str += "_ ";
		else
			str += "> ";
	}
	str += "\n";

	return str;
}

/**
 * Backtrack approach for searching a solution
 */
void graph::dfs()
{
	if ( !solved() )
	{
		for(int i = 0; i < 2*n+1; i++)
		{
			switch(g[i])
			{
			case DIRECTION_FORWARDS:
				if ( step_possible(DIRECTION_FORWARDS, i, 1) )
				{
					path.push_back(current_setup());
					make_step(DIRECTION_FORWARDS, i, 1);
					dfs();
					undo_step(DIRECTION_FORWARDS, i, 1);
					path.pop_back();
				}
				else if ( step_possible(DIRECTION_FORWARDS, i, 2) )
				{
					path.push_back(current_setup());
					make_step(DIRECTION_FORWARDS, i, 2);
					dfs();
					undo_step(DIRECTION_FORWARDS, i, 2);
					path.pop_back();
				}
				break;

			case DIRECTION_BACKWARDS:
				if ( step_possible(DIRECTION_BACKWARDS, i, 1) )
				{
					path.push_back(current_setup());
					make_step(DIRECTION_BACKWARDS, i, 1);
					dfs();
					undo_step(DIRECTION_BACKWARDS, i, 1);
					path.pop_back();
				}
				else if ( step_possible(DIRECTION_BACKWARDS, i, 2) )
				{
					path.push_back(current_setup());
					make_step(DIRECTION_BACKWARDS, i, 2);
					dfs();
					undo_step(DIRECTION_BACKWARDS, i, 2);
					path.pop_back();
				}
				break;
			}
		}
	}
	else
	{
		path.push_back(current_setup());
		path.push_back("Solved!\n");
		print();
		exit(0);
		return;
	}
}

/**
 * Fill in the vector with the inital states of the frogs.
 */
void graph::initialize_graph()
{
	for(int i = 0; i < 2*n+1; i++)
	{
		g.push_back(EMPTY);
	}
	for(int i = 0; i < n; i++)
	{
		g[i] = DIRECTION_FORWARDS;
		g[2*n-i] = DIRECTION_BACKWARDS;
	}
}

void graph::input()
{
	std::cout << "Enter number of frogs: ";
	std::cin >> n;
}

/**
 * Print the path(steps) to the solution
 */
void graph::print()
{
	for (unsigned int i = 0; i < path.size(); i++)
	{
		std::cout << path[i];
	}
}

bool graph::solved()
{
	for(int i = 0; i < n; i++)
	{
		if ( g[i] == DIRECTION_BACKWARDS && g[2*n-i] == DIRECTION_FORWARDS )
			continue;
		else
			return false;
	}
	return true;
}

bool graph::step_possible(direction_e dir, int position, int distance)
{
	if ( g[position + dir*distance] == EMPTY && (position + dir*distance) >= 0 && (position + dir*distance) < 2*n+1 )
		return true;
	else
		return false;
}

void graph::make_step(direction_e dir, int position, int distance)
{
	std::swap(g[position], g[position + dir*distance]);
}

void graph::undo_step(direction_e dir, int position, int distance)
{
	std::swap(g[position], g[position + dir*distance]);
}

graph::~graph() {
	// TODO Auto-generated destructor stub
}

