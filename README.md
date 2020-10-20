# shell-snake
A simple OOP version of 'Snake' to run in the Linux shell (on Ubuntu based systems)   
   
The project implements the classic 'Snake' game! This instance runs in the Linux shell (Ubuntu/Unix based systems).   
Control the snake and collect the foods to gain score. With each food the snake becomes longer. It cannot hit itself or the wall!   

This version is made for solely educational and recreational purposes by Cédric Jockel.   
email: <cedric.jockel@stud.uni-frankfurt.de>
GitHub: <https://github.com/xcex>   


How to use:
- Compile using 'g++ *.cpp' and run using './a.out'
- Controls (key presses):
	- movement: 'w': up; 'a': left; 's': down; 'd': right  
	- utility: 'q' or 'c' or 'z' quit the program prematurely
- Change game paramatres in 'main.cpp':
	- change parameters 'timestep_beginning', 'timestep_min' and 'f'(decay factor) to affect the behaviour of the decay-function (see patchnotes v.1.1.0)
	- change parameters in constructor of the snake object: (starting position, starting direction, start length). I Recommend leaving everything on default


***

**VERSIONS AND CHANGELOG:**   

- v1.1.0
	- The playing field now takes the same size as the currently open console window
	- The timestep of each tick now gets smaller after more food has been collected. The decay function f(score) can be changed using the parameters 'timestep_beginning', 'timestep_min' and 'f'(decay factor). The function has the form 'f(s)= f*(timestep_beginning-timestep_min) / (f+s) + timestep_min'

- v1.0.1
	- Fixed a bug where the snake would move two tiles per tick when eating a food

- v1.0.0 
	- Initial release

***

**LIST OF KNOWN BUGS:**  
- [FIXED] When playing with worldSize(60, 20) and when the food spawns in the upper right corner, the snake dies when touching the food. This could possibly also happen for other world sizes. Just spawning on the border is fine though so maybe the problem is only when the food spawns in a corner. (possible cause: the snake grows AND moves in one iteration, making the snake move twice and run into the wall)

***
  
**LIST OF POSSIBLE FEATURES:**  
- Game speed changes with respect to the score (program sleeps for shorter amounts of time) so it becomes progessively faster with increasing score. Need to implement some kind of shortest time step.  
- Implement a "You Lost" or "Game Over" screen  
- Animation for when the snake is dying   
- A kind of power-up which makes the points go up more but make the game run faster  
- Bigger feature ideas: Different difficulty settings; title screen; (local) leaderboards and highscore system   
   
***

**REFERENCES:**    
    
I got the functions _kbhit() and sleepcp() from Suraj Singh Bisht.    
Blog:'<www.bitforestinfo.com>', Github:'<https://github.com/surajsinghbisht054>'   
   
Links:    
Regarding the kbhit function (took the links from Suraj Singh Bisht):  
https://www.quora.com/With-which-function-can-I-replace-kbhit-in-C++-because-the-header-conio-h-doesnt-exist-in-linux  
http://www.flipcode.com/archives/_kbhit_for_Linux.shtml    

For Ubuntu users (try to run the program frst, this may be optional to install):  
sudo apt-get install libncurses5-dev libncursesw5-dev
