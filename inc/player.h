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
    /**
     * @brief Construct a new player object. This constructor is used to create a new player object with default values.
     */
    player();

    /**
     * @brief This function is intended to set the player name based on the given string value
     *
     * @param name => name input by user
     */
    player(std::string, int, unsigned int);


    ~player(){}

    /**
     * @brief This function is intended to set the player name based on the given string value
     *
     * @param name => name input by user
     */
    void setName(std::string name);

    /**
     * @brief This function is intended to set the player player type based on the given unsigned integer value
     *
     * @param type => desired player type
     */
    void setpType(unsigned int type);

    /**
     * @brief This function is intended to return the currently saved player name
     *
     * @return pName string => current player name
     */
    std::string getName();

    /**
     * @brief This function is intended to return the currently saved player rating
     *
     * @return pName int => current player rating
     */
    int getRating();

    /**
     * @brief This function is intended to return the currently saved player type
     *
     * @return 0 => human player
     * @return 1 => accessibility player
     * @return 2 => robot player
     */
    unsigned int getType();

private:
    /**
     * @brief Player name
     */
    std::string pName;

    /**
     * @brief Player score
     */
    int pRating;

    /**
     * @brief Player type
     */
    unsigned int pType;

    /**
     * @brief Table mode.
     */
    unsigned int mode;
};

#endif // PLAYER_H
