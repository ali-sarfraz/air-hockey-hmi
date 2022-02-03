/**
 * @file MessagePacket.cpp
 * @author Matthew Bertuzzi
 * @brief Implementation file used to implement the MessagePacket class
 * @version 0.1
 * @date 2020-10-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "MessagePacket.h"


unsigned int MessagePacket::calculateChecksum(){
    
    //initialize the checksum to zero prior to calculating
    unsigned int check = 0;

    //Use a constant iterator to enforce const-correctness and prevent overriding of the contained string
    for(std::string::const_iterator it = this->messageString.cbegin(); it != this->messageString.cend(); it++){
        
        check = (check + (unsigned int)(*it)) % 100;
    }

    return check;

}


MessagePacket::MessagePacket(std::string messageString, unsigned int messageID){

    this->messageID = messageID;
    this->messageString = messageString;

    //Calculate the checksum of the passed message
    this->checksum = this->calculateChecksum();

}


MessagePacket::MessagePacket(std::string data){
    
    //Create a string to compare when parsing
    std::string token;

    //Convert the read data line into a stream that we can tokenize as an input
    std::istringstream stream(data);

    //First, we parse the string to get the token corresponding to the message id:
    getline(stream, token, '|'); //Discard first '|' token
    getline(stream, token, '|'); //Parse second tokenized string to get the message ID

    //Convert our token into a string stream and then pipe it into an integer:
    std::istringstream mID(token);
    mID >> this->messageID;

    //Now we need to get the messageString from the packet passed:
    getline(stream, token, '>'); //Discard first '>' token
    getline(stream, token, '<'); //Keep '<' token and store within messageString

    this->messageString = token;

    //Finally, we must read in the checksum passed:
    getline(stream, token, '|'); //Keep '|' token and convert to the checksum

    //Convert our token into a string stream and then pipe it into an integer:
    std::istringstream cs(token);
    cs >> this->checksum;

}


bool MessagePacket::validateChecksum(){

    //Calculate the checksum based on the data received
    unsigned int val = this->calculateChecksum();

    //Determine whether the calculated checksum is equal to the checksum read in from the message
    if(this->checksum != val){
        return false;
    }
    else{
        return true;
    }

}


std::string MessagePacket::getFullMessage(){

    //Combine the attributes of the message packet to produce a string
    return "|" + std::to_string(this->messageID) + "|>" + this->messageString + "<" + std::to_string(this->checksum) + "|";

}