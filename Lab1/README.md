# Window Programming Laboratories Repository

## Personal Information

**Student:** Bizdiga Stanislav

**Group:** FAF-151

**Year:** 2017

_Red Pill_

## Laboratory Work 1

## Title

Window. Window handling. Basic window’s form elements

## Contents
  - Win32 API
  - GIT
  - Programming Style Guidelines
  - Window
  - Button
  - Text Input
  - Text

## Objectives:
  - Understanding and using CLI (basic level)
  - Administration of a remote linux machine using SSH
  - Ability to work remotely (remote code editing)
  - Ability to work with VCS

## Executed Tasks:
  - **Mandatory Tasks:**
    - Create a Windows application
    - Choose a _Programming Style Guideline_ that you'll follow
    - Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size) 50%
    - Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size) 50%
    - Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
  - **Tasks With Points:**
    - Make elements to fit window on resize **(1 pt)**
    - Make elements to interact or change other elements (1 pt for 2 different interactions) **(2 pt)** 
    - Change behavior of different window actions (at least 3). **(1 pt)**
    - Write your own PSG (you can take existent one and modify it) and argue why it is better (for you) **(1 pt)**
  - **Additional Tasks:**
    - Additional taks done for fun
    
    
    
   
## Theoretical work procedure:

Chosen PSG: Geotechnical Software Services C++ PSG as a base guideline, but covered in my way. 

http://geosoft.no/development/cppstyle.html

Mainly my way of doing it implies making an aesthetically harmonious, blocky code, based on segments that are self-explainatory. Grouping it this way allows fast access and clear understanding of what a specific area of code is about and what it does.

In this laboratory work I concentrated at grasping the new concept of "messages", which isn't like linear coding I am used to.

Starting out a great help for me was the book of Charles Petzold's - "Programming Windows", 5th Edition. Also the course notes I have from Winodows Programming lectures and obviously microsoft helpful resources from http://msdn.microsoft.com were of good use.

It is undeniable though, that without googling I wouldn't have reached to the actual point. There are numerous resources online that are more than helpful in order to learn what is required to do at any moment.


  
  
# Practical work procedure:

## Create windows application

Simple - go to file->new->project->win32gui 

## Create text inputs/elements,buttons

Fairly easy, in WM_CREATE you use CreateWindowsEx function with the EDIT or BUTTON parameter. You also need to make sure each message is defined, and then used in WM_COMMAND accordingly to access the case you require.

## Create text in middle screen that due resizing remains there

Done, but due design features, it was moved to a right bottom align mode. The modern, copyright style/way.

# Features:
My program is an application to have a good laugh. You're being tested how good of a joker you are. You can use the left input box to talk to the computer, and see its feedback on the right output box. Obviously it's just a simulation of AI yet so don't be mad if cpu doesn't get your joke.

# Functionality:
- button to center the app at middle of screen
- button to shrink the app to its minimum area
- button to "tell" a joke to your smart computer
- button to "laugh" in order to make it awkward, or funny perhaps?
- area that shows the moods and thoughts of your smart computer
- area that allows changing/inputting text/jokes
- resizing to a limited minimum/maximum sizes
- elements are nicely aligned, text fits to the middle
- funny message pop-ups to almost each user action
- over 7+ genuine reactions from your brilliant cpu

# Who needs facebook friends when you have this!

## Conclusion

It was fun, it was hard, it was horribly confusing, but it was worth it! This first laboratory work marked a important shift in my life. I learned a lot of concepts: version control with github, messages on the base which my operation system works, ways of developing gui applications, and much more. It is great to observe new ways to interact with the computational world.



