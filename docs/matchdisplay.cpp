/**
 * @file matchdisplay.cpp
 * @author Sanjayan Kulendran
 * @brief Implementation file used to implent the qt5 based matchDisplay class.
 *
 * @version 1.0
 * @date 2020-11-30
 *
 *
 * @copyright Copyright (c) 2020
 *
 */


#include "matchdisplay.h"
#include "ui_matchdisplay.h"

matchDisplay::matchDisplay(std::vector<game> &gamesInMatchReturnPointer, QWidget *parent, usermatchsettings *matchSettingsObjPtr , tableconfigurationsettings *tableConfigObjPtr,  player *playerAObjPtr, player *playerBObjPtr) :
    QDialog(parent),
    ui(new Ui::matchDisplay)
{
    ui->setupUi(this);

    //Initialize the amount of games won
    playerAVictories = 0;
    playerBVictories = 0;

    //Initialize the amount of games needed to win
    firstTo = static_cast<int>(matchSettingsObjPtr->getNumberOfGames());

    //Output this in the match display
    ui->titleLabel->setText("First to " + QString::number(firstTo) + " Game Victories ");
    ui->titleLabel->setAlignment( Qt::AlignCenter);

    //Output the player labels
    ui->playerAlabel->setText(QString::fromStdString(playerAObjPtr->getName()));
    ui->playerBlabel->setText(QString::fromStdString(playerBObjPtr->getName()));

    //Set the internal game vector pointer to the passed by reference vector
    gamesInMatch = &gamesInMatchReturnPointer;

    //Save all the passed in pointers
    savedMatchSettingsObjPtr = matchSettingsObjPtr;
    savedTableConfigObjPtr = tableConfigObjPtr;
    savedPlayerAObjPtr = playerAObjPtr;
    savedPlayerBObjPtr = playerBObjPtr;

    //Initialize the match as not being over
    matchOver = false;


}

matchDisplay::~matchDisplay()
{
    delete ui;
}

void matchDisplay::on_pushButton_clicked()
{

    //If the match is not over
    if(!matchOver){

        //Start the next game as a modal
        gameDisplay curGameDisplay(*gamesInMatch, this, this->savedMatchSettingsObjPtr, this->savedTableConfigObjPtr,this->savedPlayerAObjPtr, this->savedPlayerBObjPtr);
        curGameDisplay.setModal(true);
        curGameDisplay.exec();

        //If player A had the higher score
        if((*gamesInMatch).back().getPlayerAScore() > (*gamesInMatch).back().getPlayerBScore()){

            //Increment player a's count
            playerAVictories++;
            //Update player a's display
            ui->playerAlcdNumber->display(playerAVictories);

        }
        //else If player B had the higher score
        else if((*gamesInMatch).back().getPlayerBScore() > (*gamesInMatch).back().getPlayerAScore()){

            //Increment player b's count
            playerBVictories++;
            //Update player b's display
            ui->playerBlcdnumber->display(playerBVictories);

        }
        //Other wise if there was a tie
        else if ((*gamesInMatch).back().getPlayerBScore() == (*gamesInMatch).back().getPlayerAScore()){

            //Increment player a's count
            playerAVictories++;
            //Update player a's display
            ui->playerAlcdNumber->display(playerAVictories);

            //Increment player b's count
            playerBVictories++;
            //Update player b's display
            ui->playerBlcdnumber->display(playerBVictories);

        }

        //Update player a's display
        //ui->playerAlcdNumber->display(playerAVictories);
        //Update player b's display
        //ui->playerBlcdnumber->display(playerBVictories);

        //If only player A has won enough games to win the match
        if ( (playerAVictories >= firstTo) && ( playerBVictories < firstTo) ){

            //End the match
            matchOver = true;

            //Display that player a is the victor
            ui->titleLabel->setText( QString::fromStdString(savedPlayerAObjPtr->getName()) + " WINS!");
            ui->titleLabel->setAlignment( Qt::AlignCenter);

            //Hghlight Player A's box
            ui->playerAlcdNumber->setSegmentStyle(QLCDNumber::Filled);
            ui->playerAlcdNumber->setPalette(QColor(25,255,100,255));

            //Set the pushbutton to an exit label
            ui->pushButton->setText(QString::fromStdString("Exit"));

        }
        //If only player B has won enough games to win the match
        else if ( (playerBVictories >= firstTo) && ( playerAVictories < firstTo) ){

            //End the match
            matchOver = true;

            //Display that player b is the victor
            ui->titleLabel->setText( QString::fromStdString(savedPlayerBObjPtr->getName()) + " WINS!");
            ui->titleLabel->setAlignment( Qt::AlignCenter);

            //Hghlight Player B's box
            ui->playerBlcdnumber->setSegmentStyle(QLCDNumber::Filled);
            ui->playerBlcdnumber->setPalette(QColor(25,255,100,255));

            //Set the pushbutton to an exit label
            ui->pushButton->setText(QString::fromStdString("Exit"));

        }

        //If both players have won enough games to win the match
        else if ( (playerAVictories >= firstTo) && (playerBVictories == playerAVictories)){

            //End the match
            matchOver = true;

            //Display that there is a tie
            ui->titleLabel->setText( QString::fromStdString(" TIE!"));
            ui->titleLabel->setAlignment( Qt::AlignCenter);


            //Hghlight Player A's box
            ui->playerAlcdNumber->setSegmentStyle(QLCDNumber::Filled);
            ui->playerAlcdNumber->setPalette(QColor(225,155,100,255));

            //Hghlight Player B's box
            ui->playerBlcdnumber->setSegmentStyle(QLCDNumber::Filled);
            ui->playerBlcdnumber->setPalette(QColor(225,155,100,255));

            //Set the pushbutton to an exit label
            ui->pushButton->setText(QString::fromStdString("Exit"));

        }

    }
    //If the match is finished
    else{

        //This functions as the close button
        matchDisplay::accept();


    }


}
