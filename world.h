#ifndef world_HEADER
#define world_HEADER

#include <vector>
#include <iostream>
#include <iomanip>	// for leading zeros in the headline of the graphical output
#include "coord.h"
#include "snake.h"


class world {

	public:
	world();
	world(const unsigned, const unsigned);	// size_of_grid_x size_of_grid_y

	void reset();	// resets the grid to be empty
	void print_world();	// print the grid including the border
	void update(snake, coord);	// use the snake's position and food positions to update the grid
	void increment_score();
	
	void set_element(const unsigned, const unsigned, const std::string); // set one individual entry of the array
	std::string get_element(const unsigned, const unsigned); // get element (j,i)
	unsigned get_score();
	void set_score(const unsigned);
	coord get_size();
	int get_size_x();
	int get_size_y();

	private:
	coord worldsize;	// x-size and y-size of the world grid
	std::vector<std::string> grid;	// main grid which stores the position of the snake and all items (excluding the border). It has 'size_y*size_x' elements
	unsigned score = 0;

};


#endif