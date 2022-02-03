/**
 * @file gamedisplay.cpp
 * @author Sanjayan Kulendran
 * @brief Implementation file used to Implement the qt5 based gameDisplay class.
 * @version 1.1
 * @date 2020-11-30
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "gamedisplay.h"
#include "ui_gamedisplay.h"

#define DISPLAY_UPDATE_PERIOD 100 //!< Define the display update period [ms]
#define MESSAGE_UPDATE_PERIOD 1000 //!< Define the message update period [ms]

/**
 * @brief Implementation file used to Implement the qt5 based gameDisplay class.
 */
gameDisplay::gameDisplay(std::vector<game> &gameReturnPointer, QWidget *parent, usermatchsettings *matchSettingsObjPtr , tableconfigurationsettings *tableConfigObjPtr,  player *playerAObjPtr, player *playerBObjPtr) :
    QDialog(parent),
    ui(new Ui::gameDisplay)
{

    //Setup user interface
    ui->setupUi(this);

    //Default values for display and poll update variables
    displayUpdateInterval = DISPLAY_UPDATE_PERIOD; //1000 = update display every second
    messagePollInterval = MESSAGE_UPDATE_PERIOD; //500 = update score/check messages every second

    //Save the pointers to the players
    playerA = playerAObjPtr;
    playerB = playerBObjPtr;

    //Setup the player names
    ui->playerALabel->setText(QString::fromStdString(playerA->getName()));
    ui->playerBLabel->setText(QString::fromStdString(playerB->getName()));

    //If the game victory type integer is 0, the game finishes on score (consider changing this for consistency)
    if (matchSettingsObjPtr->getGameVictoryType() == 0){

        //Create a new score based game
        currentGame = new game(true, matchSettingsObjPtr->getScoreThreshold());

        //Initizalize the game timer to zero (in score based we are going up)
        gameTime = 0;

        //Set the game display to reflect that it is score-threshold based
        ui->timerLabel->setText("Time Elapsed");
        ui->timerLabel->setAlignment( Qt::AlignCenter);
        ui->goalTargetLabel->setText("Goals for Victory");
        ui->pointGoalNumber->display(static_cast<int>(matchSettingsObjPtr->getScoreThreshold()));


    }
    //Otherwise, the game finishes on a timer
    else{

        //Create a timer based game (kept true while game objects are finalized)
        currentGame = new game(false, matchSettingsObjPtr->getGameTimeLimit());

        //Initialize the game timer to the time limit
        gameTime = 60*(static_cast<int>(matchSettingsObjPtr->getGameTimeLimit()));

        //Hide goals to victory
        ui->pointGoalNumber->hide();

        //Set the game display to reflect that it is timer based
        ui->timerLabel->setText("Time Remaining");
        ui->timerLabel->setAlignment( Qt::AlignCenter);

    }

    //Store the pointer to the game vector for reference on finishing the game
    gameVector = &gameReturnPointer;

    //Setup the new display timer
    gameTimeUpdater = new QTimer(this);

    //Setup the connection between the timer and the display update function
    connect(gameTimeUpdater, SIGNAL(timeout()), this, SLOT(displayUpdate()));

    //Start the timer with the display interval value
    gameTimeUpdater->start(displayUpdateInterval);

    //Setup the new communications timer
    messagePollTimer = new QTimer(this);

    //Setup the connection between the timer and the poll update function
    connect(messagePollTimer, SIGNAL(timeout()), this, SLOT(updateScore()));

    //Start the timer with the poll interval value
    messagePollTimer->start(messagePollInterval);

    //Game is unpaused
    gamePaused = false;

    //Send signal to start the table emulator
    MessageHandler::instance().sendMessage(M_RPI_SET_GAME_ACTIVE_STATE, TO_STRING(ML_ACTIVE));


}


