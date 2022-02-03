/**
 * @file usermatchsettingswindow.cpp
 * @author Mohammad Iqbal
 * @brief Implementation file used to implement the usermatchsettingswindow class
 * @version 0.2
 * @date 2020-11-30
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "usermatchsettingswindow.h"
#include "ui_usermatchsettingswindow.h"


userMatchSettingsWindow::userMatchSettingsWindow(QWidget *parent,usermatchsettings* matchsettingsptr) :
    QDialog(parent),
    ui(new Ui::userMatchSettingsWindow)
{
    //Pass main menu match settings ptr to userMatchSettingsWindow
    parentmatchsettingsptr = matchsettingsptr;

    //Create temp match settings object to hold user changes, have it show main menu match settings by default
    tempSettingsObjectPtr = new usermatchsettings();
    tempSettingsObjectPtr->setGameTimeLimit(parentmatchsettingsptr->getGameTimeLimit());
    tempSettingsObjectPtr->setNumberOfGames(parentmatchsettingsptr->getNumberOfGames());
    tempSettingsObjectPtr->setScoreThreshold(parentmatchsettingsptr->getScoreThreshold());
    tempSettingsObjectPtr->setGameVictoryType(parentmatchsettingsptr->getGameVictoryType());

    ui->setupUi(this);


    //Block # of games combo box signals while setting it up
    ui->comboBoxNumOfGames->blockSignals(1);

    //Setup # of games combobox with items
    for (int i = 1; i<=7;i++) {
         ui->comboBoxNumOfGames->addItem(QString::number(i));
    }

    //Set combobox for current number of games as blank by default
    ui->comboBoxNumOfGames->setCurrentIndex(-1);
    //Have current number of games label show default value
    ui->labelCurrNumOfGames->setText(QString::number(tempSettingsObjectPtr->getNumberOfGames()));

    //# of games combobox setup unblock signals
    ui->comboBoxNumOfGames->blockSignals(0);



    //Block game time limit combobox while it is being setup
    ui->comboBoxGameTimeLimit->blockSignals(1);

    //Setup Game Time Limit combobox with items
    for (int i = 1; i<=5;i++) {
         ui->comboBoxGameTimeLimit->addItem(QString::number(i));
    }
    //Set combobox for game time limit as blank by default
    ui->comboBoxGameTimeLimit->setCurrentIndex(-1);

    //Have current game time limit label show default value
    ui->labelCurrGameTimeLimit->setText(QString::number(tempSettingsObjectPtr->getGameTimeLimit()));

    //Game time limit combobox setup unblock signals
    ui->comboBoxGameTimeLimit->blockSignals(0);



    //Block Score Threshold combobox while it is being setup
    ui->comboBoxScoreThreshold->blockSignals(1);

    //Setup Score Threshold combobox with items
    for (int i = 1; i<=7;i++) {
         ui->comboBoxScoreThreshold->addItem(QString::number(i));
    }
    //Set combobox for score threshold as blank by default
    ui->comboBoxScoreThreshold->setCurrentIndex(-1);

    //Have current score threshold  label show default value
    ui->labelCurrScoreThreshold->setText(QString::number(tempSettingsObjectPtr->getScoreThreshold()));

    //score threshold combobox setup, unblock signals
    ui->comboBoxScoreThreshold->blockSignals(0);


    //Block game victory type combobox while it is being setup
    ui->comboBoxGameVicType->blockSignals(1);

    //Setup game victory type combobox with items
    ui->comboBoxGameVicType->addItem("First to Points Threshold");
    ui->comboBoxGameVicType->addItem("Max Goals in Set Time");

    //Set combobox for game victory type as blank by default
    ui->comboBoxGameVicType->setCurrentIndex(-1);

    //Have current game victory typelabel show default value
    if (tempSettingsObjectPtr->getGameVictoryType() == 0)
    {
         ui->labelCurrGameVicType->setText("First to Points Threshold");
    }
    else if (tempSettingsObjectPtr->getGameVictoryType() == 1)
    {
        ui->labelCurrGameVicType->setText("Max Goals in Set Time");
    }
    else
    {   //Error statement in case new game mode added and window not updated
        ui->labelCurrGameVicType->setText("Error, Unknown Choice");
    }

    //game victory type combobox setup, unblock signals
    ui->comboBoxGameVicType->blockSignals(0);

}


userMatchSettingsWindow::~userMatchSettingsWindow()
{
    delete ui;
}


void userMatchSettingsWindow::on_comboBoxNumOfGames_currentTextChanged(const QString &arg1)
{
    //Change main menu match settings object # of games
    tempSettingsObjectPtr->setNumberOfGames(arg1.toUInt());
    //Update current number of games label
    ui->labelCurrNumOfGames->setText(QString::number(tempSettingsObjectPtr->getNumberOfGames()));
}


void userMatchSettingsWindow::on_comboBoxGameTimeLimit_currentTextChanged(const QString &arg1)
{
    //Change temp match settings object game time limit
    tempSettingsObjectPtr->setGameTimeLimit(arg1.toUInt());
    //Update current number of games label
    ui->labelCurrGameTimeLimit->setText(QString::number(tempSettingsObjectPtr->getGameTimeLimit()));
}


void userMatchSettingsWindow::on_comboBoxScoreThreshold_currentTextChanged(const QString &arg1)
{
    //Change temp match settings object score threshold
    tempSettingsObjectPtr->setScoreThreshold(arg1.toUInt());
    //Update current number of games label
    ui->labelCurrScoreThreshold->setText(QString::number(tempSettingsObjectPtr->getScoreThreshold()));
}


void userMatchSettingsWindow::on_comboBoxGameVicType_currentTextChanged(const QString &arg1)
{
    //Determine user selection, and set vict type for temp match settings object and label for current victory type
    if(QString::compare(arg1,"First to Points Threshold") == 0)
    {
        tempSettingsObjectPtr->setGameVictoryType(0);
        ui->labelCurrGameVicType->setText("First to Points Threshold");
    }
    else if (QString::compare(arg1,"Max Goals in Set Time") == 0)
    {
        tempSettingsObjectPtr->setGameVictoryType(1);
        ui->labelCurrGameVicType->setText("Max Goals in Set Time");
    }
    else //Default parameter in case new victory type added, and slot not updated
    {
        ui->labelCurrGameVicType->setText("Error, Slot Not Updated");
    }
}


void userMatchSettingsWindow::on_buttonBox_accepted()
{
    parentmatchsettingsptr->setGameTimeLimit(tempSettingsObjectPtr->getGameTimeLimit());
    parentmatchsettingsptr->setNumberOfGames(tempSettingsObjectPtr->getNumberOfGames());
    parentmatchsettingsptr->setScoreThreshold(tempSettingsObjectPtr->getScoreThreshold());
    parentmatchsettingsptr->setGameVictoryType(tempSettingsObjectPtr->getGameVictoryType());
}
