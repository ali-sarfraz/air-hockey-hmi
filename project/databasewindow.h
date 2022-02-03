/**
 * @file databasewindow.h
 * @author Ali Sarfraz
 * @brief Header file used to declare the database GUI window.
 *
 * This class is a simple SQLite database that is used to store a record of all the
 * games played during the operationl lifetime of the table. The databse contains a
 * unique match ID to distinguish matches from each other, along with records from the
 * games like the player names, the player scores, and the table mode that was used in
 * the game.
 *
 * @version 0.1
 * @date 2020-12-02
 *
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <fstream>

#include "MessageLibrary.h"

namespace Ui {
class databaseWindow;
}

/**
 * @brief The databaseWindow class is mainly used to use a GUI for inputing a player
 * name into the search bar, so that the system may perform a query on the stored database
 * and return a list of all the relevant matches to the standard output terminal for the
 * users to look at a specific player's game history.
 */
class databaseWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief The constructor for the database window in the GUI.
     *
     * @param parent A pointer to the parent window that creates this.
     */
    explicit databaseWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor function for closing the database window.
     */
    ~databaseWindow();

private slots:
    /**
     * @brief Computes an SQLite database query after the user has inserted a player name
     * that the wish to search the records for.
     *
     * Displays an error message if the record does not exist, or prints the player stats onto
     * the standard terminal if the records have returned successfully.
     */
    void on_pushButton_search_clicked();

private:
    /**
     * @brief Reference to the UI window for displaying and recieving information.
     */
    Ui::databaseWindow *ui;

    /**
     * @brief SQLite database built and stored along with the project binaries.
     */
    QSqlDatabase match_history;
};

#endif // DATABASEWINDOW_H
