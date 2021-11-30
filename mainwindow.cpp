#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "City.h"

#include <QString>
#include <QTimer>
#include <QFileDialog>
#include <QMainWindow>

const QString BTN_RELEASED_STYLE = "background-color: rgba(50, 127, 127, 255);";
const QString BTN_SELECTED_STYLE = "background-color: rgba(255, 255, 255, 255);";

/**
 * Constructor of Main Window.
 *
 * Initializes its data members, with buttons set to their default selections.
 * (Navigate as default side menu button; Normal overlay as default overlay button)
 * Sets up UI. Initializes the styles and labels of all buttons.
 * Runs th game loop so that it runs 50 times a second.
 * Configures the position of the side menu.
 *
 * @param city Pointer to the current city
 * @param parent Pointer to its parent widget
 */
MainWindow::MainWindow(City *const city, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        city(city),
        selected_side_menu_button(SideMenuButton::NAVIGATE),
        selected_overlay_button(OverlayButton::NORMAL),
        side_menu_status(SideMenuStatus::HIDDEN)
{
    ui->setupUi(this);

    initialize_overlay_buttons();
    initialize_side_menu_buttons();

    // Run main loop
    loop_timer = new QTimer{this };
    connect(loop_timer, &QTimer::timeout, this, &MainWindow::main_loop);
    // 50 updates per second
    loop_timer->start(20);

    ui->side_menu_move->move(400,0);
    ui->side_menu->setMaximumWidth(0);
}

/**
 * Initializes the styles and labels of all side menu buttons.
 *
 * Sets the label of the side menu buttons to have the corresponding costs.
 * Sets the style of the side menu buttons to be in released style except for Navigate which has selected style.
 */
void MainWindow::initialize_side_menu_buttons() {
    ui->btn_clinic->setText(ui->btn_clinic->text() + " $" + QString::number(Clinic::cost));
    ui->btn_hospital->setText(ui->btn_hospital->text() + " $" + QString::number(Hospital::cost));
    ui->btn_silver->setText(ui->btn_silver->text() + " $" + QString::number(SilverMine::cost));
    ui->btn_gold->setText(ui->btn_gold->text() + " $" + QString::number(GoldMine::cost));
    ui->btn_house->setText(ui->btn_house->text() + " $" + QString::number(House::cost));
    ui->btn_apartment->setText(ui->btn_apartment->text() + " $" + QString::number(Apartment::cost));
    ui->btn_street->setText(ui->btn_street->text() + " $" + QString::number(Street::cost));
    ui->btn_avenue->setText(ui->btn_avenue->text() + " $" + QString::number(Avenue::cost));

    // START OF YOUR IMPLEMENTATION
    ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_street->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_avenue->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
    ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
    // END OF YOUR IMPLEMENTATION
}

/**
 * Initializes the styles and labels of all overlay buttons.
 *
 * Sets the label of the side menu buttons to have the corresponding costs.
 * Sets the style of the side menu buttons to be in released style except for Navigate which has selected style.
 */
void MainWindow::initialize_overlay_buttons() {
    // START OF YOUR IMPLEMENTATION
    ui->btn_overlay_normal->setStyleSheet(BTN_SELECTED_STYLE);
    ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_overlay_road->setStyleSheet(BTN_RELEASED_STYLE);
    // END OF YOUR IMPLEMENTATION
}

/**
 * Destructor of the main window
 *
 * Stops the game loop.
 * Deallocates UI, loop timer and the city.
 */
MainWindow::~MainWindow() {
    delete ui;
    loop_timer->stop();
    delete loop_timer;
    delete city;
}

/**
 * Gets the currently selected side menu button
 *
 * @return Selected side menu button (MainWindow::SideMenuButton)
 */
MainWindow::SideMenuButton MainWindow::get_selected_side_menu_button() {
    return selected_side_menu_button;
}

/**
 * Gets the currently selected overlay button
 *
 * @return Selected overlay button (MainWindow::OverlayButton)
 */
MainWindow::OverlayButton MainWindow::get_selected_overlay_button() {
    return selected_overlay_button;
}

/**
 * Gets the current side menu status
 *
 * Controls the animation of the side menu.
 *
 * @return Side menu status (MainWindow::SideMenuStatus)
 */
MainWindow::SideMenuStatus MainWindow::get_side_menu_status() {
    return side_menu_status;
}

/**
 * Sets the current side menu status
 *
 * Controls the animation of the side menu.
 *
 * @param Side menu status (MainWindow::SideMenuStatus)
 */
void MainWindow::set_side_menu_status(SideMenuStatus status) {
    side_menu_status = status;
}

/**
 * Centralized function that processes a click event of a side menu button.
 *
 * If the provided button is a building or a road,
 * if the city has enough budget, it updates the data members and button styles so that the provided button is selected;
 * otherwise, it updates the data members and button styles so that the Navigate button is selected.
 *
 * If the provided button is the Navigate or Remove button,
 * it updates the data members and button styles so that the provided button is selected.
 *
 * @param button Clicked side menu button (MainWindow::SideMenuButton)
 */
void MainWindow::on_side_menu_button_clicked(SideMenuButton button) {
    // START OF YOUR IMPLEMENTATION
    switch(button){
    case SideMenuButton::APARTMENT:
        if(city->get_budget() < 300){
            //insufficient money
            MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
            break;
        }
        MainWindow::selected_side_menu_button = SideMenuButton::APARTMENT;
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_street->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_avenue->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case SideMenuButton::CLINIC:
        if(city->get_budget() < 50){
            //insufficient money
            MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
            break;
        }
        MainWindow::selected_side_menu_button = SideMenuButton::CLINIC;
        ui->btn_clinic->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_street->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_avenue->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case SideMenuButton::DEMOLISH:
        MainWindow::selected_side_menu_button = SideMenuButton::DEMOLISH;
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_street->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_avenue->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case SideMenuButton::GOLD_MINE:
        if(city->get_budget() < 400){
            //insufficient money
            MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
            break;
        }
        MainWindow::selected_side_menu_button = SideMenuButton::GOLD_MINE;
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_street->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_avenue->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case SideMenuButton::HOSPITAL:
        if(city->get_budget() < 500){
            //insufficient money
            MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
            break;
        }
        MainWindow::selected_side_menu_button = SideMenuButton::HOSPITAL;
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_street->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_avenue->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case SideMenuButton::HOUSE:
        if(city->get_budget() < 50){
            //insufficient money
            MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
            break;
        }
        MainWindow::selected_side_menu_button = SideMenuButton::HOUSE;
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_street->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_avenue->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case SideMenuButton::NAVIGATE:
        MainWindow::selected_side_menu_button = SideMenuButton::NAVIGATE;
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_street->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_avenue->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case SideMenuButton::SILVER_MINE:
        if(city->get_budget() < 50){
            //insufficient money
            MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
            break;
        }
        MainWindow::selected_side_menu_button = SideMenuButton::SILVER_MINE;
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_street->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_avenue->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case SideMenuButton::STREET:
        if(city->get_budget() < Street::cost){
            //insufficient money
            MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
            break;
        }
        MainWindow::selected_side_menu_button = SideMenuButton::STREET;
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_street->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_avenue->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case SideMenuButton::AVENUE:
        if(city->get_budget() < Avenue::cost){
            //insufficient money
            MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
            break;
        }
        MainWindow::selected_side_menu_button = SideMenuButton::AVENUE;
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_street->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_avenue->setStyleSheet(BTN_SELECTED_STYLE);
        break;
    }
    // END OF YOUR IMPLEMENTATION
}

/**
 * Centralized function that processes a click event of a side menu button.
 *
 * Updates the data members and button styles so that the provided button is selected.
 *
 * @param button Clicked overlay button (MainWindow::OverlayButton)
 */
void MainWindow::on_overlay_button_clicked(OverlayButton button) {
    // START OF YOUR IMPLEMENTATION
    //ui->btn_overlay_normal->setStyleSheet(BTN_RELEASED_STYLE);
    //ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
    //ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
    switch (button){
    case OverlayButton::ROAD:
        ui->btn_overlay_normal->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_road->setStyleSheet(BTN_SELECTED_STYLE);
        break;
    case OverlayButton::NEIGHBOR:
        ui->btn_overlay_normal->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_neighbor->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_road->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case OverlayButton::NORMAL:
        ui->btn_overlay_normal->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_road->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case OverlayButton::TYPE:
        ui->btn_overlay_normal->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_type->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_overlay_road->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    }

    // END OF YOUR IMPLEMENTATION
}

/** Main loop of the main window
 *
 * This main loop is called 50 times a second.
 * It controls the animation of the side menu according to the side menu status of the main window.
 */
void MainWindow::main_loop() {
    switch (side_menu_status) {
        case SideMenuStatus::HIDDEN:
            break;
        case SideMenuStatus::HIDDEN_TO_VISIBLE:
            ui->side_menu->setMaximumWidth(400);
            // START OF YOUR IMPLEMENTATION
            MainWindow::ui->side_menu_move->move(MainWindow::ui->side_menu_move->x()-10,MainWindow::ui->side_menu_move->y());
            //MainWindow::ui->side_menu_move->move(QPoint(-10,0) + pos());   // appear instantly
            if (MainWindow::ui->side_menu_move->x() <= 0){
                side_menu_status = SideMenuStatus::VISIBLE;

            }
            // END OF YOUR IMPLEMENTATION
            break;
        case SideMenuStatus::VISIBLE:
            break;
        case SideMenuStatus::VISIBLE_TO_HIDDEN:
            // START OF YOUR IMPLEMENTATION

            // MOVEEEE TO LEFT
            MainWindow::ui->side_menu_move->move(MainWindow::ui->side_menu_move->x()+10,MainWindow::ui->side_menu_move->y());
            //MainWindow::ui->side_menu_move->move(QPoint(10,0)+ pos());   //appear instantly
            if (MainWindow::ui->side_menu_move->x() >= 400){
                side_menu_status = SideMenuStatus::HIDDEN;
                ui->side_menu->setMaximumWidth(0);
            }
            // END OF YOUR IMPLEMENTATION
            break;
    }
    ui->side_menu_move->setFixedWidth(ui->side_menu->width());
    ui->side_menu_move->setFixedHeight(ui->side_menu->height());

    ui->widget->loop();
}


/**
 * Function that handles the click event of the Next turn button.
 *
 * Calls the function that moves to the next turn in city.
 */
void MainWindow::on_btn_next_clicked(){
    city->move_to_next_turn();
}

/**
 * Function (slot) that handles the click event of the Neighbor Overlay button.
 *
 * Updates the data members and calls the centralized function that handles the click event of overlay buttons.
 */
void MainWindow::on_btn_overlay_neighbor_clicked(){
    on_overlay_button_clicked(OverlayButton::NEIGHBOR);
    MainWindow::selected_overlay_button = OverlayButton::NEIGHBOR;
}
/**
 * Function (slot) that handles the click event of the Normal Overlay button.
 *
 * Updates the data members and calls the centralized function that handles the click event of overlay buttons.
 */
void MainWindow::on_btn_overlay_normal_clicked(){
    on_overlay_button_clicked(OverlayButton::NORMAL);
    MainWindow::selected_overlay_button = OverlayButton::NORMAL;
}
/**
 * Function (slot) that handles the click event of the Type Overlay button.
 *
 * Updates the data members and calls the centralized function that handles the click event of overlay buttons.
 */
void MainWindow::on_btn_overlay_type_clicked(){
    on_overlay_button_clicked(OverlayButton::TYPE);
    MainWindow::selected_overlay_button = OverlayButton::TYPE;
}
/**
 * Function (slot) that handles the click event of the Road Overlay button.
 *
 * Updates the data members and calls the centralized function that handles the click event of overlay buttons.
 */
void MainWindow::on_btn_overlay_road_clicked(){
    on_overlay_button_clicked(OverlayButton::ROAD);
    MainWindow::selected_overlay_button = OverlayButton::ROAD;
}
/**
 * Function (slot) that handles the click event of the Save button.
 *
 * Opens a file dialog and saves the city into the text file selected if the text file is valid.
 */
void MainWindow::on_btn_save_game_clicked(){
    QString filename = QFileDialog::getSaveFileName(this,tr("Save File"),"/home",tr("text files (*.txt)"));
    if(!filename.isEmpty()&& !filename.isNull()){
        std::string filenamestr = filename.toStdString();
        city->save(filenamestr);
    }
}

/**
 * Function (slot) that handles the click event of the each side menu button.
 *
 * Calls the centralized function that handles the click event of side menu buttons.
 */
void MainWindow::on_btn_apartment_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::APARTMENT);
}
void MainWindow::on_btn_clinic_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::CLINIC);
}
void MainWindow::on_btn_destruct_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::DEMOLISH);
}
void MainWindow::on_btn_gold_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::GOLD_MINE);
}
void MainWindow::on_btn_hospital_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::HOSPITAL);
}
void MainWindow::on_btn_house_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::HOUSE);
}
void MainWindow::on_btn_navigate_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
}
void MainWindow::on_btn_silver_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::SILVER_MINE);
}
void MainWindow::on_btn_street_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::STREET);
}
void MainWindow::on_btn_avenue_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::AVENUE);
}

