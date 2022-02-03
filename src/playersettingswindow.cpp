/**
 * @file playersettingswindow.cpp
 * @author Natalia Bohulevych
 * @brief Implementation file used to implement the playersettingswindow class
 * @version 0.4
 * @date 2020-11-28
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "playersettingswindow.h"
#include "ui_playersettingswindow.h"
#include <QtGui>
#include<string>
#include <fstream>
#include <iostream>
#include <QDebug>

using namespace std;

/**
 * @brief Construct a new playersettingswindow object. This constructor is used when the main menu player settings
 * pushbutton is clicked. The constructor also intializes the GUI elements based on the provided tplayersettings object.
 *
 * @param parent => Pointer to the calling Qt window
 * @param playerAObjPtr => Pointer to readable parent player A object
 * @param playerBObjPtr => Pointer to readable parent player B object
 */
playersettingswindow::playersettingswindow(QWidget *parent, player *playerAObjPtr, player *playerBObjPtr) :
    QDialog(parent),
    ui(new Ui::playersettingswindow)
{
    //Keep track of parentPlayer using pointer
    parentPlayerAPtr = playerAObjPtr;
    parentPlayerBPtr = playerBObjPtr;

    tempPlayerAPtr = new player();
    tempPlayerAPtr->setName(parentPlayerAPtr->getName());
    tempPlayerAPtr->setpType(parentPlayerAPtr->getType());
    tempPlayerBPtr = new player();
    tempPlayerBPtr->setName(parentPlayerBPtr->getName());
    tempPlayerBPtr->setpType(parentPlayerBPtr->getType());

    ui->setupUi(this);


//COMBO BOXES
    //block signals
    ui->comboBox_playerAtype->blockSignals(1);
    ui->comboBox_playerBtype->blockSignals(1);

    //add type options in combo box
        //a
    ui->comboBox_playerAtype->addItem("Human");
    ui->comboBox_playerAtype->addItem("Accessibility");
        //b
    //Send signal to get table config from the table emulator
    std::vector<int> returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_TABLE_MODE);


    //incase message was not recieved then set to default value
    if (returnVal[0] >= 0 )
    {
         mode = uint(returnVal[1]);
    }

    if(mode==2)
    {
        ui->comboBox_playerBtype->addItem("AI");
    }
    else
    {
    ui->comboBox_playerBtype->addItem("Human");
    ui->comboBox_playerBtype->addItem("Accessibility");
    ui->comboBox_playerBtype->addItem("AI");
    }

    //blank combo box setup
    ui->comboBox_playerAtype->setCurrentIndex(-1);
    ui->comboBox_playerBtype->setCurrentIndex(-1);

    //unblock signals
    ui->comboBox_playerAtype->blockSignals(0);
    ui->comboBox_playerBtype->blockSignals(0);

}

/**
 * @brief Destructor for player settings window object
 */
playersettingswindow::~playersettingswindow()
{
    delete ui;
}

/**
 * @brief Function for when user clicks "OK" buttun in GUI window. Copies over changes made to
 * temporary player objects to passed (parent) player objects
 */
void playersettingswindow::on_buttonBox_accepted()
{
    parentPlayerAPtr->setName(tempPlayerAPtr->getName());
    parentPlayerBPtr->setName(tempPlayerBPtr->getName());
    parentPlayerAPtr->setpType(tempPlayerAPtr->getType());
    parentPlayerBPtr->setpType(tempPlayerBPtr->getType());
}

/**
 * @brief Function for when player B cursor is clicked on and the table mode is set to "Robotic-Opponent" (2).
 * Sets temporary player B's "Robot" if the table mode is set to "Robotic-Opponent" (2).
 */
void playersettingswindow::on_lineEdit_playerBname_cursorPositionChanged()
{
    //Send signal to get table config from the table emulator
    std::vector<int> returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_TABLE_MODE);

    mode = 0;

    //incase message was not recieved then set to default value
    if (returnVal[0] >= 0 )
    {
         mode = uint(returnVal[1]);
    }

    if(mode==2)
    {
        ui->lineEdit_playerBname->setText("Robot");
        ui->lineEdit_playerBname->setReadOnly(true);
    }
    else
    {
        ui->lineEdit_playerBname->setReadOnly(false);
    }
}

/**
 * @brief Function for when player A name is changed. Updates respective GUI element and
 * temporary player A's name to this new value.
 */
void playersettingswindow::on_lineEdit_playerAname_editingFinished()
{

    QString name = ui->lineEdit_playerAname->text();
    std::string pName = name.toStdString();
    tempPlayerAPtr->setName(pName);
}

/**
 * @brief Function for when player B name is changed. Updates respective GUI element and
 * temporary player B's name to this new value or changes the player B's name to "Robot" if the table mode is set to "Robotic-Opponent" (2)
 */
void playersettingswindow::on_lineEdit_playerBname_editingFinished()
{


    //Send signal to get table config from the table emulator
    std::vector<int> returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_TABLE_MODE);


    //incase message was not recieved then set to default value
    if (returnVal[0] >= 0 )
    {
         mode = uint(returnVal[1]);
    }

    if(mode==2)
    {
        ui->lineEdit_playerBname->setReadOnly(true);
        tempPlayerBPtr->setName("Robot");
    }
    else
    {
    QString name = ui->lineEdit_playerBname->text();
    std::string pName = name.toStdString();
    tempPlayerBPtr->setName(pName);
    }

}

/**
 * @brief Function for when player A type combo box is changed. Updates respective GUI element and
 * player A's type is set to this new value.
 *
 * @param arg1 => option chosen from combo box
 */
void playersettingswindow::on_comboBox_playerAtype_currentIndexChanged(const QString &arg1)
{

    if(QString::compare(arg1, "Human")==0)
    {
        tempPlayerAPtr->setpType(0); //set type
        ui->comboBox_playerAtype->setEnabled(1); //disable
        ui->comboBox_playerAtype->blockSignals(0);
    }
    else if(QString::compare(arg1, "Accessibility")==0)
    {
        tempPlayerAPtr->setpType(1); //set type
        ui->comboBox_playerAtype->setEnabled(1); //disable
        ui->comboBox_playerAtype->blockSignals(0);
    }
}

/**
 * @brief Function for when player B type combo box is changed. Updates respective GUI element and
 * player B's type is set to this new value or blocks option to change player name and type is table mode is
 * set to "Robotic-Opponent" (2)
 *
 * @param arg1 => option chosen from combo box
 */
void playersettingswindow::on_comboBox_playerBtype_currentIndexChanged(const QString &arg1)
{


    //Send signal to get table config from the table emulator
    std::vector<int> returnVal = MessageHandler::instance().sendMessage(M_RPI_GET_TABLE_MODE);


    //incase message was not recieved then set to default value
    if (returnVal[0] >= 0 )
    {
         mode = uint(returnVal[1]);
    }

    if(mode==2)
    {
        tempPlayerBPtr->setpType(2);
    }
    else
    {
        if(QString::compare(arg1, "Human")==0)
        {
            tempPlayerBPtr->setpType(0); //set type

        }
        else if(QString::compare(arg1, "Accessibility")==0)
        {
            tempPlayerBPtr->setpType(1); //set type
        }
        else if(QString::compare(arg1, "AI")==0)
        {
            tempPlayerBPtr->setpType(2); //set type
        }
    }
}