void gameDisplay::displayUpdate(){

    //If the game is not finished or paused
    if ((currentGame->isGameFinished() != true ) && (!gamePaused)){

        //If the game finishes on score
        if (currentGame->getDoesGameFinishOnScore()){

            //Increment the timer by the display update interval value
            gameTime = gameTime + displayUpdateInterval/1000;

        }
        //Otherwise, if the game finishes on a timer
        else{

            //Decrement the timer by the display update interval value ( minimum value of 0)
            if (0 > ( gameTime - displayUpdateInterval/1000)) gameTime = 0;
            else gameTime -= displayUpdateInterval/1000;

            //If the game time has dipped below/is zero then end the game
            if(static_cast<int>(gameTime) == 0) currentGame->endGame();

        }

        //- - - - - - - - - update the display

        //Update the minute value to the integer division of the second count (relies on C99+ behviour of rounding towards zero in integer division)
        ui->minlcdNumber->display(static_cast<int>(gameTime)/60);

        //Update the second value with the modulo with 60 of the second count
        ui->seclcdNumber->display(QString("%1").arg((static_cast<int>(gameTime)%60), 2, 10, QChar('0')));

        //Update the game score
        ui->pAlcdNumber->display(static_cast<int>(currentGame->getPlayerAScore()));
        ui->pBlcdNumber->display(static_cast<int>(currentGame->getPlayerBScore()));

    }

    //Otherwise, If the game is finished
    else if (currentGame->isGameFinished()){

        //Update the game score
        ui->pAlcdNumber->display(static_cast<int>(currentGame->getPlayerAScore()));
        ui->pBlcdNumber->display(static_cast<int>(currentGame->getPlayerBScore()));

        //If player A had the higher score
        if( currentGame->getPlayerAScore() > currentGame->getPlayerBScore()){

            //Output that player a won
            ui->timerLabel->setText( QString::fromStdString(playerA->getName()) + " WINS!");
            ui->timerLabel->setAlignment( Qt::AlignCenter);

            //Change the colour
            ui->pAlcdNumber->setSegmentStyle(QLCDNumber::Filled);
            ui->pAlcdNumber->setPalette(QColor(25,255,100,255));


        }
        //If player B had a higher score
        if( currentGame->getPlayerBScore() > currentGame->getPlayerAScore()){

            //Output that player b won
            ui->timerLabel->setText( QString::fromStdString(playerB->getName()) + " WINS!");
            ui->timerLabel->setAlignment( Qt::AlignCenter);

            //Change output colour
            ui->pBlcdNumber->setSegmentStyle(QLCDNumber::Filled);
            ui->pBlcdNumber->setPalette(QColor(25,255,100,255));

        }
        //Otherwise if tied
        if( currentGame->getPlayerBScore() == currentGame->getPlayerAScore()){

            //Output that there was a tie
            ui->timerLabel->setText(" TIE!");
            ui->timerLabel->setAlignment( Qt::AlignCenter);

            //Change output colour
            ui->pBlcdNumber->setSegmentStyle(QLCDNumber::Filled);
            ui->pBlcdNumber->setPalette(QColor(255,255,100,255));
            ui->pAlcdNumber->setSegmentStyle(QLCDNumber::Filled);
            ui->pAlcdNumber->setPalette(QColor(255,255,100,255));

        }

        //Hide the pause button
        ui->playPausepushButton->hide();

        //Colour the exit button
        ui->exitButton->setStyleSheet("background-color:green");

    }

}


void gameDisplay::updateScore(){

    //If the game is not finished, or paused
    if ((currentGame->isGameFinished() != true ) && (!gamePaused)){

        //Check to see if goal is scored (through communication singleton table emulator)
        std::vector<int> returnVal = MessageHandler::instance().unsolicitedQueueGet();

        //If there is something to read
        if(!(returnVal[0] < 0)){

            //Assign the relevant goal to the game
            currentGame->addGoal(returnVal[2], static_cast<bool>(returnVal[1]));

            //Assign this speed to the respective speed meter
            if (returnVal[1]) ui->pASpeedlcdNumber->display(static_cast<int>(returnVal[2]));
            else ui->pBSpeedlcdNumber->display(static_cast<int>(returnVal[2]));

        }

    }

}

gameDisplay::~gameDisplay()
{
    delete ui;
}


void gameDisplay::on_playPausepushButton_clicked(bool checked)
{

    //When released, the game is not paused
    gamePaused = checked;

    //Name the button accordingly
    if (gamePaused){

        //Pause the table emulator
        MessageHandler::instance().sendMessage(M_RPI_SET_GAME_ACTIVE_STATE, TO_STRING(ML_INACTIVE));

        ui->playPausepushButton->setText("Resume");
        //Colour the exit button
        ui->playPausepushButton->setStyleSheet("background-color:green");

    }

    else {

        //Restart the table emulator
        MessageHandler::instance().sendMessage(M_RPI_SET_GAME_ACTIVE_STATE, TO_STRING(ML_ACTIVE));

        //Colour the exit button
        ui->playPausepushButton->setStyleSheet("background-color:yellow");
        ui->playPausepushButton->setText("Pause");
    }

}

void gameDisplay::on_exitButton_clicked()
{

    //Stop the table emulator
    MessageHandler::instance().sendMessage(M_RPI_SET_GAME_ACTIVE_STATE, TO_STRING(ML_INACTIVE));

    //Delete the timers
    delete gameTimeUpdater;
    delete messagePollTimer;

    //Push the game onto the vector
    gameVector->push_back(*currentGame);

    //If the game was concluded before close was pressed, exit the game display with an accept
    if (currentGame->isGameFinished()) gameDisplay::accept();

    //Otherwise, end the game with a reject
    else gameDisplay::reject();

}
