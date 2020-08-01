# shell-snake
A simple OOP version of 'Snake' to run in the Linux shell (on Ubuntu based systems)   
   
The project implements the classic 'Snake' game! This instance runs in the Linux shell (Ubuntu/Unix bases systems)   

Project description here...   
    
**VERSION AND CHANGELOG:**   



**LIST OF KNOWN BUGS:**  
- When playing with worldSize(60, 20) and the food spawns in the upper right corner, the snake dies. This could possibly also happen for other world sizes. Just spawning on the border is fine though so maybe the problem is only when the food spawns in a corner.  
  
  
**LIST OF POSSIBLE FEATURES:**  
- Game speed changes with respect to the score (program sleeps for shorter amounts of time)  
- Animation for when the snake is dying   
- A kind of power-up which makes the points go up more but make the game run faster  
   
   
**REFERENCES:**    
    
I got the functions _kbhit() and sleepcp() from Suraj Singh Bisht.    
Blog:'www.bitforestinfo.com', Github:'https://github.com/surajsinghbisht054'   
   
Links:    
Regarding the kbhit function (took the links from Suraj Singh Bisht):  
https://www.quora.com/With-which-function-can-I-replace-kbhit-in-C++-because-the-header-conio-h-doesnt-exist-in-linux  
http://www.flipcode.com/archives/_kbhit_for_Linux.shtml    

For Ubuntu users (try to run the program frst, this may be optional to install):  
sudo apt-get install libncurses5-dev libncursesw5-dev
