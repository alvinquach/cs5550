## Compiling the Project

To compile this project in VC++, make sure all the .h files are added under Header Files, and all the .cpp files are added under Source Files. 

Also, make sure that glut.h, glut32.lib, and glut32.dll are inside the project directory (or modifiy the #include headers accordingly).

The window size is set to 960*720. This can be adjusted as necessary inside Window.cpp.



## Camera Control

The basic camera controls were programmed to mimic Blender:

- Hold down the middle mouse button to rotate the camera about its "look at" point.
- Press shift and then hold down the middle mouse button to pan the view. This will move the camera along its u and v directions. The camera's "look at" point will also move along with it.
- Press ctrl and then hold down the middle mouse button to zoom in and out. This will move the camera along its n direction. The camera's "look at" point will remain stationary during zooming. The camera will not be able to zoom past its "look at" point.
- When the distance between the camera's eye and look at point is zero, the camera will appear to rotate about its own axes. It will also not be able to pan. These effects can also be observed in Blender, will remain until the camera is zoomed back out and away from its look at point.

Unfortunately, the version of glut that we are using doesn't support the mouse wheel, so we cannot use it to zoom in and out.

In addition, as per the assignment instructions, the camera can automatically focus on the object (or on the world orgin if the object has not been created yet) by pressing the 'F' key. The camera can also automatically rotate around the object by pressing 'M'.

An additional feature that was not part of the requirements is the ability to set the camera to look directly at the YZ plane, XZ plane, and XY plane by pressing 'X', 'Y', and 'Z', respectively. Being able to align the camera to the XY plane may be helpful when drawing the polyline (see below).



## Object Modeling and Rendering

When drawing the poly line, the points will be added on the XY plane where the user clicked, if possible. If the distance of the point on the XY plane where the user clicked is too far from the camera (farther than the far-viewplane, which is 100 units), then the point will not be added. In addition, if the user clicked on an area that does not contain the XY plane (ie. when the camera is facing away from the XY plane), then no point will be added.

The polyline's vertices and the edges connecting the vertices are drawn on screen to aid the placement of the points. The user can clear the polyline at anytime by pressing 'C'.

The rest of the object modeling and rendering features have been implemented as close to the requirments as possible. THE ONLY CHANGE IS THAT 'H' IS USED TO CHANGE THE COLOR/MATERIAL OF THE OBJECT INSTEAD OF 'G'. This change was necessary because the 'G' button is used to translate the object (see below).



## Object Controls

Once again, the basic camera controls were programmed to mimic Blender:

- Hold right click and start dragging to initiate translate mode. You can let go of right click once the object starts moving. In translate mode, the object will follow the mouse movement and will move parallel to the camera's viewplane.
- You can also press 'G' to initiate translate mode.
- Press 'R' to initiate rotate mode. In rotate mode, the object will rotate about the camera's n-axis. The angle of rotation is controlled by mouse position.
- Press 'S' to initiate scale mode. In scale mode, the objet is uniformally scaled, based on the initial and final distance of the mouse cursor from the object's position.
- While a transfomation mode is active, you can press 'G', 'S', or 'R' at anytime to swtich to a new modes; any unsaved transformations will be reset before switching to the new mode.
- While a transfomation mode is active, you can press right click at anytime to cancel transfomation and reset the object back to its last saved state.
- While a transfomation mode is active, you can press left click or spacebar at anytime to save the transformation.

Object controls will not work for the polyline (it was purposely designed to be this way).