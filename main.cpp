#include <cstdlib>  	// for the random number generation
#include <time.h>   	// to randomize the random number seed
#include <termios.h>	// to being able to handle key input
#include <sys/ioctl.h>	// to use ioctl() which is used to handle the key input
#include <unistd.h>		// to use sleep(). (Linux exclusive. for windows include <Windows.h>)

#include "coord.h"
#include "snake.h"
#include "world.h"

/*
__author__ = "Cédric Jockel"
__email__  = "cedric.jockel@stud.uni-frankfurt.de"
__GitHub__ = "https://github.com/xcex"
__version__ = "1.0.0"	// initial release
*/

// --------------------------------------------------------------------------------------------------------

// http://www.flipcode.com/archives/_kbhit_for_Linux.shtml
// Check if keyboard is pressed or not
int _kbhit() {

	int bytesWaiting;
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}


// Cross-platform sleep function
void sleepcp(const int milliseconds) {

    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end) { }
}


// handle the reaction to key input
// change the direction of the snake (w,a,s,d) or exit program (q,z,c)
void key_input_reaction(snake& snek, const char keypress) {

	static const coord dir_up(0,-1), dir_down(0,1), dir_left(-1,0), dir_right(1,0);	// define unit vectors for the direction the snake can go ('static' to not create the objects multiple times)

	// as a switch-statement is not possible for chars/strings, if/else-clauses have to be used (with brakes to make them esentially work like a switch)
    if (keypress == 'd' || keypress == '6') {
        // change snake direction to RIGHT
		if (snek.get_direction() == dir_left) {return;}	// if the current direction is the opposite of the set direction, no change to the direction is made
        snek.set_direction(dir_right);
		return;	// return if the option has been chosen

    } else if(keypress == 'a' || keypress == '4') {
        // change snake direction to LEFT
		if (snek.get_direction() == dir_right) {return;}	// if the current direction is the opposite of the set direction, no change to the direction is made
		snek.set_direction(dir_left);
		return;	// return if the option has been chosen

    } else if(keypress == 'w' || keypress == '8') {
		// change snake direction to UP
		if (snek.get_direction() == dir_down) {return;}	// if the current direction is the opposite of the set direction, no change to the direction is made
		snek.set_direction(dir_up);
		return;	// return if the option has been chosen

    } else if(keypress == 's' || keypress == '2') {
        // change snake direction to DOWN
		if (snek.get_direction() == dir_up) {return;}	// if the current direction is the opposite of the set direction, no change to the direction is made
		snek.set_direction(dir_down);
		return;	// return if the option has been chosen

    } else if(keypress == 'q' || keypress == 'z' || keypress == 'c') {
        // emergency exit the program
		std::cout << "<- safely exiting program ->" << std::endl;
        exit(EXIT_SUCCESS);
    }

}


// creates a food while checking that the food is not on top of the snake
coord create_food(snake snek, coord worldSize) {

	bool generate_success = false;
	coord food;	// story the food position

	// randomly generate a possible coordinate until it does not overlap the snake
	while (!generate_success) {

		food = coord(rand()%worldSize.get_x(), rand()%worldSize.get_y());	// rng a position inside the grid range
		generate_success = true;

		// check if the food overlaps with the snake:
		for (unsigned i = 0; i < snek.get_length(); ++i) {
			if (food == snek.get_element(i)) {
				generate_success = false;	// the snake overlaps with the food. The while-loop needs to be repeated
				break;	// break out of the for-loop
			}
		}
	}
	return food;
}


int main() {
	
	// for Lunux/Unix systems, get the size (number of colums and rows) of the terminal window
	struct winsize shell_window;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &shell_window);

	coord worldSize(shell_window.ws_col-2, shell_window.ws_row-6);	// size of the playing field (horizontal_size, vertical_size). '-2' and '-6' to account for the 'GUI' borders
	coord food_pos;	// tracks position of the food
	char k;	// holds user key input

	int timestep_beginning = 120, timestep_min = 40; // the time in [ms] one tick takes at start and at minimum
	int f = 7;	// scaling factor for the decay of the time-tick. MUST be bigger then 1

	// initialize a playing field of the given size:
	world za_warudo(worldSize.get_x(), worldSize.get_y());
	// construct snake object with given starting position, direction, length, and possible movement range (which is the same as the world size):
	snake snek(coord(worldSize.get_x()/2, worldSize.get_y()/2), coord(-1,0), 5, za_warudo.get_size_x(), za_warudo.get_size_y());

	// initialize rng:
	std::srand(worldSize.get_x()*worldSize.get_y());	// use the world size as a seed for the rng
	//std::srand(time(0)*10000); // or: gererate a seed for random number generation (need to include <time.h> for this)

	// generate an initial food in a position
	food_pos = create_food(snek, worldSize);

	// start main game loop. Stops if the snake is dead
	while (!snek.get_is_dead()) {

		sleepcp( f*(timestep_beginning-timestep_min)/(f+za_warudo.get_score()) + timestep_min );	// sleep by a certain amount (in milliseconds) each step to make the game speed possible to handle for humans
		//TODO: make the timing dependant on score so the game becomes progressively faster over time

        if(_kbhit()) {

			std::cin >> k; // get an input character
			key_input_reaction(snek, k);	// use the input to perform an action on the snake
        }

		// update the positions of the snake and food on the grid
		za_warudo.update(snek, food_pos);
		// draw the screen with the new positions of the snake and the food
		za_warudo.print_world();

		// check whether the snake moved onto a food tile (in this case, if the head of the snake overlaps with the position of the food). if yes, grow and move it
		if(snek.get_element(snek.get_length()-1) == food_pos) {

			// the food has been taken, now grow it and increase the score
			snek.grow();
			za_warudo.increment_score();

			food_pos = create_food(snek, worldSize);	// the last food has been eaten. create a new one
		}
		else {	// if-else statement is to avoid that the snake grows AND moves in one tick because that can lead to the snake colliding with the wall if a food spawns at a border
			snek.move();	// move the snake using the new direction which was set by the key input
		}

		snek.check_collision();	// checks collision of the snake with the border and/or itself. If it hit something, it dies (game ends)

	}

	//TODO: insert "you lost" screen
	std::cout << "The snake died! The game is over!" << std::endl;

	return 0;
}