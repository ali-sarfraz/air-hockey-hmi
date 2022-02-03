/**
 * @file MessageHandler.cpp
 * @author Matthew Bertuzzi
 * @brief Implementation file used to implement the MessageHandler class
 * @version 0.1
 * @date 2020-10-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "MessageHandler.h"


MessageHandler* MessageHandler::_instance = NULL;
std::mutex MessageHandler::instantiateMutex;

MessageHandler::MessageHandler(){
    this->messageIDCount = 0;
    this->incomingQueue.empty();
    this->outgoingQueue.empty();
    this->unsolicitedQueue.empty();

    //Lock the mutexes to be treated as Semaphores/Flags
    this->outgoingMutex.lock();
    this->incomingMutex.lock();

    //Begin the pipe to allow communication between threads for simulating USART/UART:
    pipe(this->simulationPipeSend);
    pipe(this->simulationPipeReceive);
    



    //Requires Exception throwing on error
    this->outgoingThread = std::thread(&MessageHandler::sendQueueMessagesThread, this);
    this->incomingThread = std::thread(&MessageHandler::receiveQueueMessagesThread, this);
    this->embeddedSystemSimThread = std::thread(&MessageHandler::embeddedSystemSimulation, this);
    
}


void MessageHandler::sendQueueMessagesThread(){
    

    while(1){

        this->outgoingMutex.lock();
        
        //Need to check for errors here!
        MessagePacket msgToSend = this->outgoingQueue.front();

        this->outgoingQueue.pop();

        std::string sendString = msgToSend.getFullMessage();

        //We need to convert the string that we are sending into a character array for piping and/or UART
        unsigned int n = sendString.length();
    
        char charArraySend[n + 1];
    
        //copy the contents of the string to a char array
        strcpy(charArraySend, sendString.c_str());

        //Send the contents of the string over UART or over a pipe:
        write(this->simulationPipeSend[1], charArraySend, strlen(charArraySend));

    }
    
}


void MessageHandler::receiveQueueMessagesThread(){
    
    //Create a char array of max message length:
    char readMessage[100];



    while(1){
 
        //Wait to read the contents of the simulated UART
        read(this->simulationPipeReceive[0], readMessage, 100);

        

        //Once a message has been read, we convert it into a string for processing
        //When converting to a string, we iterate through each character until a null terminator is reached
        std::string readString = ""; 
        for (int i = 0; i < 100; i++) { 
            readString = readString + readMessage[i];
            if(readMessage[i] == '\0'){
                break;
            }
        }

        

        //Create the a message packet corresponding to the read string
        MessagePacket msgReceived(readString);

        //Before pushing the message on the incoming queue, we must check if the message ID indicates that it was an unsolicited message
        //That must go onto the unsolicited message queue!
        if(msgReceived.getMessageID() == 100){
            //If the message ID is 100, then we must pass the message onto the unsolicited queue
            this->unsolicitedMutex.lock(); //Protected access to queue
            unsolicitedQueue.push(msgReceived);
            this->unsolicitedMutex.unlock(); //Protected access to queue

        }
        else{
            //Push the message packet onto the received queue:
            incomingQueue.push(msgReceived);

            //Signal that the message has been received:
            this->incomingMutex.unlock();
        }

        

    }

}


void MessageHandler::embeddedSystemSimulation(){

    //Create a char array of max message length:
    char readMessage[100];

    //Set up the pipe here to be polling on read operations to emulate embedded system
    fcntl( this->simulationPipeSend[0], F_SETFL, fcntl(this->simulationPipeSend[0], F_GETFL) | O_NONBLOCK);

    //Before beginning the simulation, we need to initialize system variables that the embedded system will have
    //that represent or simulate the physical attributes of the real system

    int gameState = ML_INACTIVE;                //Initialize the air-hockey game as inactive
    int aiState = ML_INACTIVE;                  //Initialize the AI state as inactive
    int aiDifficulty = 0;                       //Initialize the AI difficulty to 0
    int tableMode = ML_STANDARD;                //Initialize the table mode to Standard
    int tableLighting = 0x000000;               //initialize the table lighting to off (RGB hex value)
    int tableAirSpeed = 50;                     //Initialize the table air speed to 50%

    //Seed RNG for determining when a goal has been scored:
    srand(time(NULL));

    //Below, we define a MAXIMUM time that we would like the air-hockey game to sleep prior to generating a random goal
    //The sleep time is stored as a value in seconds and can be tuned
    int maxSleep = 5;
    //sleep((rand() % maxSleep) + 1);
    int i = 0;
    unsigned int nextGoalTime = (rand() % maxSleep) + 1;
    int counter = 0;

    while(1){

        //If the game is in an inactive state, then we only listen for messages from the main RaspberryPi
        if(gameState != ML_ACTIVE){

            counter = 0;
            //Wait to read the contents of the simulated UART
            while(1){
                i = read(this->simulationPipeSend[0], readMessage, 100);
                if(i != -1){
                    break;
                }

                //Sleep this thread to simulate the response time of an embedded system ==> 100ms
                usleep(100000);
            } 
            
        }
        else{
            //If the game is in an ACTIVE state, then we generate random goals and send them at random time intervals
            //while simultaneously polling for received messages:


            while(1){

                i = read(this->simulationPipeSend[0], readMessage, 100);
                if(i != -1){
                    break;
                }

                if((unsigned int)(counter*0.1) >= nextGoalTime){

                    int goalSide = (rand() % 2);
                    int goalSpeed = (rand() % 100) + 1;

                    std::string stringToSend = M_EMB_SET_GOAL_DATA;
                    stringToSend += ":" + std::to_string(goalSide) + "," + std::to_string(goalSpeed);
                    MessagePacket msgTmp(stringToSend, 100); //Use a messageID of 100 in order to indicate that it is an unsolicited goal message

                    //Now, we return a response to the sent message:
                    std::string sendString = msgTmp.getFullMessage();


                    //We need to convert the string that we are sending into a character array for piping and/or UART
                    unsigned int n = sendString.length();
                
                    char charArraySend[n + 1];
                
                    //copy the contents of the string to a char array
                    strcpy(charArraySend, sendString.c_str());


                    //Send the contents of the string over UART or over a pipe:
                    write(this->simulationPipeReceive[1], charArraySend, strlen(charArraySend));

                    //Below, we generate a time at which we will generate a goal while the game mode is active:
                    nextGoalTime = (rand() % maxSleep) + 1;
                    counter = 0;
                }

                

                //Sleep this thread to simulate the response time of an embedded system ==> 100ms
                usleep(100000);
                counter++;
            } 
            

            

        }

        

        //Once a message has been read, we convert it into a string for processing
        //When converting to a string, we iterate through each character until a null terminator is reached
        std::string readString = ""; 
        for (int i = 0; i < 100; i++) { 
            readString = readString + readMessage[i];
            if(readMessage[i] == '\0'){
                break;
            }
        }

        //Create the a message packet corresponding to the read string
        MessagePacket msgReceived(readString);

        //Perform necessary parsing to identify what to do with the message
        //Create a string to compare when parsing
        std::string tokenMsg;
        std::string tokenData;

        //Convert the read data line into a stream that we can tokenize as an input
        std::istringstream stream(msgReceived.getMessageString());

        //First, we parse the string to get the token corresponding to the message string:
        getline(stream, tokenMsg, ':'); //Get message for now, assuming only message

        //Prior to performing full processing on the token received, we must check whether it is a getter or setter
        //message in order to identify whether any additional information is required
        if(msgReceived.getMessageString().find(SETTER_STRING) != std::string::npos){
            //If we are dealing with a setter message, then we must read the data coming along with the message
            getline(stream, tokenData, '<'); //Get message for now, assuming only message
        }

        //Based on the received message, decide how to respond and what simulation values to alter/change!
        MessagePacket msgReturn;


        //Prior to processing the message, we must ensure that the checksums match:
        if(!msgReceived.validateChecksum()){
        
            std::string stringToSend = "ERROR! NONMATCHING CHECKSUMS";
            MessagePacket msgTmp(stringToSend + ":", msgReceived.getMessageID());
            msgReturn = msgTmp;

        }

        //Process the message based on the token received
        if(tokenMsg == M_RPI_GET_AI_DIFFICULTY){
            std::string stringToSend = M_RPI_GET_AI_DIFFICULTY;
            MessagePacket msgTmp(stringToSend + ":" + std::to_string(aiDifficulty), msgReceived.getMessageID());
            msgReturn = msgTmp;
        }
        else if(tokenMsg == M_RPI_GET_AI_ACTIVE_STATE){
            std::string stringToSend = M_RPI_GET_AI_ACTIVE_STATE;
            MessagePacket msgTmp(stringToSend + ":" + std::to_string(aiState), msgReceived.getMessageID());
            msgReturn = msgTmp;
        }
        else if(tokenMsg == M_RPI_GET_GAME_ACTIVE_STATE){
            std::string stringToSend = M_RPI_GET_GAME_ACTIVE_STATE;
            MessagePacket msgTmp(stringToSend + ":" + std::to_string(gameState), msgReceived.getMessageID());
            msgReturn = msgTmp;
        }
        else if(tokenMsg == M_RPI_GET_TABLE_MODE){
            std::string stringToSend = M_RPI_GET_TABLE_MODE;
            MessagePacket msgTmp(stringToSend + ":" + std::to_string(tableMode), msgReceived.getMessageID());
            msgReturn = msgTmp;
        }
        else if(tokenMsg == M_RPI_GET_TABLE_LIGHTING){
            std::string stringToSend = M_RPI_GET_TABLE_LIGHTING;
            MessagePacket msgTmp(stringToSend + ":" + std::to_string(tableLighting), msgReceived.getMessageID());
            msgReturn = msgTmp;
        }
        else if(tokenMsg == M_RPI_GET_TABLE_AIR_SPEED){
            std::string stringToSend = M_RPI_GET_TABLE_AIR_SPEED;
            MessagePacket msgTmp(stringToSend + ":" + std::to_string(tableAirSpeed), msgReceived.getMessageID());
            msgReturn = msgTmp;
        }
        else if(tokenMsg == M_RPI_SET_AI_DIFFICULTY){
            //Convert our token into a string stream and then pipe it into an integer:
            std::istringstream mData(tokenData);
            mData >> aiDifficulty;
            //Return the same message that was sent, without data:
            std::string stringToSend = M_RPI_SET_AI_DIFFICULTY;
            MessagePacket msgTmp(stringToSend + ":1", msgReceived.getMessageID());
            msgReturn = msgTmp;

        }
        else if(tokenMsg == M_RPI_SET_AI_ACTIVE_STATE){
            //Convert our token into a string stream and then pipe it into an integer:
            std::istringstream mData(tokenData);
            mData >> aiState;
            //Return the same message that was sent, without data:
            std::string stringToSend = M_RPI_SET_AI_ACTIVE_STATE;
            MessagePacket msgTmp(stringToSend + ":", msgReceived.getMessageID());
            msgReturn = msgTmp;

        }
        else if(tokenMsg == M_RPI_SET_GAME_ACTIVE_STATE){
            //Convert our token into a string stream and then pipe it into an integer:
            std::istringstream mData(tokenData);
            mData >> gameState;
            //Return the same message that was sent, without data:
            std::string stringToSend = M_RPI_SET_GAME_ACTIVE_STATE;
            MessagePacket msgTmp(stringToSend + ":", msgReceived.getMessageID());
            msgReturn = msgTmp;

        }
        else if(tokenMsg == M_RPI_SET_TABLE_MODE){
            //Convert our token into a string stream and then pipe it into an integer:
            std::istringstream mData(tokenData);
            mData >> tableMode;
            //Return the same message that was sent, without data:
            std::string stringToSend = M_RPI_SET_TABLE_MODE;
            MessagePacket msgTmp(stringToSend + ":", msgReceived.getMessageID());
            msgReturn = msgTmp;

        }
        else if(tokenMsg == M_RPI_SET_TABLE_LIGHTING){
            //Convert our token into a string stream and then pipe it into an integer:
            std::istringstream mData(tokenData);
            mData >> tableLighting;
            //Return the same message that was sent, without data:
            std::string stringToSend = M_RPI_SET_TABLE_LIGHTING;
            MessagePacket msgTmp(stringToSend + ":", msgReceived.getMessageID());
            msgReturn = msgTmp;

        }
        else if(tokenMsg == M_RPI_SET_TABLE_AIR_SPEED){
            //Convert our token into a string stream and then pipe it into an integer:
            std::istringstream mData(tokenData);
            mData >> tableAirSpeed;
            //Return the same message that was sent, without data:
            std::string stringToSend = M_RPI_SET_TABLE_AIR_SPEED;
            MessagePacket msgTmp(stringToSend + ":", msgReceived.getMessageID());
            msgReturn = msgTmp;

        }
        else{
            std::string stringToSend = "ERROR! UNRECOGNIZED MESSAGE";
            MessagePacket msgTmp(stringToSend + ":", msgReceived.getMessageID());
            msgReturn = msgTmp;
        }

        //Now, we return a response to the sent message:
        std::string sendString = msgReturn.getFullMessage();


        //We need to convert the string that we are sending into a character array for piping and/or UART
        unsigned int n = sendString.length();
    
        char charArraySend[n + 1];
    
        //copy the contents of the string to a char array
        strcpy(charArraySend, sendString.c_str());


        //Send the contents of the string over UART or over a pipe:
        write(this->simulationPipeReceive[1], charArraySend, strlen(charArraySend));

    }

}

MessageHandler& MessageHandler::instance(){
    
    //After we check if _instance has been set, we lock the mutex. This is important
    //to prevent locking the mutex every time we try to access the instance
    if(MessageHandler::_instance == NULL){


        MessageHandler::instantiateMutex.lock();
        
        //Check again incase the instance was created while waiting on the lock
        if(MessageHandler::_instance == NULL){
            
            MessageHandler::_instance = new MessageHandler();
        }

        MessageHandler::instantiateMutex.unlock();
    
    }

    return *MessageHandler::_instance;

}


std::vector<int> MessageHandler::sendMessage(std::string message, std::string arguements){

    std::vector<int> vectReturn;

    //First, we must construct the message with the arguements provided
    std::string messageString = message + ":" + arguements;

    //Pass the contructed message string into a MessagePacket object
    MessagePacket msgToSend(messageString, this->messageIDCount);

    //Needs to be mutex protected
    this->messageIDCount++;
    if(this->messageIDCount > 99){
        this->messageIDCount = 0;  //Wrap the message count once we reach 99 messages.
    }

    //Could be formed as a vector so we can have any number of messges waiting for a response
    this->waitingMessage = msgToSend;

    //Put the message to send onto the queue and then signal the thread to send the message
    //It is assumed that the main program will be hosted in a single thread, and such the sending queue
    //Is not mutex protected ==> Should be mutex protected if multiple threads in main program leading to
    //Multiple calls to sendMessage (ALSO, would require a counting semaphore for message notifications)

    

    outgoingQueue.push(this->waitingMessage);
    this->outgoingMutex.unlock(); //Needs to be a counting semaphore here IF multiple threads can send messages

    //Wait here until a message was received:
    this->incomingMutex.lock();

    

    //Get the message received: Check for errors here
    MessagePacket msgReceived = this->incomingQueue.front();
    this->incomingQueue.pop();

    

    //Perform error checking
    if(msgReceived.getMessageString().find("ERROR") != std::string::npos){
        vectReturn.push_back(-1);
        return vectReturn;
    }
    else if(!msgReceived.validateChecksum()){
        vectReturn.push_back(-2);
        return vectReturn;
    }

    //If no errors, then we push_back the message ID and returned arguements:
    vectReturn.push_back(msgReceived.getMessageID());

    std::string token;

    //Convert the read data line into a stream that we can tokenize as an input
    std::istringstream stream(msgReceived.getMessageString());

    //First, we parse the string to get the token corresponding to the message id:
    getline(stream, token, ':'); //Ignore the message


    //Get all values in the string arguments
    int i = 0;
    while(getline(stream, token, ',')){
        //Convert our token into a string stream and then pipe it into an integer:
        std::istringstream mID(token);
        mID >> i;
        vectReturn.push_back(i);
    }

    return vectReturn;

}


std::vector<int> MessageHandler::unsolicitedQueueGet(){

    std::vector<int> vectReturn;

    //First, we check if there is anything on the queue:
    this->unsolicitedMutex.lock(); //Protected access to queue

    //Check if the unsolicitedQueue is empty
    if(this->unsolicitedQueue.empty()){
        
        //If the unsolicited queue is empty, then we return in error
        this->unsolicitedMutex.unlock(); //Unlock the queue before returning in error
        vectReturn.push_back(-1);
        return vectReturn;
    }

    //If the queue is not empty, then we get the next message on it for processing:
    MessagePacket msgReceived = this->unsolicitedQueue.front();
    this->unsolicitedQueue.pop();

    this->unsolicitedMutex.unlock(); //Protected access to queue

    //Now, we can process the unsolicited message for the values received:

    //Perform necessary parsing to identify what to do with the message
    //Create a string to compare when parsing
    std::string tokenMsg;
    std::string tokenData;

    //Convert the read data line into a stream that we can tokenize as an input
    std::istringstream stream(msgReceived.getMessageString());

    //First, we parse the string to get the token corresponding to the message string:
    getline(stream, tokenMsg, ':'); //Get message for now, assuming only message

    //Prior to performing full processing on the token received, we must check whether it is a getter or setter
    //message in order to identify whether any additional information is required
    if(msgReceived.getMessageString().find(SETTER_STRING) != std::string::npos){
        //If we are dealing with a setter message, then we must read the data coming along with the message
        getline(stream, tokenData, '<'); //Get message for now, assuming only message
    }


    //Prior to processing the message, we must ensure that the checksums match:
    if(!msgReceived.validateChecksum()){
    
        vectReturn.push_back(-2);
        return vectReturn;

    }

    //Process the message based on the token received
    if(tokenMsg == M_EMB_SET_GOAL_DATA){
        //Get the messageID:
        vectReturn.push_back(msgReceived.getMessageID());

        //Convert our token into a string stream and then pipe it into an integer:
        int goalSide = 0;
        int goalSpeed = 0;

        //Get the goal side and speed form the received message
        std::istringstream mData(tokenData);
        char comma;

        mData >> goalSide;
        mData >> comma;
        mData >> goalSpeed;

        vectReturn.push_back(goalSide);
        vectReturn.push_back(goalSpeed);
        return vectReturn;

    }
    else{
        //If no matching message was found, we return in error
        vectReturn.push_back(-3);
        return vectReturn;
    }


}