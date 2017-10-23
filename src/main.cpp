/*
 * main.cpp
 *
 *  Created on: Oct 20, 2017
 *      Author: kristiyan
 */

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

static std::vector<int> g;

static int n;

void initialize_graph();
void input(void);
void print(void);

enum direction_e
{
	DIRECTION_BACKWARDS = -1,
	EMPTY = 0,
	DIRECTION_FORWARDS = 1,
};

void initialize_graph()
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

void input()
{
	std::cout << "Enter the number of frogs in each direction: ";
	std::cin >> n;
	initialize_graph();
}

void graph_input()
{
	int from, to;
	scanf("%d %d", &from, &to);

}

void print(std::vector<int>& graph)
{
	for(int i = 0; i < 2*n + 1; i++)
	{
		if ( graph[i] == DIRECTION_BACKWARDS )
			std::cout << "< ";
		else if (graph[i] == EMPTY )
			std::cout << "_ ";
		else
			std::cout << "> ";
	}
	std::cout << std::endl;
}

bool solved(std::vector<int>& graph)
{
	for(int i = 0; i < n; i++)
	{
		if ( graph[i] == DIRECTION_BACKWARDS && graph[2*n-i] == DIRECTION_FORWARDS )
			continue;
		else
			return false;
	}

	return true;
}

bool step_possible(direction_e dir, std::vector<int> graph, int position, int distance)
{
	if ( graph[position + dir*distance] == EMPTY && (position + dir*distance) >= 0 && (position + dir*distance) < 2*n+1 )
		return true;
	else
		return false;
}

void make_step(direction_e dir, std::vector<int>& graph, int position, int distance)
{
	std::swap(graph[position], graph[position + dir*distance]);
}

void undo_step(direction_e dir, std::vector<int>& graph, int position, int distance)
{
	std::swap(graph[position], graph[position + dir*distance]);
}

void dfs(std::vector<int> graph)
{
	if ( !solved(graph) )
	{
		for(int i = 0; i < 2*n+1; i++)
		{
			bool printed = false;
			switch(graph[i])
			{
			case DIRECTION_FORWARDS:
				if ( step_possible(DIRECTION_FORWARDS, graph, i, 1) )
				{
					print(graph);
					make_step(DIRECTION_FORWARDS, graph, i, 1);
					dfs(graph);
					undo_step(DIRECTION_FORWARDS, graph, i, 1);
				}
				else if ( step_possible(DIRECTION_FORWARDS, graph, i, 2) )
				{
					print(graph);
					make_step(DIRECTION_FORWARDS, graph, i, 2);
					dfs(graph);
					undo_step(DIRECTION_FORWARDS, graph, i, 2);
				}
				break;

			case DIRECTION_BACKWARDS:
				if ( step_possible(DIRECTION_BACKWARDS, graph, i, 1) )
				{
					print(graph);
					make_step(DIRECTION_BACKWARDS, graph, i, 1);
					dfs(graph);
					undo_step(DIRECTION_BACKWARDS, graph, i, 1);

				}
				else if ( step_possible(DIRECTION_BACKWARDS, graph, i, 2) )
				{
					print(graph);
					make_step(DIRECTION_BACKWARDS, graph, i, 2);
					dfs(graph);
					undo_step(DIRECTION_BACKWARDS, graph, i, 2);
				}
				break;
			}
		}
	}
	else
	{
		print(graph);
		std::cout << "Solved!\n";
		exit(0);
		return;
	}
}

int main()
{
	input();
	dfs(g);
}
