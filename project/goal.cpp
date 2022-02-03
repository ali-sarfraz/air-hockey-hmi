/**
 * @file goal.cpp
 * @author Sanjayan Kulendran
 * @brief Implementation file used to implement the Goal class.
 *
 * @version 1.0
 * @date 2020-11-30
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "goal.h"

//Goal class implementation


//Constructor taking all goal parameters
goal::goal(int initialSpeed, unsigned initialTimeStamp, bool goalIsOnBSide){

    //Set the private members as assigned
    speed = initialSpeed;
    timeStamp = initialTimeStamp;
    onBSide = goalIsOnBSide;

}


//Copy constructor for goal
goal::goal(const goal &copyGoal){

    //Copy all the private members from the goal to copy from
    speed = copyGoal.speed;
    timeStamp = copyGoal.timeStamp;
    onBSide = copyGoal.onBSide;

}

//Getter for Goal speed
int goal::getSpeed(){

    //Return the goal speed
    return speed;

}

//Getter for goal time
unsigned goal::getTime(){

    //Return the goal time
    return timeStamp;

}

//Getter for if the goal was on the robot side
bool goal::isGoalOnBSide(){

    //Return if the goal is on robot's side
    return onBSide;

}

//Destructor, no dynamic memory allocated so default destructor is fine
goal::~goal(){};
