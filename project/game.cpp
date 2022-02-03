/**
 * @file game.cpp
 * @author Sanjayan Kulendran
 * @brief Implementation file used to implement the Game class
 * @version 1.1
 * @date 2020-11-30
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "game.h"

//Game constructor, game must be instantiated with atleast wintype and corresponding threshold (be it time or points)
game::game(bool gameFinisheshOnScore, unsigned gameWinValue)
{
    //Initialize all game status values to zero
    playerAScore = 0;
    playerBScore = 0;
    gameFinished = false;

    //If the game finishes on score
    if(gameFinisheshOnScore){

        //Set the wintype to reflect this
        gameWinOnScore = true;
        //Set the corresponding win threshold
        gameScoreLimit = gameWinValue;
        gameTimeLimit = 0;

    }

    //otherwise, the game finishes with a time limit
    else{

        //Set the wintype to reflect this
        gameWinOnScore = false;
        //Set the corresponding win threshold
        gameScoreLimit = 0;
        gameTimeLimit = gameWinValue;

    }

}


//Copy constructor for game
game::game(const game &copyGame){

    //Player Scores
    playerAScore = copyGame.playerAScore;
    playerBScore = copyGame.playerBScore;

    //Game Status variables
    gameFinished = copyGame.gameFinished;
    gameWinOnScore = copyGame.gameWinOnScore;
    gameUsesAlarm = copyGame.gameUsesAlarm;
    gameScoreLimit = copyGame.gameScoreLimit;
    gameTimeLimit = copyGame.gameTimeLimit;
    gameStartTime = copyGame.gameStartTime;

    //Goal Vector
    goalList = copyGame.goalList;
}


//Function to start the game throwing an alarm when complete
void game::startGameWithAlarm(){

    //Record the starting time
    gameStartTime = std::time(NULL);

    //Set a system alarm for the end time (if no time limit, no alarm will be set)
    alarm(gameTimeLimit);

    //Indicate that this game uses csignal's alarm
    gameUsesAlarm = true;


}

//Function to pause the game
void game::pauseGame(){

    //Clear the pending game alarm, if the game used one
    if(gameUsesAlarm) alarm(0);

    //If the game win type is a time limit
    if(!gameWinOnScore){

        //The game time limit is the current remainder of time
        gameTimeLimit = gameTimeLimit - (std::time(NULL) - gameStartTime);

    }


};

//Function to stop/end the game
void game::endGame(){

    //clear any pending alarms
    if(gameUsesAlarm) alarm(0);

    //If the game win type is a time limit
    if(!gameWinOnScore){

        //Set the remaining time limit to 0 to prevent further execution
        gameTimeLimit = 0;

    }

    //Indicate that the game is completed
    gameFinished = true;

};

//Function to add a goal, given the speed and side
void game::addGoal(unsigned goalSpeed, bool onBSide){


    //Create a new goal with the given information, and add it to game goal vector
    goalList.push_back(goal(goalSpeed, std::time(NULL), onBSide));

    //If the goal was on the robot side
    if(onBSide){

        //Increment Player A's score
        playerAScore++;

    }
    //Otherwise if it's on the human/Player A side
    else{

        //Increment Player B's score
        playerBScore++;
    }

    //If we are going by the first to reach a certain score, and either player A or B has reached the thershold
    if ((gameWinOnScore) && ((playerAScore >= gameScoreLimit) || (playerBScore >= gameScoreLimit))){

        //The game has been won, end the game
        endGame();
    }

};

//Function that returns the score of player A
unsigned long game::getPlayerAScore(){

    //Return player A's score
    return playerAScore;

};

//Function that returns the score of player B
unsigned long game::getPlayerBScore(){

    //Return player B's score
    return playerBScore;

};

//Function that returns true if the game finishes on a score and not a timer
bool game::getDoesGameFinishOnScore(){

    //Return the status of the game
    return gameWinOnScore;


};

//Function that returns true if the game is finished
bool game::isGameFinished(){

    //Return the status of the game
    return gameFinished;


};

//Function that returns an iterator of the goal list
std::vector<goal>::iterator game::getGoalList(){

    //Return an iterator from the front of the goal list
    return goalList.begin();

};
