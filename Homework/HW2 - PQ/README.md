## Compiling the Project

To compile this project in VC++, make sure all the .h files are added under Header Files, and all the .cpp files are added under Source Files. 

Also, make sure that glut.h, glut32.lib, and glut32.dll are inside the project directory (or modifiy the #include headers accordingly).

The window size is set to 960*540. This can be adjusted as necessary inside Window.h.



## Robot Control

In addition to the keys specified in the assignment, the robot arm can also be rotated using the left and right arrow keys.


## Throwing the Ball

If you hold 'a', you can delay throwing the ball. The ball will be thrown once you let go of 'a'.

You can also move the robot around while throwing the ball. The velocity of the thrown ball will be affected by the robot's velocity at the time the ball is released from the hand.