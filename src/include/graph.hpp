/*
 * graph.hpp
 *
 *  Created on: Oct 24, 2017
 *      Author: devteam
 */

#ifndef SRC_GRAPH_HPP_
#define SRC_GRAPH_HPP_

#include <vector>
#include <string>

enum direction_e
{
    DIRECTION_BACKWARDS = -1,
    EMPTY = 0,
    DIRECTION_FORWARDS = 1,
};

class graph {
public:
    graph();
    void dfs();
    void initialize_graph();
    void input();
    void print();
    virtual ~graph();
private:
    int n;
    std::vector<std::string> path;
    std::vector<int> g;
    
    bool solved();
    bool step_possible(direction_e dir, int position, int distance);
    void make_step(direction_e dir, int position, int distance);
    void undo_step(direction_e dir, int position, int distance);
    std::string current_setup();
};

#endif /* SRC_GRAPH_HPP_ */
