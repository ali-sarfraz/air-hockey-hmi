/**
 * @file usermatchsettings.cpp
 * @author Mohammad Iqbal
 * @brief Implementation file used to implement the usermatchsettings class
 * @version 0.1
 * @date 2020-11-11
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "usermatchsettings.h"


usermatchsettings::usermatchsettings()
{
//Setting match settings to default values
    numOfGames = 3;
    gameTimeLimit = 5; //Time in minutes
    scoreThreshold = 7;
    gameVictoryType = 1; //Set to max goals in time limit by default

}

//Setter method definitions

void usermatchsettings::setNumberOfGames(unsigned int chosenNumOfGames)
{
    numOfGames = chosenNumOfGames;
}


void usermatchsettings::setGameTimeLimit(unsigned int chosenTimeLimit)
{
    gameTimeLimit = chosenTimeLimit;
}


void usermatchsettings::setScoreThreshold(unsigned int chosenThreshold)
{
    scoreThreshold = chosenThreshold;
}


void usermatchsettings::setGameVictoryType(unsigned int chosenVicType)
{
    gameVictoryType = chosenVicType;
}

//Getter method definitions

unsigned int usermatchsettings::getNumberOfGames()
{
    return numOfGames;
}


unsigned int usermatchsettings::getGameTimeLimit()
{
    return gameTimeLimit;
}


unsigned int usermatchsettings::getScoreThreshold()
{
    return scoreThreshold;
}


unsigned int usermatchsettings::getGameVictoryType()
{
    return gameVictoryType;
}
