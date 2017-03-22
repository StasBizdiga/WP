# Windows Programming Laboratory Work #2

## Title
Advanced Form Elements. Child Windows. Basics of Working With Keyboard.

## Contents
* The Keyboard
* Child Window Controls
  * Scroll Bar
  * Listbox
* Menus and Other Resources
* Dialog Boxes

### Laboratory work Requirements:
  - for _Basic Level_ (grade 5 || 6) you should be able to:
    * Create a Windows application what will dispaly a dialog box on some event (ex. on clicking some button)
    * Add a system menu to your application with at least 3 items (add actions to that items)
    * Hook keyboard input. Add 2 custom events for 2 different keyboard combinations (ex. change window background on ctrl+space) 
  - for _Normal Level_ (grade 7 || 8) you should be able to:
    * Realize the tasks from _Basic Level_.
    * Add a scroll bar that will change any visible parameter of any other element (color of a text) OR other 2 scroll bars that will manage main window size or position
  - for _Advanced Level_ (grade 9 || 10) you should be able to:
    * Realize the tasks from _Normal Level_.
    * Customize your application by adding an icon and using different cursor in application
    * Add a listbox and attach some events when any element is accessed (clicked)
  - for _Bonus Point Tasks_ :
    * Use a scroll bar to scroll through application working space. Scroll should appear only when necessary (eg. when window width is smaller than 300px)


## Executed tasks
Basic Level:

    - Create a Windows application what will display a dialog box on some event (ex. on clicking some button)
    
    - Add a system menu to your application with at least 3 items (add actions to that items)
   
    - Hook keyboard input. Add 2 custom events for 2 different keyboard combinations


Normal Level:

    - Realize the tasks from Basic Level.

    - Add 2 scroll bars that will manage main window size or position
    
    
 ## Features


- On clicking the MICRO button, the window shrinks to its minimal size. It then displays a dialog box as required by the first task.



- There are system menus with different actions to them:


Menu - Exit 	   : exits the window

Functions - Micro  : makes the window smallest possible

Functions - Center : moves the window to the middle of the screen

Info - About		: displays an "about" joke message box

Info - Help			: displays a help joke message box



- When pressing Shift and then any arrow key: UP,DOWN,LEFT,RIGHT you get a message depending on which key you pressed. Here I press SHIFT+RIGHT:



- Scroll bars are used to move and resize the window:


Vertical scrolling: moves window to a constant position (top-left: x=0,y=0)

Horizontal scrolling: resizes the window to a constant of x=300 y=300



