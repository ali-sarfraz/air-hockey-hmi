/**
 * @file mainmenuwindow.h
 * @author Mohammad Iqbal, Mohammad Sarfraz, Sanjayan Kulendran, Natalia Bohulevych
 * @brief Header file used to declare the usermatchsettings class.
 *
 * The main menu window class is responsible for displaying the GUI to all the available
 * features in the program. It contains its own usermatchsettings, tableconfigurationsettings, and
 * player objects that are referenced by other classes. Based on which push button is clicked
 * by the user, the main menu window class opens the respective window to handle the command and
 * passes it any neccessary information.
 *
 * @version 0.1
 * @date 2020-11-11
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <functional> //For hash generation in unique match id
#include <iostream> //For assembling the string for hashing
#include "usermatchsettings.h"
#include "usermatchsettingswindow.h"
#include "tableconfigurationsettings.h"
#include "tableconfigurationsettingswindow.h"
#include "player.h"
#include "playersettingswindow.h"
#include "gamedisplay.h"
#include "matchdisplay.h"
#include "gameoutcome.h"
#include "time.h" //For unique match id generation
#include "sqlite3.h" //For accessing an SQLite database.
#include "databasewindow.h"

namespace Ui {
class MainMenuWindow;
}

/**
 * @brief  The main menu window class is responsible for displaying the GUI to all the available
 * features in the program. It contains its own usermatchsettings, tableconfigurationsettings, and
 * player objects that are referenced by other classes. Based on which push button is clicked
 * by the user, the main menu window class opens the respective window to handle the command and
 * passes it any neccessary information.
 */
class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief The constructor for the main menu window in the GUI.
     *
     * @param parent => A pointer to the parent widget that creates this object.
     */
    explicit MainMenuWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor function for closing the main menu window.
     */
    ~MainMenuWindow();

    /**
     * @brief Pointer to usermatchsettings object to hold any persistent match setting changes
     */
    usermatchsettings *matchSettingsObjPtr;

    /**
     * @brief Pointer to table configuration object to hold any persistent table setting changes
     */
    tableconfigurationsettings *tableConfigObjPtr;

    /**
     * @brief Pointer to player object to hold any persistent player setting changes
     */
    player *playerAObjPtr;

    /**
     * @brief Pointer to player object to hold any persistent player setting changes
     */
    player *playerBObjPtr;

private slots:
    /**
     * @brief Creates a usermatchsettingswindow object, passes it a pointer to self, pointer to own
     * usermatchsettingsobject and then shows the match settings window GUI
     */
    void on_pushButtonUserMatchSettings_clicked();

    /**
     * @brief Creates a tableconfigurationsettingswindow object, passes it a pointer to self, pointer to own
     * tableconfigurationsettings object, pointer to own playerB object and then shows the table configuration window GUI
     */
    void on_pushButtonTableConfig_clicked();

    /**
     * @brief Creates a playersettingswindow object, passes it a pointer to self, and pointer to own
     * playerA and playerB objects and then shows the player settings window GUI
     */
    void on_pushButtonPlayerSettings_clicked();

    /**
     * @brief Creates a temporary game vector to hold the data about the games that are
     * about to be played and a game outcome vector to be passed to database. It then
     * creates a game outcome object to store data about the games outcome, with this a unique
     * match ID is created to identify gameoutcome objects from the same match. The game match display
     * window object is created based on the given match settings object, table settings object
     * and player objects. The relevant information (player names, table mode) that are consistent
     * with each game are saved to a current game object, then the total player score is computed
     * from the completed games in the game vector. Lastly the database file is opened and the match
     * data is saved into the database
     */
    void on_pushButtonStartMatch_clicked();

    /**
     * @brief Creates a databaseWindow object, passes it a pointer to self and then shows the database window GUI
     */
    void on_pushButtonDatabaseWindow_clicked();

private:

    /**
     * @brief Reference to the UI window for displaying and recieving information.
     */
    Ui::MainMenuWindow *ui;

    /**
     * @brief Reference to the dynamically created usermatchsettingswindow object
     */
    userMatchSettingsWindow *userMatchSettingsWindowPtr;

    /**
     * @brief Reference to the dynamically created tableConfigSettingsWindow object
     */
    tableconfigurationsettingswindow *tableConfigSettingsWindowPtr;

    /**
     * @brief Reference to the dynamically created playerSettingsWindow object
     */
    playersettingswindow *playerSettingsWindowPtr;

    gameDisplay *gameDisplayPtr; ///< Stores pointer to game display
    matchDisplay *matchDisplayPtr; ///< Stores pointer to match display
    databaseWindow *databaseWindowPtr;///< Stores pointer to database display


};

#endif // MAINMENUWINDOW_H
