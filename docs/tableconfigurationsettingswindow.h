/**
 * @file tableconfigurationsettingswindow.h
 * @author Mohammad Iqbal
 * @brief Header file used to declare the tableconfigurationsettingswindow class.
 *
 * The tableconfigurationsettingswindow class is responsible for displaying the GUI that
 * pertains to the tableconfigurationsettings class. It allows the user to select different settings
 * for each of the data members in the tableconfigurationsettings class. This class works on the
 * tableconfigurationsettings object that is passed to it, in the context of this project, this
 * would be the tableconfigurationsettings object held by the main menu window. Should the user hit
 * accept on the GUI interface, the chosen settings will be applied to the passed tableconfigurationsettings
 * object.
 *
 * @version 0.2
 * @date 2020-11-28
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef TABLECONFIGURATIONSETTINGSWINDOW_H
#define TABLECONFIGURATIONSETTINGSWINDOW_H

#include <QColor>
#include <QDialog>
#include "tableconfigurationsettings.h"
#include "player.h"

#include "MessagePacket.h"
#include "MessageHandler.h"
#include "MessageLibrary.h"

namespace Ui {
class tableconfigurationsettingswindow;
}

/**
 * @brief The tableconfigurationsettingswindow class is responsible for displaying the GUI that
 * pertains to the tableconfigurationsettings class. It allows the user to select different settings
 * for each of the data members in the tableconfigurationsettings class. This class works on the
 * tableconfigurationsettings object that is passed to it, in the context of this project, this
 * would be the tableconfigurationsettings object held by the main menu window. Should the user hit
 * accept on the GUI interface, the chosen settings will be applied to the passed tableconfigurationsettings
 * object.
 *
 */
class tableconfigurationsettingswindow : public QDialog
{
    Q_OBJECT


public:

    /**
     * @brief The constructor for the table configuration window in the GUI.
     *
     * @param parent => A pointer to the parent window that creates this.
     * @param tableConfigPtr => A pointer to the parent tableconfigurationsettings object
     * @param playerB => A pointer to the parent (main menu) player B object
     */
    explicit tableconfigurationsettingswindow(QWidget *parent = nullptr,tableconfigurationsettings *tableConfigPtr = nullptr,player *playerB = nullptr);

    /**
     * @brief Destructor function for closing the table configuration settings window.
     */
    ~tableconfigurationsettingswindow();



private slots:

    /**
     * @brief Assigns the temporary tableconfigurationsettings object the updated table mode value and updates
     * its respective label (visual feedback to user)
     */
    void on_comboBoxTableMode_currentTextChanged(const QString &arg1);

    /**
     * @brief Assigns the temporary tableconfigurationsettings object's settings to the parents's tableconfigurationsettings object
     * and updates the embedded system through the singleton message handler about the new settings. Sets player B's name to
     * "Robot" if table mode is set to Robotic-Opponent.
     */
    void on_buttonBox_accepted();

    /**
     * @brief Assigns the temporary tableconfigurationsettings object the updated ai difficulty value and updates
     * its respective label (visual feedback to user)
     */
    void on_comboBoxAiDiff_currentTextChanged(const QString &arg1);

    /**
     * @brief Assigns the temporary tableconfigurationsettings object the updated table lighting value and updates
     * its respective label (visual feedback to user)
     */
    void on_horizontalSliderTableLighting_valueChanged(int value);

    /**
     * @brief Assigns the temporary tableconfigurationsettings object the updated table air speed value and updates
     * its respective label (visual feedback to user)
     */
    void on_horizontalSliderTableAirSpeed_valueChanged(int value);

private:
    /**
     * @brief Reference to the UI window for displaying and recieving information.
     */
    Ui::tableconfigurationsettingswindow *ui;

    /**
     * @brief Pointer to temporary tableconfigurationsettings object to hold any user changes until
     * GUI screen confirmation or cancellation
     */
    tableconfigurationsettings *tempTableConfigPtr;

    /**
     * @brief Pointer to parent tableconfigurationsettings object to apply user changes (if any) upon
     * GUI screen confirmation or cancellation
     */
    tableconfigurationsettings *parentTableConfigPtr;

    /**
     * @brief Pointer to parent player object to modify player name upon robotic table mode selection
     * GUI screen confirmation
     */
    player *parentPlayerBPtr;

    /**
     * @brief Q colour object used to change table lighting label colour
     */
    QColor tColor;

};

#endif // TABLECONFIGURATIONSETTINGSWINDOW_H
