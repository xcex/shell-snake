#include "world.h"

// constructors
world::world() {

	std::cout << "No valid arguments given. Could not initialize the world!" << std::endl;
	exit(EXIT_FAILURE);
}
world::world(const unsigned x_size, const unsigned y_size) {	// horizontal size, vertical size

	worldsize = coord(x_size, y_size);

	// check if the world is big enough to support the snake, and playfield header etc.
	if (x_size < 60) {
		std::cout << "Please increase horizontal size of the grid to 60 ore more!" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (x_size < 15) {
		std::cout << "Please increase vertical size of the grid to 15 ore more!" << std::endl;
		exit(EXIT_FAILURE);
	}

	grid.resize(x_size*y_size, " ");	// initialize the array to be filles with blank characters
}

// member functions
void world::reset() {

	std::fill(grid.begin(), grid.end(), " ");	// fill the whole grid array with blanck-characters again
}
void world::print_world() {
	
	// clears the current console (cross-plattform compatible)
	#if defined _WIN32
		system("cls");
	#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
	#elif defined (__APPLE__)
		system("clear");
	#endif

	/*	The playing field will look like the following:

	######################################################
	# 'snake' made by Cedric Jockel     # score: 000     #
	######################################################
	|                                                    |
	|                                                    |
	|                                                    |
	|                                                    |
	|                                                    |
	|                                                    |
	|                                                    |
	|                                                    |
	|                                                    |
	|                                                    |
	|                                                    |
	O----------------------------------------------------O
	
	Note: the border and the geader are not part of the grid!
	*/

	// create the header of the playing field:

	for (unsigned i = 0; i < worldsize.get_x() + 2; ++i) {	// +2 because the border is not part of the grid and needs to be accounted for
		std::cout << "#";	// print the first line made of '#'
	}
	std::cout << std::endl;

	// prepare the second line
	std::string header_line_start = "# 'Snake' made by Cedric Jockel";
	std::string header_line_end = "     #";
	
	// need a padding string to get to the right length of the second line 
	// (note: +2 because of the bigger size of this line cpmpared to gridsize.x; -10 because of 'score ' and the leading zeros of the score)
	// padding made out of blanks to insert between 'header_line_start' and 'score'
	std::string header_line_padding(( worldsize.get_x()- 10 + 2 - header_line_start.length() - header_line_end.length() ), ' ');

	// print the second line
	std::cout << header_line_start << header_line_padding << "score ";
	std::cout << std::setfill('0') << std::setw(4) << score << header_line_end << std::endl;

	for (unsigned i = 0; i < worldsize.get_x() + 2; ++i) {
		std::cout << "#";	// print the third line made out of '#'
	}
	std::cout << std::endl;

	// print the actual playfield including the border

	for (unsigned j = 0; j < worldsize.get_y(); ++j) {
		
		std::cout << "|";	// print left border
		for (unsigned i = 0; i < worldsize.get_x(); ++i) {
	
			std::cout << grid[j*worldsize.get_x() + i];
		}

		std::cout << "|" << std::endl;	// print right border
	}

	// print the lower border
	std::cout << "O";
	for (unsigned i = 0; i < worldsize.get_x(); ++i) {
		std::cout << "-";	// print the lower boarder (last line) made out of '-'
	}
	std::cout << "O" << std::endl;

}
void world::update(snake snek, coord food) {

	// update the grid with the snake and food positions and assign different characters to the grid to represent them accordingly:

	// update the position of the food:
	grid[food.get_y()*worldsize.get_x() + food.get_x()] = "%"; // set this element to be food

	// update the position of the snake
	for (unsigned i = 0; i < snek.get_length()-1; ++i) {

		grid[ snek.get_element(i).get_y() * worldsize.get_x() + snek.get_element(i).get_x() ] = "O"; // set this element to be a part of the snake body
	}
	// the last element of the array is the head of the snake:
	grid[ snek.get_element(snek.get_length()-1).get_y() * worldsize.get_x() + snek.get_element(snek.get_length()-1).get_x() ] = "0";

}
void world::increment_score() {

	score++;
}

// setter and getter
void world::set_element(const unsigned j, const unsigned i, const std::string strg_in) {
	
	grid[j*worldsize.get_x() + i] = strg_in;
}
std::string world::get_element(const unsigned j, const unsigned i) {

	return grid[j*worldsize.get_x() + i];
}
unsigned world::get_score() {
	
	return score;
}
void world::set_score(const unsigned sc_in) {

	score = sc_in;
}
coord world::get_size() {

	return worldsize;
}
int world::get_size_x() {
	
	return worldsize.get_x();
}
int world::get_size_y() {
	
	return worldsize.get_y();
}