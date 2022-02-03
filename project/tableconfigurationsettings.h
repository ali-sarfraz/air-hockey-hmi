/**
 * @file tableconfigurationsettings.h
 * @author Mohammad Iqbal
 * @brief Header file used to declare the tableconfigurationsettings class.
 *
 * The tableconfigurationsettings class is responsible for creating a standard structure for
 * storing and accessing the current table configuration. This allows it pertinent information to be
 * passed around the program easily.
 *
 * @version 0.3
 * @date 2020-11-29
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef TABLECONFIGURATIONSETTINGS_H
#define TABLECONFIGURATIONSETTINGS_H

#include "MessagePacket.h"
#include "MessageHandler.h"
#include "MessageLibrary.h"
#include <QMessageBox>

/**
 * @brief The tableconfigurationsettings class is responsible for creating a standard structure for
 * storing and accessing the current table configuration. This allows it pertinent information to be
 * passed around the program easily.
 *
 */
class tableconfigurationsettings
{
private:

    /**
     * @brief Used to store the table mode (Free-play, Accessibility-Controlled, Robotic-Opponent)
     *
     */
    unsigned int tableMode;

    /**
     * @brief Used to store the ai difficulty (beginner, intermediate, expert)
     *
     */
    unsigned int aiDifficulty;

    /**
     * @brief Used to store the table air box CFM output (0 to 100 CFM)
     *
     */
    unsigned int tableAirSpeed;

    /**
     * @brief Used to store the RGB value of the table lighting (0 to 16777215)
     *
     */
    int tableLighting;

public:
    /**
     * @brief Construct a new tableconfigurationsettings object ==> This constructor is used when main menu window needs to
     * create its a tableconfigurationsettings object to store its current table settings, and by tableconfigurationsettings window
     * to temporarily store any temporary changes made through the GUI
     */
    tableconfigurationsettings();

    /**
     * @brief Default destructor for tableconfigurationsettings class
     */
    ~tableconfigurationsettings(){}

    /**
     * @brief set the table mode
     * @param chosenMode => unsigned int representing the table mode
     */
    void setTableMode(unsigned int chosenMode);

    /**
     * @brief set the ai difficulty
     * @param chosenDiff => unsigned int representing the ai difficulty
     */
    void setAiDifficulty(unsigned int chosenDiff);

    /**
     * @brief set the table air speed in CFM
     * @param chosenAirSpeed => unsigned int representing the air speed in CFM
     */
    void setTableAirSpeed(unsigned int chosenAirSpeed);

    /**
     * @brief set the table lighting colour
     * @param chosenLighting => int representing the RGB value of the lighting colour
     */
    void setTableLighting(int chosenLighting);

    /**
     * @brief Get the current value of the table mode attribute
     *
     * @return unsigned int => Returns an unsigned int containing the \ref tableMode attribute
     */
    unsigned int getTableMode();

    /**
     * @brief Get the current value of the ai difficulty attribute
     *
     * @return unsigned int => Returns an unsigned int containing the \ref aiDifficulty attribute
     */
    unsigned int getAiDifficulty();

    /**
     * @brief Get the current value of the table air speed attribute
     *
     * @return unsigned int => Returns an unsigned int containing the \ref tableAirSpeed attribute
     */
    unsigned int getTableAirSpeed();

    /**
     * @brief Get the current value of the table lighting attribute
     *
     * @return unsigned int => Returns an unsigned int containing the \ref tableLighting attribute
     */
    int getTableLighting();
};

#endif // TABLECONFIGURATIONSETTINGS_H
