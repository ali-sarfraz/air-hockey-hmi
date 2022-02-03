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

player::player()
{
    //set default
    pName = "";
    pRating = 0;
    pType = 0;
}

player::player(std::string name, int rating, unsigned int type)
{
    pName = name;
    pRating = rating;
    pType = type;
}

//Setting Methods

void player::setName(std::string name)
{
    pName = name;
}


void player::setpType(unsigned int type)
{
    pType = type;
}

//Getter Methods

std::string player::getName()
{
    return pName;
}

int player::getRating()
{
    return pRating;
}

unsigned int player::getType()
{
    return pType;
}
