/**
 * @file mainmenuwindow.cpp
 * @author Mohammad Iqbal, Mohammad Sarfraz, Sanjayan Kulendran, Natalia Bohulevych
 * @brief Implementation file used to implement the mainmenuwindow class
 * @version 0.5
 * @date 2020-12-02
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"

static const char* database_name = "game_records.db"; //!< Constant for naming the saved database.

MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuWindow)
{
    //Create main menu objects, TO-DO: get these objects from database
    matchSettingsObjPtr = new usermatchsettings();
    tableConfigObjPtr = new tableconfigurationsettings();
    playerAObjPtr = new player("playerA", 0, 0);
    playerBObjPtr = new player("playerB", 0, 0);

    ui->setupUi(this);
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}

void MainMenuWindow::on_pushButtonUserMatchSettings_clicked()
{
    //Create usermatchsettingswindow object, pass mainmenu usermatch settings object pointer

    userMatchSettingsWindowPtr = new userMatchSettingsWindow(this,this->matchSettingsObjPtr );
    userMatchSettingsWindowPtr->show();

}

void MainMenuWindow::on_pushButtonTableConfig_clicked()
{
    //Create tableconfig object and pass it to tableconfigwindow to be modified by user, as well as playerB in case of AI table mode
    tableConfigSettingsWindowPtr = new tableconfigurationsettingswindow(this,this->tableConfigObjPtr,this->playerBObjPtr);
    tableConfigSettingsWindowPtr->show();
}

void MainMenuWindow::on_pushButtonPlayerSettings_clicked()
{
    playerSettingsWindowPtr = new playersettingswindow(this, this->playerAObjPtr, this->playerBObjPtr);
    playerSettingsWindowPtr->show();
}

void MainMenuWindow::on_pushButtonStartMatch_clicked()
{

    //Initialize a temporary game vector
    std::vector<game> gameVector;

    //Initialize a vector of game structures
    std::vector<gameOutcome> gameOutcomes;

    //Initialize a game outcome
    gameOutcome currentGameOutcome;

    //Main component of Unique Match ID is UNIX time since epoch
    int matchTime = static_cast<int>(std::time(NULL));

    //Assemble match ID string before hashing, composed of time since epoch, player a name, player b name
    std::string preHashedMatchID = std::to_string(matchTime) + this->playerAObjPtr->getName() + this->playerBObjPtr->getName();

    //Create hash object
    std::hash<std::string> matchIDHasher;

    //hash match id, this reduces the chances of two matches sharing an ID due to system clock issues
    std::string currentMatchID = std::to_string(matchIDHasher(preHashedMatchID));

    //Initialize new match as modal ( to ensure match is complete before executing storage)
    matchDisplay curMatchDisplay(gameVector, this, this->matchSettingsObjPtr, this->tableConfigObjPtr,this->playerAObjPtr, this->playerBObjPtr);
    curMatchDisplay.setModal(true);
    curMatchDisplay.exec();

    //Store the the parameters that are constant for each game
    currentGameOutcome.matchID = currentMatchID;
    currentGameOutcome.playerAName = this->playerAObjPtr->getName();
    currentGameOutcome.playerBName = this->playerBObjPtr->getName();
    currentGameOutcome.tableMode = this->tableConfigObjPtr->getTableMode();

    //For every game in the match
    for (int i = static_cast<int>(gameVector.size()); i > 0; i--){

        //Copy the player scores
        currentGameOutcome.playerAScore = gameVector.back().getPlayerAScore();
        currentGameOutcome.playerBScore = gameVector.back().getPlayerBScore();

        //Add this element to the outcome vector
        gameOutcomes.push_back(currentGameOutcome);

        //Remove the element from the match-produced game vector
        gameVector.pop_back();

    }

    // Create/Open the database file using SQLite.
    char* err;
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open(database_name, &db);

    // Start by creating a table 'game_data' if not already present in file.
    std::string cmd = "CREATE TABLE IF NOT EXISTS game_data(ID varchar(100), player_A varchar(100)"
                      ", player_B varchar(100), A_score INT, B_score INT, table_mode INT);";
    int rc = sqlite3_exec(db, cmd.c_str(), NULL, NULL, &err);

    // Check to make sure we dont get any errors.
    if (rc != SQLITE_OK) {
        qDebug() << "Error: " << err;
    }

    // Insert all values from gameOutcome vector into the database.
    for(auto i = 0u; i < gameOutcomes.size(); i++){
        // Get each parameter from the game...
        auto ID = gameOutcomes.at(i).matchID;
        auto name_A = gameOutcomes.at(i).playerAName;
        auto name_B = gameOutcomes.at(i).playerBName;

        auto score_A = gameOutcomes.at(i).playerAScore;
        auto score_B = gameOutcomes.at(i).playerBScore;
        auto table_mode = gameOutcomes.at(i).tableMode;

        std::string query = "insert into game_data VALUES('" + ID + "','" + name_A + "', '" + name_B + "', "
                + std::to_string(score_A) + ", " +std::to_string(score_B) + ", " +std::to_string(table_mode)+ ");";

        int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);

        // Check to make sure we dont get any errors.
        if (rc != SQLITE_OK) {
            qDebug() << "Error: " << err;
        }
    }

    // Close the database.
    sqlite3_close(db);
}

 //Create databaseWindow object, pass mainmenu pointer
void MainMenuWindow::on_pushButtonDatabaseWindow_clicked()
{
    databaseWindowPtr = new databaseWindow(this);
    databaseWindowPtr->show();
}
