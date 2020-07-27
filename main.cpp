#include <cstdlib>  	// for the random number generation
#include <time.h>   	// to randomize the random number seed
#include <termios.h>	// to being able to handle key input
#include <sys/ioctl.h>	// to use ioctl() which is used to handle the key input
#include <unistd.h>		// to use sleep(). (Linux exclusive. for windows include <Windows.h>)

#include "coord.h"
#include "snake.h"
#include "world.h"


/*
REFERENCES:

I Got the functions _kbhit() and sleepcp() from Suraj Singh Bisht.
Blog:'www.bitforestinfo.com', Github:'https://github.com/surajsinghbisht054'

Links:
    https://www.quora.com/With-which-function-can-I-replace-kbhit-in-C++-because-the-header-conio-h-doesnt-exist-in-linux

Ubuntu Users (try to run the program frst, this may be optional to install):
    sudo apt-get install libncurses5-dev libncursesw5-dev
*/


// --------------------------------------------------------------------------------------------------------


// http://www.flipcode.com/archives/_kbhit_for_Linux.shtml
// Check if KeyBoard is Pressed Or Not
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

	static const coord dir_up(0,1), dir_down(0,-1), dir_left(-1,0), dir_right(1,0);	// define unit vectors for the direction the snake can go ('static' to not create the objects multiple times)

    if (keypress == 'd' || keypress == '6') {
        // change snake direction to RIGHT
        snek.set_direction(dir_right);

    } else if(keypress == 'a' || keypress == '4') {
        // change snake direction to LEFT
		snek.set_direction(dir_left);

    } else if(keypress == 'w' || keypress == '8') {
		// change snake direction to UP
		snek.set_direction(dir_up);

    } else if(keypress == 's' || keypress == '2') {
        // change snake direction to DOWN
		snek.set_direction(dir_down);

    } else if(keypress == 'q' || keypress == 'z' || keypress == 'c') {
        
		std::cout << "<- safely exiting program ->" << std::endl;
        exit(EXIT_SUCCESS);
    }

}



int main() {
	
	coord worldSize(100, 30);	// size of the playing field (horizontal_size, vertical_size)
	coord food_pos;	// tracks position of the food
	char k;	// holds user key input

	// init a playing field of the given size:
	world za_warudo(worldSize.get_x(), worldSize.get_y());
	// construct snake object with given starting position, direction, length, and possible movement range (which is the same as the world size):
	snake snek(coord(worldSize.get_x()/2, worldSize.get_y()/2), coord(-1,0), 4, za_warudo.get_size_x(), za_warudo.get_size_y());

	// initialize rng:
	std::srand(worldSize.get_x()*worldSize.get_y());	// use the world size as a seed for the rng
	//std::srand(time(0)*10000); // or: gererate a seed for random number generation (need to include <time.h> for this)


	// start main game loop. Stops if the snake is dead
	while (!snek.get_is_dead()) {

		sleepcp(200);	// sleep by a certain amount each step to make the game speed possible to handle for humans

        if(_kbhit()) {

			std::cin >> k; // get an input character
			key_input_reaction(snek, k);
        }

		// TODO: implement the actual game loop logic
		// first generate food and update world, then print it. after that make the snake do stuff like growing or moving
		za_warudo.print_world();
		break;
	}


	return 0;
}