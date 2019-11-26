# opengl-smiley-editor
An OpenGL application where you can place smileys on a blank canvas,
move them around, resize them and delete them.

# Features
The following lists all features inside the application:

## Selecting Smileys
To select a smiley, left click the smiley. Once a smiley has been selected, its colour and will be brought to the front of the canvas.

Because smileys can occlude each other, you can only select visible parts of the smiley.

## Moving Smileys
Left-click and drag a smiley to move it. Note that the initial left-clicking will also select it.

## Resizing Smileys
Ctrl, left-click and drag left and right to resize the smiley.
Dragging to the left will shrink the smiley, while dragging to the right will expand the smiley.

The smiley has a minimum and a maximum size however, and you cannot resize past that size. This can still be configured in the code, however.

## Creating New Smileys
Right-click anywhere to create a new smiley. That smiley will be selected and brought to the front of the canvas.

You can create a maximum of 10 smileys, though this can be changed in the code.

## Deleting Individual Smileys
With a smiley selected, hit the Delete key to delete that smiley. A poofing animation will play at the smiley's position when it is deleted.

## Deleting All Smileys
To delete all smileys from the program, hold down the Shift key, then hit the Delete key. All smileys will play the poofing animation at its position.

## Saving and Loading Smileys
Smileys are saved automatically when quitting the program. There are loaded the next time the program is opened.

The smileys are saved in a file "smileys.txt".

Note that if there are no smileys saved, the program will automatically generate one for you the next time it loads.