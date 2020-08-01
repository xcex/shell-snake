# shell-snake
A simple OOP version of 'Snake' to run in the Linux shell (on Ubuntu based systems)   
   
The project implements the classic 'Snake' game! This instance runs in the Linux shell (Ubuntu/Unix based systems)   

How to use:
- Compile using 'g++ *.cpp' and run using './a.out'
- Controls (key presses):
	- movement: 'w': up; 'a': left; 's': down; 'd': right  
	- utility: 'q' or 'c' or 'z' quit the program prematurely
- Change game paramatres in 'main.cpp':
	- change 'worldSize(x,y)': x: width of the playing field; y: height of the field (in character sizes)
	- change parameters in constructor of the snake object: (starting position, starting direction, start length). I Recommend leaving everything on default


***

**VERSIONS AND CHANGELOG:**   

v1.0.0 Initial release

***

**LIST OF KNOWN BUGS:**  
- When playing with worldSize(60, 20) and when the food spawns in the upper right corner, the snake dies when touching the food. This could possibly also happen for other world sizes. Just spawning on the border is fine though so maybe the problem is only when the food spawns in a corner. (possible cause: the snake grows AND moves in one iteration, making the snake move twice and run into the wall)

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
Blog:'www.bitforestinfo.com', Github:'https://github.com/surajsinghbisht054'   
   
Links:    
Regarding the kbhit function (took the links from Suraj Singh Bisht):  
https://www.quora.com/With-which-function-can-I-replace-kbhit-in-C++-because-the-header-conio-h-doesnt-exist-in-linux  
http://www.flipcode.com/archives/_kbhit_for_Linux.shtml    

For Ubuntu users (try to run the program frst, this may be optional to install):  
sudo apt-get install libncurses5-dev libncursesw5-dev
