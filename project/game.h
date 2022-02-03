/**
 * @file game.h
 * @author Sanjayan Kulendran
 * @brief Header file used to declare the Game class.
 * The Game class represents a game with two players, where each player scores points via Goal objects
 * Each goal object results in an increment of one point to the player it is credited to (either player A or player B)
 * No calculations are made as to the winner of the game, all that is set is a flag indicating the game is finished
 * when a player reaches a pre-defined score threshold, or if stopGame() is called
 * If specified at time of construction, the game class will throw a POSIX timer interrupt after a specified number of game seconds
 * (game seconds are counted after startGameWithTimer() is called, and not counted after pauseGame() or endGame()
 * Otherwise this functionality can be ignored to handle game timing externally
 *
 * @version 1.1
 * @date 2020-11-30
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef GAME_H
#define GAME_H

#include "goal.h"  //Game is composed of goals
#include<vector>  //Vector for storing array of goals
#include<ctime>  //Keep track of the time - remove if removing alarm functions
#include<unistd.h> // set up timer interrupt

#include<iostream> //debug

//Game class header

/**
 * @brief The Game class represents a game with two players, where each player scores points via Goal objects
 * Each goal object results in an increment of one point to the player it is credited to (either player A or player B)
 * No calculations are made as to the winner of the game, all that is set is a flag indicating the game is finished
 * when a player reaches a pre-defined score threshold, or if stopGame() is called
 * If specified at time of construction, the game class will throw a POSIX timer interrupt after a specified number of game seconds
 * (game seconds are counted after startGameWithTimer() is called, and not counted after pauseGame() or endGame()
 * Otherwise this functionality can be ignored to handle game timing externally
 */
class game
{

private:

    //Player Scores
    unsigned long playerAScore; //!< Stores the score of player A (always >= 0)
    unsigned long playerBScore; //!< Stores the score of player B (always >= 0)

    //Game Status variables
    bool gameFinished; //!< Status of the game, if true, game has finished
    bool gameWinOnScore; //!< Is true if the game wins on a player reaching a certain score
    bool gameUsesAlarm; //!< Is true if the game object throws a SIGALRM that must be handled
    unsigned long gameScoreLimit; //!< If the game has a score limit, it is stored using this variable
    unsigned long gameTimeLimit; //!< If the game has a time limit, it is stored using this variable (seconds)
    unsigned long gameStartTime; //!< Stores the UNIX time when the game has started for internal reference

    //Goal Vector
    std::vector<goal> goalList; //!< A vector of goal objects, storing all the goals in the game

public:

    /**
     * @brief game - Game constructor, game must be instantiated with atleast wintype and corresponding threshold (time[s] or points)
     * @param doesGameFinishOnScore - True if the game wins on reaching a point threshold, false otherwise
     * @param gameWinValue - If game finishes on score, this is the score in points, otherwise this is an optional parameter taking time in seconds if using internal alarm functionality
     */
    game(bool doesGameFinishOnScore, unsigned gameWinValue = 0);


    /**
     * @brief game - Basic copy constructor for game
     * @param copyGame
     */
    game(const game &copyGame);

    /**
     * @brief startGameWithAlarm - Function to start/resume the game with SIGALRM
     */
    void startGameWithAlarm();

    /**
     * @brief pauseGame - Function to pause the game if using SIGALRM
     */
    void pauseGame();

    /**
     * @brief pauseGame - Function to stop/end the game
     */
    void endGame();

    /**
     * @brief addGoal - Function to add a goal
     * @param goalSpeed - goal speed (unspecified units)
     * @param onBSide - true if scored on side B, i.e. if Player A has scored
     */
    void addGoal(unsigned goalSpeed, bool onBSide);

    /**
     * @brief getPlayerAScore - Function that returns the score of player A
     * @return Player A score as unsigned int
     */
    unsigned long getPlayerAScore();

    /**
     * @brief getPlayerBScore - Function that returns the score of player B
     * @return Player B score as unsigned int
     */
    unsigned long getPlayerBScore();

    /**
     * @brief getDoesGameFinishOnScore - Function that indicates if the game finishes on a score threshold
     * @return boolean that is 'true' if the game finishes on a score
     */
    bool getDoesGameFinishOnScore();

    /**
     * @brief isGameFinished - Function that indicates if the game internally considers itself complete
     * @return boolean that is 'true' if the game has set itself to being complete
     */
    bool isGameFinished();

    /**
     * @brief getGoalList - Function that gives access to the vector of goals
     * @return vector iterator for goal objects, starting at the first goal score in the game
     */
    std::vector<goal>::iterator getGoalList();

};

#endif // GAME_H
