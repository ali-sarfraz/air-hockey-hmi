/**
 * @file goal.h
 * @author Sanjayan Kulendran
 * @brief Header file used to declare the Goal class.
 * Simple goal class that stores a goal speed in unspecified units and a boolean representing the side the goal is on
 *
 * @version 1.0
 * @date 2020-11-30
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef GOAL_H
#define GOAL_H

/**
 * @brief Simple goal class that stores a goal speed in unspecified units and a boolean representing the side the goal is on
 * A side and B side are arbitrary names used for consistency in differentiating goals
 */
class goal
{

private:

    int speed; //!< Integer holding the goal speed [m/s]

    unsigned timeStamp; //!< Unsigned integer giving time of goal from the start of the game [s]

    bool onBSide; //!< Boolean value indicating whether the goal was on player B side of the table


public:


    /**
     * @brief goal - Constructor taking all goal parameters
     * @param initialSpeed - Speed of goal in unspecified units
     * @param initialTimeStamp - Time of goal (unspecified, but likely UNIX time in seconds since epoch)
     * @param goalIsOnBSide - Boolean value 'true' if the goal was score against player b's side
     */
    goal(int initialSpeed, unsigned initialTimeStamp, bool goalIsOnBSide);

    /**
     * @brief goal - Copy constructor for goal
     * @param copyGoal
     */
    goal(const goal &copyGoal);

    /**
     * @brief getSpeed - Getter for Goal speed
     * @return - integer representing goal speed in unspecified units
     */
    int getSpeed();

    /**
     * @brief getTime - Getter for goal time
     * @return - unsigned value giving the time assocaited with the goal
     */
    unsigned getTime();

    /**
     * @brief isGoalOnBSide - Getter for if the goal was on B side
     * @return - Boolean that is 'true' if goal was on B side
     */
    bool isGoalOnBSide();


    //Destructor, no dynamic memory allocated so default destructor is fine
    ~goal();

};

#endif // GOAL_H
