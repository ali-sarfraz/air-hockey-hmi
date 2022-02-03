/**
 * @file tableconfigurationsettingswindow.cpp
 * @author Mohammad Iqbal
 * @brief Implementation file used to implement the tableconfigurationsettingswindow class
 * @version 0.2
 * @date 2020-11-28
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "tableconfigurationsettingswindow.h"
#include "ui_tableconfigurationsettingswindow.h"


tableconfigurationsettingswindow::tableconfigurationsettingswindow(QWidget *parent, tableconfigurationsettings *tableConfigPtr, player *playerB) :
    QDialog(parent),
    ui(new Ui::tableconfigurationsettingswindow)
{
    //Keep track of parentTableConfig using pointer
    parentTableConfigPtr = tableConfigPtr;

    //Keep track of parent playerB using pointer
    parentPlayerBPtr = playerB;

    //Create temp tableconfig object to hold user changes, assign main menu table settings by default
    tempTableConfigPtr = new tableconfigurationsettings();
    tempTableConfigPtr->setTableMode(parentTableConfigPtr->getTableMode());
    tempTableConfigPtr->setAiDifficulty(parentTableConfigPtr->getAiDifficulty());
    tempTableConfigPtr->setTableAirSpeed(parentTableConfigPtr->getTableAirSpeed());
    tempTableConfigPtr->setTableLighting(parentTableConfigPtr->getTableLighting());

    ui->setupUi(this);

    //Block table mode combobox signals while its being setup
    ui->comboBoxTableMode->blockSignals(1);

    //Add table modes to combobox
    ui->comboBoxTableMode->addItem("Free-Play");
    ui->comboBoxTableMode->addItem("Accessiblity-Controlled");
    ui->comboBoxTableMode->addItem("Robotic-Opponent");

    //Set combobox as blank by default
    ui->comboBoxTableMode->setCurrentIndex(-1);

    //Have current table model label show main menu table mode by default
    if(tempTableConfigPtr->getTableMode() == 0)
    {
        ui->labelCurrTableMode->setText("Free-Play");
    }
    else if (tempTableConfigPtr->getTableMode() == 1)
    {
        ui->labelCurrTableMode->setText("Accessiblity-Controlled");
    }
    else if (tempTableConfigPtr->getTableMode() == 2)
    {
        ui->labelCurrTableMode->setText("Robotic-Opponent");
    }
    else
    {
        //Display error message in case label is not up to date
         ui->labelCurrTableMode->setText("Error, Unsupported Choice");
    }

    //Table Mode combobox set up, unblock signals
    ui->comboBoxTableMode->blockSignals(0);



    //Block Ai Difficulty combobox while being setup
    ui->comboBoxAiDiff->blockSignals(1);

    //Add Ai difficulty levels to combobox
    ui->comboBoxAiDiff->addItem("Beginner");
    ui->comboBoxAiDiff->addItem("Intermediate");
    ui->comboBoxAiDiff->addItem("Expert");

    //Set combobox as blank by default
    ui->comboBoxAiDiff->setCurrentIndex(-1);

    //Set current ai difficulty label to main menu ai difficulty as default
    if(tempTableConfigPtr->getTableMode() != 2)
    {
        ui->labelCurrAiDiff->setText("Not Applicable");
    }
    else if (tempTableConfigPtr->getAiDifficulty() == 0)
    {
        ui->labelCurrAiDiff->setText("Beginner");
    }
    else if (tempTableConfigPtr->getAiDifficulty() == 1)
    {
        ui->labelCurrAiDiff->setText("Intermediate");
    }
    else if (tempTableConfigPtr->getAiDifficulty() == 2)
    {
        ui->labelCurrAiDiff->setText("Expert");
    }
    else
    {
        //Display error message in case label is not up to date
        ui->labelCurrAiDiff->setText("Error, Unsupported Choice");
    }

    //Disable Ai difficulty combobox if not applicable to table mode
    if(tempTableConfigPtr->getTableMode() == 2)
    {
        ui->comboBoxAiDiff->setEnabled(1);
        //Unblock combobox signals
        ui->comboBoxAiDiff->blockSignals(0);
    }
    else
    {
        ui->comboBoxAiDiff->setEnabled(0);
    }


    //Setup table lighting textbox and slider

    ui->horizontalSliderTableLighting->blockSignals(1);     //block signals while being setup
    ui->labelCurrTableLighting->setText("");

    //update text box to provide user with lighting feedback

    tColor.setRgb(QRgb(parentTableConfigPtr->getTableLighting()));
    QPalette pal = ui->labelCurrTableLighting->palette();
    pal.setColor(ui->labelCurrTableLighting->backgroundRole(),tColor);
    ui->labelCurrTableLighting->setAutoFillBackground(1);
    ui->labelCurrTableLighting->setPalette(pal);


    ui->horizontalSliderTableLighting->setValue(parentTableConfigPtr->getTableLighting());
    ui->horizontalSliderTableLighting->blockSignals(0);     //slider free to use

    //Setup table airspeed textbox and slider
    ui->horizontalSliderTableAirSpeed->blockSignals(1);     //block signals while being setup
    ui->labelCurrTableAirSpeed->setText(QString::number(parentTableConfigPtr->getTableAirSpeed()));
    ui->horizontalSliderTableAirSpeed->setValue(int(parentTableConfigPtr->getTableAirSpeed()));
    ui->horizontalSliderTableAirSpeed->blockSignals(0);     //slider free to use
}


tableconfigurationsettingswindow::~tableconfigurationsettingswindow()
{
    delete ui;
}


void tableconfigurationsettingswindow::on_comboBoxTableMode_currentTextChanged(const QString &arg1)
{
    //Determine user selection for table mode and set temp object to it
    if(QString::compare(arg1,"Free-Play") == 0)
    {
        tempTableConfigPtr->setTableMode(0);
        ui->labelCurrTableMode->setText(arg1);

        //Make sure Ai Difficulty Combo box is disabled
        ui->comboBoxAiDiff->setEnabled(0);
        //Unblock combobox signals
        ui->comboBoxAiDiff->blockSignals(1);
        ui->labelCurrAiDiff->setText("Not Applicable");
    }
    else if (QString::compare(arg1,"Accessiblity-Controlled") == 0)
    {
        tempTableConfigPtr->setTableMode(1);
        ui->labelCurrTableMode->setText(arg1);

        //Make sure Ai Difficulty Combo box is disabled
        ui->comboBoxAiDiff->setEnabled(0);
        //Unblock combobox signals
        ui->comboBoxAiDiff->blockSignals(1);
        ui->labelCurrAiDiff->setText("Not Applicable");
    }
    else if (QString::compare(arg1,"Robotic-Opponent") == 0)
    {
        tempTableConfigPtr->setTableMode(2);
        ui->labelCurrTableMode->setText(arg1);

        //Enable AiDifficulty combobox
        ui->comboBoxAiDiff->setEnabled(1);
        //Unblock combobox signals
        ui->comboBoxAiDiff->blockSignals(0);

        //Update current ai difficulty label
        if (tempTableConfigPtr->getAiDifficulty() == 0)
        {
            ui->labelCurrAiDiff->setText("Beginner");
        }
        else if (tempTableConfigPtr->getAiDifficulty() == 1)
        {
            ui->labelCurrAiDiff->setText("Intermediate");
        }
        else if (tempTableConfigPtr->getAiDifficulty() == 2)
        {
            ui->labelCurrAiDiff->setText("Expert");
        }
        else
        {
            //Display error message in case label is not up to date
            ui->labelCurrAiDiff->setText("Error, Unsupported Choice");
        }


    }
    else //Default parameter in case new victory type added, and slot not updated
    {
        ui->labelCurrTableMode->setText("Error, Slot Not Updated");
    }
}


void tableconfigurationsettingswindow::on_buttonBox_accepted()
{
    //Apply user chosen table config settings to main menu table settings object
    parentTableConfigPtr->setTableMode(tempTableConfigPtr->getTableMode());
    parentTableConfigPtr->setAiDifficulty(tempTableConfigPtr->getAiDifficulty());
    parentTableConfigPtr->setTableAirSpeed(tempTableConfigPtr->getTableAirSpeed());
    parentTableConfigPtr->setTableLighting(tempTableConfigPtr->getTableLighting());

    //If Robotic Opponent is selected, update Player B name
    if (parentTableConfigPtr->getTableMode() == 2)
    {
        parentPlayerBPtr->setName("Robot");
    }

    //Update embedded system with table mode info
    MessageHandler::instance().sendMessage(M_RPI_SET_TABLE_MODE, std::to_string(parentTableConfigPtr->getTableMode()));
    MessageHandler::instance().sendMessage(M_RPI_SET_AI_DIFFICULTY, std::to_string(parentTableConfigPtr->getAiDifficulty()));
    MessageHandler::instance().sendMessage(M_RPI_SET_TABLE_LIGHTING, std::to_string(parentTableConfigPtr->getTableLighting()));
    MessageHandler::instance().sendMessage(M_RPI_SET_TABLE_AIR_SPEED, std::to_string(parentTableConfigPtr->getTableAirSpeed()));

    //Set table emulator ai state using singleton messenger
    if (parentTableConfigPtr->getTableMode() == 2)
    {
        MessageHandler::instance().sendMessage(M_RPI_SET_AI_ACTIVE_STATE, "0");
    }
    else
    {
        MessageHandler::instance().sendMessage(M_RPI_SET_AI_ACTIVE_STATE, "1");
    }
}


void tableconfigurationsettingswindow::on_comboBoxAiDiff_currentTextChanged(const QString &arg1)
{

    if(QString::compare(arg1,"Beginner") == 0)
    {
        tempTableConfigPtr->setAiDifficulty(0);
        ui->labelCurrAiDiff->setText("Beginner");
    }
    else if(QString::compare(arg1,"Intermediate") == 0)
    {
        tempTableConfigPtr->setAiDifficulty(1);
        ui->labelCurrAiDiff->setText("Intermediate");
    }
    else if(QString::compare(arg1,"Expert") == 0)
    {
        tempTableConfigPtr->setAiDifficulty(2);
        ui->labelCurrAiDiff->setText("Expert");
    }
    else
    {
        //Display error message in case label is not up to date
        ui->labelCurrAiDiff->setText("Error, Unsupported Choice");
    }

}



void tableconfigurationsettingswindow::on_horizontalSliderTableLighting_valueChanged(int value)
{
    //update table lighting value in temp object
    tempTableConfigPtr->setTableLighting(value);

    //update text box background colour to provide user with lighting feedback
    tColor.setRgb(QRgb(value));
    QPalette pal = ui->labelCurrTableLighting->palette();
    pal.setColor(ui->labelCurrTableLighting->backgroundRole(),tColor);
    ui->labelCurrTableLighting->setAutoFillBackground(1);
    ui->labelCurrTableLighting->setPalette(pal);

}


void tableconfigurationsettingswindow::on_horizontalSliderTableAirSpeed_valueChanged(int value)
{
    //update air speed value in temp object
    if (value <= 0)
    {
        tempTableConfigPtr->setTableAirSpeed(0);
    }
    else if (value >=100)
    {
        tempTableConfigPtr->setTableAirSpeed(100);
    }
    else
    {
        tempTableConfigPtr->setTableAirSpeed(uint(value));
    }


    //update text box to provide user with air speed feedback
    ui->labelCurrTableAirSpeed->setText(QString::number(tempTableConfigPtr->getTableAirSpeed()));
}
