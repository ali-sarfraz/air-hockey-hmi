/**
 * @file player.h
 * @author Natalia Bohulevych
 * @brief Header file used to declare the player class.
 *
 * The player class is responsible for creating a standard structure for creating
 * storing and accessing player objects.
 *
 * @version 0.3
 * @date 2020-12-02
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <string>

#include "MessagePacket.h"
#include "MessageHandler.h"
#include "MessageLibrary.h"
#include <QMessageBox>

/**
 * @brief This class is responsible for storing and retrieving information regarding player objects
 *
 */
class player
{
public:
    player();
    player(std::string, int, unsigned int);
    ~player(){}

    //set
    void setName(std::string name);
    void setpType(unsigned int type);

    //get
    std::string getName();
    int getRating();
    unsigned int getType();

private:

    /**
     * @brief String to store the name of the player
     * 
     */
    std::string pName;

    /**
     * @brief integer to store the rating of the player
     * 
     */
    int pRating;

    /**
     * @brief unsigned integer to store the type of the player (Human, Accessability, or AI)
     * 
     */
    unsigned int pType;

    /**
     * @brief unsigned integer to store the table mode of the air-hockey game
     * 
     */
    unsigned int mode;
};

#endif // PLAYER_H
