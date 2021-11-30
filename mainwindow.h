#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "City.h"

#include <QMainWindow>

namespace Ui { class MainWindow; }

/**
 * The MainWindow class.
 *
 * Holds information and handles methods related to the main game window.
 */

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:

    // Enum class for side menu button
    enum class SideMenuButton {
        CLINIC = 1, HOSPITAL = 2, SILVER_MINE = 3, GOLD_MINE = 4, HOUSE = 5, APARTMENT = 6, STREET = 7, AVENUE = 8, DEMOLISH = 9, NAVIGATE = 10
    };

    // Enum class for overlay button
    enum class OverlayButton {
        NORMAL, TYPE, NEIGHBOR, ROAD
    };

    // Enum class for side menu status
    enum class SideMenuStatus {
        HIDDEN, HIDDEN_TO_VISIBLE, VISIBLE, VISIBLE_TO_HIDDEN
    };

    // Constructor and destructor of the Main Window
    MainWindow(City *const city, QWidget *parent = nullptr);
    ~MainWindow();

    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;

    // Accessors and mutators of private data members that save information about the current screen
    SideMenuButton get_selected_side_menu_button();
    OverlayButton get_selected_overlay_button();
    SideMenuStatus get_side_menu_status();
    void set_side_menu_status(SideMenuStatus status);

private slots:
    // Slots of buttons; Functions called when the buttons are clicked
    void on_btn_next_clicked();
    void on_btn_overlay_neighbor_clicked();
    void on_btn_overlay_normal_clicked();
    void on_btn_overlay_type_clicked();
    void on_btn_overlay_road_clicked();
    void on_btn_save_game_clicked();
    void on_btn_apartment_clicked();
    void on_btn_clinic_clicked();
    void on_btn_destruct_clicked();
    void on_btn_gold_clicked();
    void on_btn_hospital_clicked();
    void on_btn_house_clicked();
    void on_btn_navigate_clicked();
    void on_btn_silver_clicked();
    void on_btn_street_clicked();
    void on_btn_avenue_clicked();

private:
    // Initialization functions, called in constructor
    void initialize_overlay_buttons();
    void initialize_side_menu_buttons();

    // Function that processes button press events
    void on_overlay_button_clicked(OverlayButton button);
    void on_side_menu_button_clicked(SideMenuButton button);

    // Main loop of the main window that runs 50 times a second
    void main_loop();

    // Data member that points to the UI of the main window. Can access elements of the main window through it.
    Ui::MainWindow* ui;

    // Data member that saves the pointer to the current city.
    City *const city;

    // Loop timer used for the game loop
    QTimer* loop_timer;

    // Data member that saves information about the main window
    SideMenuButton selected_side_menu_button;
    OverlayButton selected_overlay_button;
    SideMenuStatus side_menu_status;

    friend class GameWidget;
};
#endif // MAINWINDOW_H
