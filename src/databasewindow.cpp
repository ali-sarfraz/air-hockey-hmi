/**
 * @file databasewindow.cpp
 * @author Ali Sarfraz
 * @brief Implementation file used to implement the databasewindow class
 * @version 0.1
 * @date 2020-12-02
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "databasewindow.h"
#include "ui_databasewindow.h"

static const char* database_name = "game_records.db"; //!< Const for keeping track of the database.

databaseWindow::databaseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databaseWindow)
{
    ui->setupUi(this);

    // Initialize the database.
    match_history = QSqlDatabase::addDatabase("QSQLITE");
    match_history.setDatabaseName(database_name);

    // Ensure that the database is present.
    // Close the window if not.
    std::ifstream database_file;
    database_file.open(database_name);
    if(!database_file){
        QMessageBox::critical(this, "Error", "Database does not exist!");
        QTimer::singleShot(0, this, SLOT(close()));
    }
    database_file.close();
}

databaseWindow::~databaseWindow()
{
    delete ui;
}

// Function that executes the search feature.
void databaseWindow::on_pushButton_search_clicked()
{
    // Access the string input by the user into the search bar.
    QString player_name = ui->lineEdit_player_name->text();

    // Open the databse file.
    match_history.open();

    // Perform a query in the database using the provided name as a key.
    // Will search in both Player_A and Player_B slots.
    QSqlQuery qry;
    if (!qry.exec("select * from game_data where player_A='" +
                  player_name +"' OR player_B='" + player_name + "';")){
        QMessageBox::critical(this, "Error", "Invalid Syntax!");
    } else {
        // Counter to keep track of the number of games matched.
        int count = 0;

        // Print all the data to the terminal for now...
        while (qry.next()) {
            qDebug () << "******************************************************";
            qDebug () << "Match ID:" << qry.value("ID").toString() << "\n";
            qDebug () << "Player A Name:" << qry.value("player_A").toString();
            qDebug () << "Player B Name:" << qry.value("player_B").toString();
            qDebug () << "Player A Score:" << qry.value("A_score").toInt();
            qDebug () << "Player B Score:" << qry.value("B_score").toInt();

            // Retrieve the table mode data.
            auto table_mode = qry.value("table_mode").toInt();

            // Switch on the table mode.
            switch (table_mode) {
            case ML_STANDARD:
                qDebug () << "Table Mode: Standard";
                break;
            case ML_ACCESSABILITY:
                qDebug () << "Table Mode: Accessability";
                break;
            case ML_AI:
                qDebug () << "Table Mode: AI";
                break;
            }

            count++;
         }

        // Display error if we haven't matched atleast one game with the provided string.
        if(count == 0){
            QMessageBox::critical(this, "Error", "No game records found!");
        }
     }
}
