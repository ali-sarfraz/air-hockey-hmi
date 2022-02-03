/**
 * @file player.cpp
 * @author Natalia Bohulevych
 * @brief Implementation file used to implement the tableconfigurationsettings class
 * @version 0.3
 * @date 2020-12-02
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "player.h"
#include <stdio.h>
#include <string>

/**
 * @brief Construct a new player object. This constructor is used to create a new player object with default values.
 */
player::player()
{
    //set default
    pName = "";
    pRating = 0;
    pType = 0;
}

/**
 * @brief Construct a new player object. This constructor is used when by the main menu when it initializes player objects
 * and by playersettingswindow class to hold any changes the user makes in the GUI.
 */
player::player(std::string name, int rating, unsigned int type)
{
    pName = name;
    pRating = rating;
    pType = type;
}

//Setting Methods
/**
 * @brief This function is intended to set the player name based on the given string value
 *
 * @param name => name input by user
 */
void player::setName(std::string name)
{
    pName = name;
}

/**
 * @brief This function is intended to set the player player type based on the given unsigned integer value
 *
 * @param type => desired player type
 */
void player::setpType(unsigned int type)
{
    pType = type;
}

//Getter Methods

/**
 * @brief This function is intended to return the currently saved player name
 *
 * @return pName string => current player name
 */
std::string player::getName()
{
    return pName;
}

/**
 * @brief This function is intended to return the currently saved player rating
 *
 * @return pName int => current player rating
 */
int player::getRating()
{
    return pRating;
}

/**
 * @brief This function is intended to return the currently saved player type
 *
 * @return 0 => human player
 * @return 1 => accessibility player
 * @return 2 => robot player
 */
unsigned int player::getType()
{
    return pType;
}
