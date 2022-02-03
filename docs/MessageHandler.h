/**
 * @file MessageHandler.h
 * @author Matthew Bertuzzi
 * @brief Header file used to declare the MessageHandler class. 
 * The MessageHandler class is designed using a Singleton design pattern so that one object can be used throughout
 * the code for communication with the embedded system or simulated embedded system, regardless of our location within
 * the code. The communication is handled with separate threads for sending messages to the embedded system, receiving messages
 * from the embedded system, and simulating the embedded system. Using the object, a user can simply call a function to send a message
 * and the receive the appropriate data as a result.
 * 
 * @version 0.1
 * @date 2020-10-07
 * 
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include <sstream>
#include <queue>
#include <mutex>
#include <vector>
#include <thread>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "MessageLibrary.h"
#include "MessagePacket.h"


/**
 * @brief The MessageHandler class is designed using a Singleton design pattern so that one object can be used throughout
 * the code for communication with the embedded system or simulated embedded system, regardless of our location within
 * the code. The communication is handled with separate threads for sending messages to the embedded system, receiving messages
 * from the embedded system, and simulating the embedded system. Using the object, a user can simply call a function to send a message
 * and the receive the appropriate data as a result.
 * 
 */
class MessageHandler{

    //Declare MessageHandler attributes
    private:

        //Properties:

        /**
         * @brief Used to identify the message that was sent and is waiting for a response
         * 
         */
        MessagePacket waitingMessage;

        /**
         * @brief Used to identify the message that was received and can be processed
         * 
         */
        MessagePacket receivedMessage;

        /**
         * @brief Used to identify the ID of the message to be sent
         * 
         */
        unsigned int messageIDCount;

        /**
         * @brief Queue used if multiple messages are being received simultaneously
         * 
         */
        std::queue<MessagePacket> incomingQueue;

        /**
         * @brief Queue used for handling multiple unsolicited messages simultaneously
         * 
         */
        std::queue<MessagePacket> unsolicitedQueue;

        /**
         * @brief Queue used if multiple messages are being sent simultaneously
         * 
         */
        std::queue<MessagePacket> outgoingQueue;

        /**
         * @brief Thread used for sending messages to the embedded system
         * 
         */
        std::thread outgoingThread;

        /**
         * @brief Thread used for receiving messages from the embedded system
         * 
         */
        std::thread incomingThread;

        /**
         * @brief Thread used for simulating the embedded system
         * 
         */
        std::thread embeddedSystemSimThread;

        /**
         * @brief Pipe used to simulate the USART Tx line
         * 
         */
        int simulationPipeSend[2];

        /**
         * @brief Pipe used to simulate the USART Rx line
         * 
         */
        int simulationPipeReceive[2];

        /**
         * @brief Mutex used as a flag to identify when a message is ready to send
         * 
         */
        std::mutex outgoingMutex;

        /**
         * @brief Mutex used as a flag to identify when a message has been received
         * 
         */
        std::mutex incomingMutex;

        /**
         * @brief Mutex used to protect access to the unsolicited queue
         * 
         */
        std::mutex unsolicitedMutex;

        /**
         * @brief Mutex used for thread-safe Singleton creation
         * 
         */
        static std::mutex instantiateMutex;

        /**
         * @brief Pointer used to contain a reference to the Singleton
         * 
         */
        static MessageHandler* _instance;

        /**
         * @brief Make copy constructor private in overloads to prevent accidental creation of another singleton
         * 
         */
        MessageHandler(const MessageHandler &other){};

        /**
         * @brief Make assignment operator private in overloads to prevent accidental creation of another singleton
         * 
         */
        MessageHandler& operator=(const MessageHandler &other){return *this;};

        //Thread functions for sending and receiving data, as well as simulation:

        /**
         * @brief The sendQueueMessagesThread is responsible for operating as a thread that sends messages to
         * the embedded system. When a message is available to send, it receives a notification through the
         * outgoingMutex and then takes the next message to send from the outgoingQueue. For simulation purposes,
         * the message is sent through a Pipe as the Tx line.
         * 
         */
        void sendQueueMessagesThread();

