/**
 * @file usermatchsettings.h
 * @author Mohammad Iqbal
 * @brief Header file used to declare the usermatchsettings class.
 *
 * The usermatchsettings class is responsible for creating a standard structure for
 * storing and accessing the current match settings. This allows it pertinent information to be
 * passed around the program easily.
 *
 * @version 0.1
 * @date 2020-11-11
 *
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef USERMATCHSETTINGS_H
#define USERMATCHSETTINGS_H

/**
 * @brief The usermatchsettings class is responsible for creating a standard structure for
 * storing and accessing the current match settings. This allows it pertinent information to be
 * passed around the program easily.
 */
class usermatchsettings
{
private:
    /**
     * @brief Used to store the number of games in a match (1 to 7)
     *
     */
    unsigned int numOfGames;

    /**
     * @brief Used to store the time limit for each game (1 to 5)
     *
     */
    unsigned int gameTimeLimit;

    /**
     * @brief Used to store the score threshold for victory in each game (1 to 7)
     *
     */
    unsigned int scoreThreshold;

    /**
     * @brief Used to store the rule for game victory (first to points threshold or max goals in set timeframe)
     *
     */
    unsigned int gameVictoryType; //0 = point threshold for win, 1 = max goals in gameTimeLimit

public:
    /**
     * @brief Construct a new usermatchsettings object ==> This constructor is used when main menu window needs to
     * create its a usermatchsettings object to store its current match settings, and by usermatchsettings window to temporarily
     * store any temporary changes made through the GUI
     */
    usermatchsettings();

    /**
     * @brief Default destructor for usermatchsettings class
     */
    ~usermatchsettings() {}

    /**
     * @brief set the number of games in a match
     *
     * @param chosenNumOfGames => unsigned int representing the number of games
     */
    void setNumberOfGames(unsigned int chosenNumOfGames);

    /**
     * @brief set the game time limit in a match
     *
     * @param chosenTimeLimit => unsigned int representing the time limit in minutes
     */
    void setGameTimeLimit(unsigned int chosenTimeLimit);

    /**
     * @brief set the score threshold for each game
     *
     * @param chosenThreshold => unsigned int representing the score threshold for
     * victory in a game
     */
    void setScoreThreshold(unsigned int chosenThreshold);

    /**
     * @brief set the rule for victory in a game
     *
     * @param chosenVicType => unsigned int representing the game victory type
     */
    void setGameVictoryType(unsigned int chosenVicType);

    /**
     * @brief Get the current value of the number of games attribute
     *
     * @return unsigned int => Returns an unsigned int containing the \ref numOfGames attribute
     */
    unsigned int getNumberOfGames();

    /**
     * @brief Get the current value of the game time limit attribute
     *
     * @return unsigned int => Returns an unsigned int containing the \ref gameTimeLimit attribute
     */
    unsigned int getGameTimeLimit();

    /**
     * @brief Get the current value of the score threshold attribute
     *
     * @return unsigned int => Returns an unsigned int containing the \ref scoreThreshold attribute
     */
    unsigned int getScoreThreshold();

    /**
     * @brief Get the current value of the game victory type attribute, where a number
     * corresponds to a specific type of rule
     *
     * @return unsigned int => Returns an unsigned int containing the \ref gameVictoryType attribute
     */
    unsigned int getGameVictoryType();
};

#endif // USERMATCHSETTINGS_H
