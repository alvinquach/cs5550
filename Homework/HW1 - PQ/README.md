## Compiling the Project

To compile this project in VC++, make sure all the .h files are added under Header Files, and all the .cpp files are added under Source Files. 

The following files should be added under the Header Files in VC++:
* Ball.h
* ColorRGB.h
* Draw.h
* Input.h
* main.h
* Physics.h
* Random.h
* Scene.h
* Vector.h
* Vector2f.h
* Window.h


The following files should be added under the Source Files in VC++:
* Ball.cpp
* ColorRGB.cpp
* Draw.cpp
* Input.cpp
* main.cpp
* Physics.cpp
* Random.cpp
* Scene.cpp
* Vector2f.cpp


Also, make sure that glut.h, glut32.lib, and glut32.dll are inside the project directory (or modifiy the #include headers accordingly).



## Ball Selection

There are multiple ways to select a ball. In addition to using the number keys as specified in the assignment instructions, the user can also select the ball by left-clicking or right-clicking on a ball.

When left-clicking on the ball, the ball will be locked to the mouse movement until the left-click is released (more on this later). That means the velocity of the ball will most likely change just by left clicking on it. To select a ball using the mouse without changing its position/velocity, use right-click instead.

The currently selected ball will be indicated by a black outline around the ball. To deselect a ball, press '0' on the keyboard.



## Adding New Balls

As per the assignment instructions, ressing 'n' will add a new ball to the screen as long as the limit has not been reached. The ball will be added in the center of the world/screen, and can potentially overlap with existing balls. In the case that the newly added ball does overlap with any existing ball, it will be non-solid and will not be able to physically affect any other balls. This condition is lifted as soon as the new ball has cleared the other balls and is no longer overlapping with any of them.



## Altering Ball Movement Using Mouse

As previously mentioned, pressing down the left mouse button on a ball will 'lock' the position of the ball to the mouse. The ball can then be dragged around by using the mouse. When the left mouse button is released, the ball will be freed from the mouse.

When a ball is being draged around by the mouse, it will remain solid and can collide with other balls. However, the ball that is being dragged by the mouse will be treated as having infinite mass, so it can easily knock away the other balls. Its mass is reset to normal once the left mouse button is released, and will resume moving at its position and velocity from the last mouse update.

There is a restriction placed to prevent the user from dragging the ball outside of the window.



## Altering Ball Properties Using Keyboard Input

The up and down arrow keys will increase and decrease the selected ball's speed, respectively. However, there is a limit to the balls maximum speed when it is increased in this method. The limit is based on the ball's total momentum; the larger the ball, the lower the speed is limited to when using the up arrow. This limit does not affect the speed change due to elastic collision, only when using the up arrow.

Similarly, the page up and page down button can increase and decrease the selected ball's radius, respectively, within a limited range.

The user can press 's' to set the speeds of all the balls to 5. This is handy when things get out of hand and the balls end up moving too fast.