        /**
         * @brief The receiveQueueMessagesThread is responsible for operating as a thread that receives messages from
         * the embedded system. When a message is receives, it receives a notification through the
         * pipe, simulationPipeReceive, and then takes the recieved message, and puts it on the incomingQueue.
         * The thread also notifies that it has put a received message on the queue using incomingMutex. It is noted
         * that the thread is intended to behave as the Rx line.
         * 
         */
        void receiveQueueMessagesThread();

        /**
         * @brief The embeddedSystemSimulation is responsible for operating as a thread that simulates the embedded system.
         * As a result, it is responsible for receiving and parsing messages, acting accordingly to the messages, and then sending a valid response.
         * 
         */
        void embeddedSystemSimulation();
        

    protected:

        /**
         * @brief Construct a new Message Handler:: Message Handler object The constructor is responsible
         * for intializing all attributes, but also starts the threads used with the Message Handler because
         * a Singleton pattern is used and only allows for single thread creation with a single object.
         * Protected to prevent instantiation.
         * 
         */
        MessageHandler();

        /**
         * @brief Destroy the Message Handler object
         * 
         */
        ~MessageHandler(){
        };

    public:

        //Getter functions for the private variables

        /**
         * @brief Get the Message I D Count object
         * 
         * @return unsigned int  => Returns an unsigned int containing the \ref messageIDCount attribute
         */
        unsigned int getMessageIDCount() {return this->messageIDCount;}

        /**
         * @brief Get the Waiting Message object
         * 
         * @return MessagePacket  => Returns a MessagePacket containing the \ref waitingMessage attribute
         */
        MessagePacket getWaitingMessage() {return this->waitingMessage;}

        /**
         * @brief Get the Received Message object
         * 
         * @return MessagePacket  => Returns a MessagePacket containing the \ref receivedMessage attribute
         */
        MessagePacket getReceivedMessage() {return this->receivedMessage;}

        

        //Instance function for Singleton design pattern:

        /**
         * @brief This function is responsible for creating the single MessageHandler object for the Singleton design pattern
         * 
         * NOTE: The Double-Checked Locking Pattern (DCLP) is used when initializing the _instance variable to ensure
         * that we have efficient, thread-safe implementation of the Singleton initialization.
         * Although there are some issues associated with DCLP, we assume proper functionality here
         * 
         * @return MessageHandler& 
         */
        static MessageHandler& instance();

        //Methods Used for communication:

        /**
         * @brief This function is the main function to be used throught the code structure for the project and operates by taking a desired message
         * to send and any associated arguements if necessary. The values are put together into a MessagePacket, which is placed on the outgoingQueue
         * for sending. Sending and receiving are handled by threads, and the function is then notified of a response received through
         * incomingMutex. The received message is taken off of the incomingQueue and processed for results and data returned through a vector.
         * 
         * @param message -> Message to send to the embedded system according to \ref MessageLibrary.h
         * @param arguements -> Arguments to send along with the message
         * @return std::vector<int> -> Pertinent data associated with the response to the sent message.
         * IF there was an error, the FIRST element of the vector takes a negative value
         * IF the transaction was successful, the FIRST element is the ID of the message, and the following elements correspond to any arguements that were returned as part of the message
         */
        std::vector<int> sendMessage(std::string message, std::string arguements = "");

        /**
         * @brief This function is responsible for checking if the unsolicitedQueue of the MessageHandler singleton has any messages.
         * Ideally, the unsolicited queue would be handled through the incomingQueue, and be processed in a separate thread that would
         * use interrupts or signals to identify important events (such as when a goal is scored). However, this function operates in a manner
         * To simulate the embedded system comunication, and as a result, because there is only a single MAIN thread for sending and receiving messages,
         * the function can be polled to identify whether a message was successfully received in the unsolicited queue!
         * 
         * @return std::vector<int> If the unsolicitedQueue is empty, the firs value in the vector is returned as a negative (-1), which is the ONLY value in the vector
         * If the unsolicitedQueue had a message, the message is removed, and the first value of the vector is returned as the ID of the message received, while the remaining
         * values in the vector are returned as values associated with the message on the queue (Because there is ONLY 1 message type that can be sent unsolicited, it is always
         * the goal side and then the goal speed in the vector)
         * 
         * Ex. vect<int>[0] = 100 (messageID), vect<int>[0] = 1 (goalSide), vect<int>[0] = 100 (goalSpeed)
         */
        std::vector<int> unsolicitedQueueGet();

};




#endif /*MESSAGE_HANDLER_H*/