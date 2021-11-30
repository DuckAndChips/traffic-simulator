#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "City.h"

#include <QMainWindow>

namespace Ui { class MenuWindow; }

/**
 * The MenuWindow class.
 *
 * Holds information and handles methods related to the menu window.
 */

class MenuWindow: public QMainWindow
{
    Q_OBJECT

public:
    // Constructors and destructors of the menu window
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private:
    // Function that starts the game
    void start_game(City *city);

    // Data member that points to the UI of the menu window. Can access elements of the main window through it.
    Ui::MenuWindow *ui;

    // Store the grid size in this variable
    int selected_grid_size;

private slots:
    // Slots of buttons; Functions called when the buttons are clicked
    void on_btn_new_clicked();
    void on_btn_load_clicked();
    void on_btn_increase_size_clicked();
    void on_btn_decrease_size_clicked();
    void on_btn_start_game_clicked();
};

#endif // MENUWINDOW_H
