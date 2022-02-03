/**
 * @file tableconfigurationsettings.cpp
 * @author Mohammad Iqbal
 * @brief Implementation file used to implement the tableconfigurationsettings class
 * @version 0.3
 * @date 2020-11-29
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "tableconfigurationsettings.h"


tableconfigurationsettings::tableconfigurationsettings()
{

    //Send signal to get table config from the table emulator
    std::vector<int> returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_TABLE_MODE);

    //incase message was not recieved then set to default value
    if (returnVal[0] > 0 )
    {
         tableMode = uint(returnVal[1]);
    }
    else
    {
        tableMode = 0; // 0 = freeplay mode (human v human), 1 = accessiblity controlled opponent, 2 = robotic opponent
    }

    //Send signal to get ai difficulty from the table emulator
    returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_AI_DIFFICULTY);

    //incase message was not recieved then set to default value
    if (returnVal[0] > 0 )
    {
         aiDifficulty = uint(returnVal[1]);
    }
    else
    {
        aiDifficulty = 0; // 0 = Beginner (default), 1 = Indermediate, 2 = Expert
    }

    //Send signal to get air speed from the table emulator
    returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_TABLE_AIR_SPEED);

    //incase message was not recieved then set to default value
    if (returnVal[0] > 0 )
    {
         tableAirSpeed = uint(returnVal[1]);
    }
    else
    {
        tableAirSpeed = 100; // Set to max CFM as default
    }

    //Send signal to get lighting state from the table emulator
    returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_TABLE_LIGHTING);

    //incase message was not recieved then set to default value
    if (returnVal[0] > 0 )
    {
         tableLighting = returnVal[1];
    }
    else
    {
        tableLighting =0x000000;     //initialize the table lighting to off (RGB hex value)
    }

}

//Setting Methods

void tableconfigurationsettings::setTableMode(unsigned int chosenMode)
{
    tableMode = chosenMode;
}


void tableconfigurationsettings::setAiDifficulty(unsigned int chosenDiff)
{
    aiDifficulty = chosenDiff;
}


void tableconfigurationsettings::setTableLighting(int chosenLighting)
{
    tableLighting = chosenLighting;

}


void tableconfigurationsettings::setTableAirSpeed(unsigned int chosenAirSpeed)
{
    if (chosenAirSpeed <= 0)
    {
        tableAirSpeed = 0;
    }
    else if (chosenAirSpeed >= 100)
    {
        tableAirSpeed = 100;
    }
    else
    {
        tableAirSpeed = chosenAirSpeed;
    }
}

//Getter Methods


unsigned int tableconfigurationsettings::getTableMode()
{
    return tableMode;
}



unsigned int tableconfigurationsettings::getAiDifficulty()
{
    return aiDifficulty;
}



unsigned int tableconfigurationsettings::getTableAirSpeed()
{
    return tableAirSpeed;
}


int tableconfigurationsettings::getTableLighting()
{
    return tableLighting;
}
