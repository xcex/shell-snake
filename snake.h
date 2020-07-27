#ifndef snake_HEADER
#define snake_HEADER

#include <vector>
#include <iostream>

#include "coord.h"


class snake {

	public:
	snake();
	snake(const coord start_pos, const coord start_direction, const unsigned length_in, const int range_x_in, const int range_y_in);	// starting pos, starting direction, length, x_range, y_range

	void move();
	void check_collision();	// checks collision with itself and the world boarder
	void grow();

	void set_direction(const coord);
	unsigned get_length();
	coord get_element(const unsigned);
	bool get_is_dead();
	void set_is_dead(const bool);
	bool get_food_taken();
	void set_food_taken(const bool);

	private:
	coord direction_facing;	// the direction in which the snake is looking and will go to next
	coord max_range;	// the maximal x-range/boundary and y-range/boundary the snake can move in. This is equal to the size of the playing field grid
	unsigned snake_len;	// length of the snake
	std::vector<coord> snake_elements;	// holds the body of the snake
	
	bool is_dead = false;
	bool food_taken = false;
};


#endif