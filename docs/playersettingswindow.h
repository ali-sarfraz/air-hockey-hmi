/**
 * @file playersettingswindow.h
 * @author Natalia Bohulevych
 * @brief Header file used to declare the playersettingswindow class.
 *
 * The playersettingswindow class is responsible for displaying the GUI that
 * pertains to the player class. It allows the user to select different settings
 * for each of the data members in the player class. This class works on the
 * player objects that are passed to it, in the context of this project, this
 * would be the tplayer objects held by the main menu window. Should the user hit
 * accept on the GUI interface, the chosen settings will be applied to the passed player
 * objects.
 *
 * @version 0.2
 * @date 2020-12-02
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef PLAYERSETTINGSWINDOW_H
#define PLAYERSETTINGSWINDOW_H

#include <QDialog>
#include "player.h"

namespace Ui {

class playersettingswindow;
}

/**
 * @brief This class is responsible for altering the player objects that
 * were passed to it.
 *
 */
class playersettingswindow : public QDialog
{
    Q_OBJECT

public:
    explicit playersettingswindow(QWidget *parent = nullptr, player *playerAObjPtr = nullptr, player *playerBObjPtr = nullptr);
    ~playersettingswindow();

private slots:
    void on_buttonBox_accepted();

//    void on_lineEdit_playerAname_returnPressed();

//    void on_lineEdit_playerBname_returnPressed();

    void on_lineEdit_playerBname_cursorPositionChanged();

    void on_lineEdit_playerAname_editingFinished();

    void on_lineEdit_playerBname_editingFinished();

    void on_comboBox_playerAtype_currentIndexChanged(const QString &arg1);

    void on_comboBox_playerBtype_currentIndexChanged(const QString &arg1);

private:
    /**
     * @brief pointer to playersettingswindow for access to UI for QT
     * 
     */
    Ui::playersettingswindow *ui;

     /**
     * @brief pointer to player object of calling parent to adjust params of Player A
     * 
     */
    player *parentPlayerAPtr;

     /**
     * @brief pointer to player object of calling parent to adjust params of Player B
     * 
     */
    player *parentPlayerBPtr;

     /**
     * @brief pointer to player object to temporarily change parameters of Player A
     * 
     */
    player *tempPlayerAPtr;

     /**
     * @brief pointer to player object to temporarily change parameters of Player B
     * 
     */
    player *tempPlayerBPtr;

     /**
     * @brief unsigned int to determine and store the table mode of the air-hockey game
     * 
     */
    unsigned int mode;
};

#endif // PLAYERSETTINGSWINDOW_H
