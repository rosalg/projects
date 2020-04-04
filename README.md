# projects
Hello and welcome to Gilbert Rosal's project repository. This file describes each project.

This repository contains all of Gilbert's coding projects starting from Fall 2018.

At the moment there are three projects:
    
1. Stanford Scrappers

This project is contained in the Stanford Scrappers folder. The folder contains the Java code for Gilbert's 106A Graphics Contest entry 
Stanford Scrappers, an independently developed 2-player fighting game that uses a keyboard interface to allow players to menu, read 
instructions and view credits, select from one of 6 maps, then fight one another. Gilbert finished this project in exactly 1 week over 
Thanksgiving break of 2018.

The main code for the game is in the Game folder, in GraphicsClass.java. This file contains the main update loop, keeping track of game state, I/O from the user on the keyboard, and updating player sprites based on key presses.

The assets folder contains any audio or jpg files used in the game. I TAKE NO CREDIT FOR ANYTHING IN THESE FOLDERS.

The CharacterModels folder contains all the java files declaring different body parts of the sprite, then combines them all into a
GCompound so that each drawn shape does not have to be drawn individually.

Lastly, the Characters folder contains the modules for firing a projectile and the players actually fighting.

2. Coin 

This project is made up of the Assets, Packages, and Project Settings folders. The game, titled Coin, is a single-player puzzle app developed using C# and Unity2D that has mirror reflections of the sprite that both move when one moves, but are faced with a different set of obstacles. The player must get both sprites to an exit at the same time. This game is in the midst of development, containing 10 levels, a self-made soundtrack, and self-made artwork. The goal for initial release is 30 levels.

The Assets folder contain self-describing folders, as well as scripts for the game in C#. The scripts are labelled to correspond with
what each script manages. The only script I did NOT make myself was the CharacterController2D, however I made modifications of my own
to make it work for the purposes of this game.

3. SuperSmashCS107E

This project is made up of four primary modules: gameplay, controller, player, gl.

The gameplay module is in charge of managing all sprites, updating information based on information communicated by the controller module.
The controller module is in charge of initializing pins on the Raspberry Pi as I/O pins that then read information from the Gamecube
remotes, utilizing getter functions to obtain information about the buttons and joysticks contained in a 64 bit array.
The player module is in charge of handling the individual player, controlling jumping, movement, and redrawing of the player.
Lastly, the gl module contains helper functions to draw to the framebuffer.

I worked on the gameplay, controller, and player modules. My partner worked on the GL module, extending it from the assignment we
had in the class.
