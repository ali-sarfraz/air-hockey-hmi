/**
 * @file gameoutcome.h
 * @author Sanjayan Kulendran
 * @brief The gameOutcome struct provides a database-friendly structure to store game data
 * @version 1.0
 * @date 2020-11-30
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef GAMEOUTCOME_H
#define GAMEOUTCOME_H

#include<string>

/**
 * @brief The gameOutcome struct provides a database-friendly structure to store game data
 */
struct gameOutcome{

    std::string playerAName; ///<Name of player A in the game
    std::string playerBName; ///<Name of player B in the game
    std::string matchID; ///<unique ID to associate each game to a match

    unsigned long playerAScore; ///<final score of player A
    unsigned long playerBScore; ///<final score of player B
    unsigned long tableMode; ///<table mode configuration


};

#endif // GAMEOUTCOME_H
