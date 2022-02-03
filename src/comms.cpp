/**
 * @file comms.cpp
 * @author Matthew Bertuzzi
 * @brief This file is responsible for testing the communication classes implemented for communicating
 * between the Raspberry PI and the embedded system, or a simulated embedded system
 * 
 * Currently, the only command tested is obtaining the AI Difficulty for testing purposes arround the structure of the communication code
 * @version 0.1
 * @date 2020-10-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <unistd.h>
#include "MessagePacket.h"
#include "MessageHandler.h"
#include "MessageLibrary.h"


int main(){

    sleep(2);

    //Send a valid message to simulated embedded system to obtain the AI difficulty
    // std::cout<<"Send a valid message to the simulated embedded system to obtain the AI difficulty:"<<std::endl; 

    // std::vector<int> returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_AI_ACTIVE_STATE);

    // if(returnVal[0] < 0){
    //    std::cout<<"ERROR> Did not receive expected message response"<<std::endl; 
    // }
    // else{
    //     std::cout<<"MsgID: "<<returnVal[0]<<std::endl;
    //     std::cout<<"AI Difficulty: "<<returnVal[1]<<std::endl;
    // }


    // sleep(2);

    // //Set AI Difficulty to check setters:
    // std::cout<<"Send a valid message to the simulated embedded system to set the AI difficulty:"<<std::endl; 

    // returnVal = MessageHandler::instance().sendMessage(M_RPI_SET_AI_ACTIVE_STATE, TO_STRING(ML_ACTIVE));
    // if(returnVal[0] < 0){
    //    std::cout<<"ERROR> Did not receive expected message response"<<std::endl; 
    // }
    // else{
    //     std::cout<<"MsgID: "<<returnVal[0]<<std::endl;
    // }


    // sleep(2);



    // //Send a valid message to simulated embedded system to obtain the AI difficulty to verify that it is persistent through a game
    // std::cout<<std::endl;
    // std::cout<<"Send a valid message to the simulated embedded system to obtain the AI difficulty to verify that it is persistent through a game:"<<std::endl; 

    // returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_AI_ACTIVE_STATE);

    // if(returnVal[0] < 0){
    //    std::cout<<"ERROR> Did not receive expected message response"<<std::endl; 
    // }
    // else{
    //     std::cout<<"MsgID: "<<returnVal[0]<<std::endl;
    //     std::cout<<"AI Difficulty: "<<returnVal[1]<<std::endl;
    // }

    // sleep(2);

    


    // //Send an invalid message to the embedded system
    // std::cout<<std::endl;
    // std::cout<<"Send an invalid message to the simulated embedded system:"<<std::endl; 

    // returnVal = MessageHandler::instance().sendMessage("INVALID MESSAGE");

    // if(returnVal[0] < 0){
    //    std::cout<<"ERROR> Did not receive expected message response"<<std::endl; 
    // }
    // else{
    //     std::cout<<"MsgID: "<<returnVal[0]<<std::endl;
    //     std::cout<<"AI Difficulty: "<<returnVal[1]<<std::endl;
    // }


    // sleep(2);


    std::cout<<"Send a message to the simulated embedded system to get the game state:"<<std::endl; 

    std::vector<int> returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_GAME_ACTIVE_STATE);

    if(returnVal[0] < 0){
       std::cout<<"ERROR> Did not receive expected message response"<<std::endl; 
    }
    else{
        std::cout<<"MsgID: "<<returnVal[0]<<std::endl;
        std::cout<<"Active Game State: "<<returnVal[1]<<std::endl;
    }

    sleep(5);

    std::cout<<"Send a message to the simulated embedded system to start the game:"<<std::endl; 

    returnVal = MessageHandler::instance().sendMessage(M_RPI_SET_GAME_ACTIVE_STATE, TO_STRING(ML_ACTIVE));

    if(returnVal[0] < 0){
       std::cout<<"ERROR> Did not receive expected message response"<<std::endl; 
    }
    else{
        std::cout<<"MsgID: "<<returnVal[0]<<std::endl;
    }

    //For a 20 second game, receive any goals that may have been scored:
    int count = 0;

    while(count < 20){
        sleep(1);
        returnVal = MessageHandler::instance().unsolicitedQueueGet();
        if(returnVal[0] < 0){
            std::cout<<"No goal was scored"<<std::endl; 
        }
        else{
            std::cout<<"GOAL!!!"<<std::endl;
            std::cout<<"Side: "<<returnVal[1]<<std::endl; 
            std::cout<<"Speed: "<<returnVal[2]<<std::endl; 
        }
        
        
        count++;
    }


    std::cout<<"Send a message to the simulated embedded system to end the game:"<<std::endl; 

    returnVal = MessageHandler::instance().sendMessage(M_RPI_SET_GAME_ACTIVE_STATE, TO_STRING(ML_INACTIVE));

    if(returnVal[0] < 0){
       std::cout<<"ERROR> Did not receive expected message response"<<std::endl; 
    }
    else{
        std::cout<<"MsgID: "<<returnVal[0]<<std::endl;
    }


    //For a 20 second game, receive any goals that may have been scored: (No goals should be scored here)
    count = 0;

    while(count < 20){
        sleep(1);
        returnVal = MessageHandler::instance().unsolicitedQueueGet();
        if(returnVal[0] < 0){
            std::cout<<"No goal was scored"<<std::endl; 
        }
        else{
            std::cout<<"GOAL!!!"<<std::endl;
            std::cout<<"Side: "<<returnVal[1]<<std::endl; 
            std::cout<<"Speed: "<<returnVal[2]<<std::endl; 
        }
        
        
        count++;
    }


    return 0;

}