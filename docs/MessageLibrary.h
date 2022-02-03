/**
 * @file MessageLibrary.h
 * @author Matthew Bertuzzi
 * @version 0.1
 * @date 2020-10-07
 * @brief Header file responsible for creating the library of valid string messages that can be sent to the embedded system
 * or received from the embedded system. The messages that can be sent must follow a standard structure, which is why they are
 * encoded in the library below, which is intended to be shared between the embedded system and the Raspberry PI. As a result, the
 * library must be C friendly

 * \n\n
 * The messages sent between the Raspberry PI and the embedded system will be NULL terminated and follow the structure indicated below:
 * 
 * "|MSG_ID|>MESSAGE:ARGUMENTS<CHECKSUM|"
 * 
 * In the above formatting:
 * MSG_ID = the ID of the message being sent or received (Used to identify matching messages)
 * MESSAGE = Indicates what detials are being exchanged or what is desired
 * ARGUMENTS = Values for specified data in the message that are being exchanged (If multiple, comma separated)
 * CHECKSUM = Value used to identify whether the passed message had any errors
 * 
 * Using the format above for messages, it makes it possible to tokenize the string for parsing
 * 
 * NOTE: Responses to a message will have the SAME MSG_ID and MESSAGE, but will differ in terms of arguements
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef MESSAGE_LIBRARY_H
#define MESSAGE_LIBRARY_H


#define GETTER_STRING "GET;"                                //!< Used defines the getter substring
#define SETTER_STRING "SET;"                                //!< Used defines the setter substring

//=========================================== STANDARD VALUES TO BE SENT ALONG WITH MESSAGES TO EITHER SYSTEM ===========================================

//Values used for defining activity states of subsystems:
#define ML_INACTIVE         0                               //!< Used when putting a subsystem in an inactive state
#define ML_ACTIVE           1                               //!< Used when putting a subsystem in an active state

//Values used for defining the table mode:
#define ML_STANDARD         0                               //!< Puts the table in standard (default) mode with two players playing against eachother
#define ML_ACCESSABILITY    1                               //!< Puts the table in accessability mode with one player using accessability controls
#define ML_AI               2                               //!< Puts the table in AI mode, with one player being controlled by an AI

//Values used to define the sides of the table:
#define ML_PLAYER_ONE_SIDE  0                               //!< Defines the side of the table where a human player will always play
#define ML_AI_SIDE          1                               //!< Defines the side of the table where a the AI and accesability systems are located

//Below, we define some macros to convert the defines above into strings when passed as parameters:
#define STRING(token)       #token                          //!< Intermediate step to get the value stored in the define to convert to a string
#define TO_STRING(token)    STRING(token)                   //!< Macro to call on define to convert the define's CONTENTS to a string



//=========================================== Messages to be sent to the embedded system from the Raspberry PI ===========================================
//Note: Messages sent from the Raspberry PI to the embedded system are indicated with RPI!


//Getters:
#define M_RPI_GET_AI_DIFFICULTY "GET; AI DIFFICULTY"         //!< Getter => Integer ranging from 1 to 10 for AI Difficulty
#define M_RPI_GET_AI_ACTIVE_STATE "GET; AI STATE"            //!< Getter => Inactive = 0, Active = 1 for defining if the table AI is active
#define M_RPI_GET_GAME_ACTIVE_STATE "GET; GAME STATE"        //!< Getter => Inactive = 0, Active = 1 ==> If Acitve, goal data will be sent when a goal is scored
#define M_RPI_GET_TABLE_MODE "GET; TABLE MODE"               //!< Getter => Standard = 0, Accessability = 1, AI = 2 for defining the mode of play for the table
#define M_RPI_GET_TABLE_LIGHTING "GET; LIGHTING VALUE"       //!< Getter => 24-bit RGB value for defining the lighting on the table
#define M_RPI_GET_TABLE_AIR_SPEED "GET; TABLE AIR SPEED"     //!< Getter => Integer ranging from 0 to 100 for setting the air speed for puck levitation

//Setters:
#define M_RPI_SET_AI_DIFFICULTY "SET; AI DIFFICULTY"         //!< Setter => Integer ranging from 1 to 10 for AI Difficulty
#define M_RPI_SET_AI_ACTIVE_STATE "SET; AI STATE"            //!< Setter => Inactive = 0, Active = 1 for defining if the table AI is active
#define M_RPI_SET_GAME_ACTIVE_STATE "SET; GAME STATE"        //!< Setter => Inactive = 0, Active = 1 ==> If Acitve, goal data will be sent when a goal is scored
#define M_RPI_SET_TABLE_MODE "SET; TABLE MODE"               //!< Setter => Standard = 0, Accessability = 1, AI = 2 for defining the mode of play for the table
#define M_RPI_SET_TABLE_LIGHTING "SET; LIGHTING VALUE"       //!< Setter => 24-bit RGB value for defining the lighting on the table
#define M_RPI_SET_TABLE_AIR_SPEED "SET; TABLE AIR SPEED"     //!< Setter => Integer ranging from 0 to 100 for setting the air speed for puck levitation


//=========================================== Messages to be sent to the Raspberry PI from the embedded system ===========================================
//Note: Messages sent from the embedded system to the Raspberry PI are indicated with EMB!


//Getters:

//Setters:
#define M_EMB_SET_GOAL_DATA "SET; GOAL DATA"                //!< Setter => Includes SIDE of goal and puck speed on entry: [SIDE, SPEED]


#endif /*MESSAGE_LIBRARY_H*/