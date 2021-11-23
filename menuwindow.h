#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "City.h"

#include <QMainWindow>

namespace Ui { class MenuWindow; }

class MenuWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private:
    void start_game(City *city);

    Ui::MenuWindow *ui;

    // Store the grid size in this variable
    int selected_grid_size;

private slots:
    void on_btn_new_clicked();
    void on_btn_load_clicked();

    void on_btn_increase_size_clicked();
    void on_btn_decrease_size_clicked();

    void on_btn_start_game_clicked();
};

#endif // MENUWINDOW_H
