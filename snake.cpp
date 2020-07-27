#include "snake.h"

// constructors
snake::snake() {

	std::cout << "No valid arguments given. Could not initialize the snake!" << std::endl;
	exit(EXIT_FAILURE);
}
snake::snake(const coord start_pos, const coord start_direction, const unsigned length_in, const int range_x_in, const int range_y_in) { // starting pos, starting direction, length, x_range, y_range

	// initialize some member variables
	direction_facing = start_direction;
	max_range = coord(range_x_in, range_y_in);
	snake_len = length_in;

	// check if the snake at start is too large
	if( (length_in > range_x_in) || (length_in > range_y_in) ) {
		std::cout << "Range is smaller than the snake! Increase the size of the playing field" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	// create the snake body with the given length with the head (last array element) being at the starting position:
	snake_elements.resize(snake_len);	// give it the initial length specified
	snake_elements[snake_len-1] = start_pos;	// allocate the first element of the snake. This is the 'head' of the snake.

	// fill the snake elements with the respective positions
	for (int i = snake_len - 2; i >= 0; --i) {

		snake_elements[i] = snake_elements[i+1] - direction_facing;	// propagate the coordinates of the snake elements back into the array
	}
	std::cout << "segfault debug" << std::endl;
	// check, if the snake is on the grid/withing allowed bounds:
	for (unsigned i = 0; i < snake_len; ++i) {
		if ( (snake_elements[i].get_x() > max_range.get_x()) || (snake_elements[i].get_x() < 0) || 
			 (snake_elements[i].get_y() > max_range.get_y()) || (snake_elements[i].get_y() < 0) ) {
			
			// if the snake is out of bound, relocate the snake to the middle of the grid:
			snake_elements[snake_len-1] = coord((int)(range_x_in/2), (int)(range_y_in/2) );

			// fill the snake elements with the respective positions
			for (int j = snake_len - 2; j >= 0; --j) {

				snake_elements[j] = snake_elements[j+1] - direction_facing;	// propagate the coordinates of the snake elements back into the array
			}
		}
	}

}

// member functions
void snake::move() {

	for (unsigned i = 0; i < snake_len - 1; ++i) {

		snake_elements[i] = snake_elements[i+1];	// move all positions of the elements one over, leaving the last two entries identical
	}
	snake_elements[snake_len-1] += direction_facing;	// update the first element
}
void snake::grow() {

	coord head_pos = snake_elements[snake_len-1];	// save the current head position
	snake_elements.push_back(head_pos + direction_facing);	// this becomes the new head
	snake_len++;	// increase the length of the snake when it grows. This is Important!
}
void snake::check_collision() {

	// First, check if the snake is inside the world bound.
	// It is enough to just check the 'head element (last element of the array) since the others snake parts only propagated to previously known positions. 
	// Only the head assumes a new position after moving so it is enough to just check the position of the head and it's pos relative to the other parts of the snake
	if ( (snake_elements[snake_len-1].get_x() > max_range.get_x()) || (snake_elements[snake_len-1].get_x() < 0) ||
		 (snake_elements[snake_len-1].get_y() > max_range.get_y()) || (snake_elements[snake_len-1].get_y() < 0) ) {

		is_dead = true;	// this means that the snake went out of bound i.e. it hit one of the walls
	}

	// check if the head moved into an existing part of the snake. If true, the snake dies
	for (unsigned i = 0; i < snake_len - 1; ++i) {

		if ( snake_elements[i] == snake_elements[snake_len-1] ) {
			is_dead = true;
		}
	}
}

// setter and getter
void snake::set_direction(const coord new_dir) {
	
	direction_facing = new_dir;	// update the new direction the snake is looking
}
unsigned snake::get_length() {
	
	return snake_len;
}
coord snake::get_element(const unsigned i) {
	
	return snake_elements[i];
}
bool snake::get_is_dead() {
	
	return is_dead;
}
void snake::set_is_dead(const bool dead_in) {
	
	is_dead = dead_in;
}
bool snake::get_food_taken() {

	return food_taken;
}
void snake::set_food_taken(const bool food_in) {

	food_taken = food_in;
}