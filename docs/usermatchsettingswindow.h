/**
 * @file usermatchsettingswindow.h
 * @author Mohammad Iqbal
 * @brief Header file used to declare the usermatchsettingswindow class.
 *
 * The usermatchsettingswindow class is responsible for displaying the GUI that
 * pertains to the usermatchsettings class. It allows the user to select different settings
 * for each of the data members in the usermatchsettings class. This class works on the
 * usermatchsettings object that is passed to it, in the context of this project, this
 * would be the usermatchsettings object held by the main menu window. Should the user hit
 * accept on the GUI interface, the chosen settings will be applied to the passed usermatchsettings
 * object.
 *
 * @version 0.3
 * @date 2020-11-30
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef USERMATCHSETTINGSWINDOW_H
#define USERMATCHSETTINGSWINDOW_H

#include <QDialog>
#include "usermatchsettings.h"

namespace Ui {
class userMatchSettingsWindow;
}

/**
 * @brief The usermatchsettingswindow class is responsible for displaying the GUI that
 * pertains to the usermatchsettings class. It allows the user to select different settings
 * for each of the data members in the usermatchsettings class. This class works on the
 * usermatchsettings object that is passed to it, in the context of this project, this
 * would be the usermatchsettings object held by the main menu window. Should the user hit
 * accept on the GUI interface, the chosen settings will be applied to the passed usermatchsettings
 * object.
 */
class userMatchSettingsWindow : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief The constructor for the match settings window in the GUI.
     *
     * @param parent => A pointer to the parent window that creates this.
     * @param matchsettingsptr => A pointer to the parent usermatchsettings object
     */
    explicit userMatchSettingsWindow(QWidget *parent = nullptr,usermatchsettings* matchsettingsptr = nullptr);

    /**
     * @brief Destructor function for closing the match settings window.
     */
    ~userMatchSettingsWindow();

private slots:

    /**
     * @brief Assigns the temporary usermatchsettings object the updated number of games value and updates
     * its respective label (visual feedback to user)
     */
    void on_comboBoxNumOfGames_currentTextChanged(const QString &arg1);

    /**
     * @brief Assigns the temporary usermatchsettings object the updated game time limit value and updates
     * its respective label (visual feedback to user)
     */
    void on_comboBoxGameTimeLimit_currentTextChanged(const QString &arg1);


    /**
     * @brief Assigns the temporary usermatchsettings object the updated score threshold value and updates
     * its respective label (visual feedback to user)
     */
    void on_comboBoxScoreThreshold_currentTextChanged(const QString &arg1);

    /**
     * @brief Assigns the temporary usermatchsettings object the updated game victory type value and updates
     * its respective label (visual feedback to user)
     */
    void on_comboBoxGameVicType_currentTextChanged(const QString &arg1);


    /**
     * @brief Assigns the temporary usermatchsettings object's settings to the parents's usermatchsettings object
     */
    void on_buttonBox_accepted();

private:

    /**
     * @brief Pointer to temporary usermatchsettings object to hold any user changes until
     * GUI screen confirmation or cancellation
     */
    usermatchsettings *tempSettingsObjectPtr;

    /**
     * @brief Pointer to parent usermatchsettings object to apply user changes (if any) upon
     * GUI screen confirmation or cancellation
     */
    usermatchsettings *parentmatchsettingsptr;

    /**
     * @brief Reference to the UI window for displaying and recieving information.
     */
    Ui::userMatchSettingsWindow *ui;
};

#endif // USERMATCHSETTINGSWINDOW_H
