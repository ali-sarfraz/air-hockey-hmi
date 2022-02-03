/**
 * @file MessagePacket.h
 * @author Matthew Bertuzzi
 * @brief Header file used to declare the MessagePacket class.
 * The MessagePacket class is responsible for creating creating a standard structure for Messages
 * sent between the RaspberryPi and embedded system. With a standard structure to messages, they
 * are easier to manage and parse.
 * 
 * @version 1
 * @date 2020-12-02
 * 
 * NOTE: See \ref MessageLibrary.h for structure of messageString
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef MESSAGE_PACKET_H
#define MESSAGE_PACKET_H

#include <string>
#include <sstream>
#include <iostream>

//Message packet needs to take advantage of a library of messages that can be sent to the embedded system, or received from the embedded system

/**
 * @brief This class is responsible for organizing message packets to be sent to-and-from an embedded system responsible for controlling
 * the air hockey game.
 * 
 */
class MessagePacket{

    //Declare MessagePacket attributes
    private:

        //Properties:

        /**
         * @brief Stores the message string to be sent or received, including message and arguements (see MessageLibrary.h)
         * 
         */
        std::string messageString;
        
        
        /**
         * @brief Stores the ID of the message being sent or received
         * 
         */
        unsigned int messageID;
        
        /**
         * @brief Stores the checksum of the message being sent or received
         * 
         */
        unsigned int checksum;

        //Methods:

        /**
         * @brief This function is responsible for calculating a checksum on the data that was sent to the user.
         * The checksum is ONLY calculated on the messageString portion of the message and is calculated as the
         * sum of all characters in the string, mod 100 after each addition of a character:
         * 
         * @return unsigned int ==> Calculated checksum
         */
        unsigned int calculateChecksum();
    
    public:

        //Getter functions for the private variables

        /**
         * @brief Get the Message String object
         * 
         * @return std::string => Returns a string containing the \ref messageString attribute
         */
        std::string getMessageString() {return this->messageString;}

        /**
         * @brief Get the Message I D object
         * 
         * @return unsigned int => Returns an unsigned int containing the \ref messageID attribute
         */
        unsigned int getMessageID() {return this->messageID;}

        /**
         * @brief Get the Checksum object
         * 
         * @return unsigned int => Returns an unsigned int containing the \ref checksum attribute
         */
        unsigned int getChecksum() {return this->checksum;}

        /**
         * @brief Create a default constructor, required when overloading is used
         * 
         */
        MessagePacket(){
            this->messageString = "";
            this->messageID = 0;
            this->checksum = 0;
        }

        /**
         * @brief Construct a new Message Packet:: Message Packet object This constructor is used when the Raspberry PI is sending a message to
         * the embedded system and the user is defining the message that is desired to send
         * 
         * @param messageString => the strign containing the message and arguements to be sent
         * @param messageID => Integer containing the ID of the message to be sent
         */
        MessagePacket(std::string messageString, unsigned int messageID);

        /**
         * @brief Construct a new Message Packet:: Message Packet object ==> This constructor is used when a full message is being
         * read and needs to be converted into a MessagePacket object through string parsing
         * 
         * NOTE: The string read has the format: "|MSG_ID|>MESSAGE:ARGUMENTS<CHECKSUM"
         * 
         * NOTE: Could add getline checks to see if it is getting errors when parsing and throw an associated excpetion as a result,
         * this must be added in the full product (Check if getline is reaching end of stream to early or erroring out)
         * 
         * @param data ==> Full string message of the form "|MSG_ID|>MESSAGE:ARGUMENTS<CHECKSUM" to be parsed into a MessagePacket object
         */
        MessagePacket(std::string data);

        /**
         * @brief Destroy the Message Packet object
         * 
         */
        ~MessagePacket(){
        }

        /**
         * @brief Create a Copy Contructor for the class:
         * 
         * @param mp MessagePacket object to be copied
         */
        MessagePacket(const MessagePacket &mp){
            this->messageString = mp.messageString;
            this->messageID = mp.messageID;
            this->checksum = mp.checksum;
        }

        //Functions used for added functionality for the Message Packets

        /**
         * @brief This function is intended to compare the checksum stored in an object to the calculated checksum based on the attributes of the MessagePacket
         * 
         * @return true -> If the calculated and stored checksums are identical
         * @return false -> If the calculated and stored checksums are not identical
         */
        bool validateChecksum();

        /**
         * @brief This function returns a string of the format: "|MSG_ID|>MESSAGE:ARGUMENTS<CHECKSUM" to be sent
         * to the embedded system, based on the parameters of the message packet
         * 
         * @return std::string -> String of format "|MSG_ID|>MESSAGE:ARGUMENTS<CHECKSUM"
         */
        std::string getFullMessage();
 
};




#endif /*MESSAGE_PACKET_H*/