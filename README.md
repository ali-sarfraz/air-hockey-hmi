# Care Hockey HMI Project

## About
Arcade gaming is a common activity for many individuals in their leisure time with their friends or family,
but it is easy to note that most if not all of the common arcade games do not provide any accessibility
features, and are geared towards providing entertainment for people with little to no physical disabilities.

An air-hockey table is one such example, where a person who is wheelchair-bound or diagnosed
with a physical disability will have difficulty1playing the game as intended. Having a table with means for
controlling the paddle without physically having to stand and hold it would be beneficial in such
circumstances. Another aspect to consider is the rising and critical need for social distancing during a
global pandemic, where most two-player arcade games such as air hockey are no longer deemed safe to
play. In this instance, it would be safer to have an autonomous mechanism act as an opponent and still
play the game while social distancing.

While the table itself is being designed and built as part of a separate capstone project, the aim of this
project is focused on designing and implementing a Human-Machine-Interface (HMI) for the table. The
interface will present information and statistics about the game as it plays out, as well as process inputs by
the player for controlling the autonomous opponent, and other accessibility features.

## Structure
The repository is split into multiple directories for convinience. The *project* directory is an amalgamation of all the source files
as seen in the Qt Creator IDE. The .pro file initiates the project as it needs to build in the IDE, and was the main source for
editing and compiling the application.

The *inc* directory contains all the application header files seperately in case they need to be inspected individually. The *src*
directory similarily contains all of the program source files for easier access and sorting. Finally, the *docs* repository is a
colection of all the doxy-generated documentation about the project, should the TAs ever want to learn about the particular
implementation of the project.

## Building
The project is most easily assessible by downloading the latest version of Qt Creator on your local linux machine and initializing
the *CareHockeyHMI.pro* file to set everything up. Alternatively, you may also build it from the command line by running
the following commands inside the project directory;

* qmake CareHockeyHMI.pro
* make

This will compile a binary executable, which can then be run by the following command;

* ./CareHockeyHMI

## Application
The application is split into multiple windows that allows the user to configure the game and table settings for a game of air
hockey. These currently include the user match settings, table configuration, player settings, and databse access.

### Match Configuration
Allows users to modify the number of games in each match, the time limit for each game, the score limit, and also how the user
wishes to play the game, i.e first to the score limit or until the game timer runs out.

### Table Configuration
Allows users to configure the table for multiple modes, such as conventional play with no accessibility features, enabled
accessibility features, and a completely autonomous opponent to emulate a player vs robot situation. If the last mode is
selected, the menu offers a difficulty setting for the AI player. You may also adjust the ambient lighting of the table using
the RGB slider, and set the air speed for each match as well.

### Player Settings
Allows users to input their names so that the GUI will display these accordingly. The player names are also saved along with the
game stats into a database so that the players may return to review their performance over time.

### Databse Access
Allows users to interact with a dynamic SQLite database that keeps track of all the game information, such as player names, player
scores, and the table mode when the game was being played. Each match has a unique ID number to ensure that no duplicate data is
returned, and may subsequently be used to distinguish games from different matches.


## Assistance 
Should the marking TAs have any questions about how the repository is structured, or problems compiling any of the programs, please
do reach out to any one of the team members and we can offer an alternative solution for demonstrating the work we have accomplished.

## Team Members
* Matthew Bertuzzi: 250797232, mbertuz@uwo.ca
* Mohammad Sarfraz: 250860782, msarfra2@uwo.ca
* Mohammed Iqbal: 250861168, miqbal57@uwo.ca
* Natalia Bohulevych: 251049015, nbohulev@uwo.ca
* Sanjayan Kulendran 250846374, skulend2@uwo.ca