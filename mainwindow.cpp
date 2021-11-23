#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "City.h"

#include <QString>
#include <QTimer>
#include <QFileDialog>
#include <QMainWindow>

const QString BTN_RELEASED_STYLE = "background-color: rgba(50, 127, 127, 255);";
const QString BTN_SELECTED_STYLE = "background-color: rgba(255, 255, 255, 255);";

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

void MainWindow::initialize_side_menu_buttons() {
    ui->btn_clinic->setText(ui->btn_clinic->text() + " $" + QString::number(Clinic::cost));
    ui->btn_hospital->setText(ui->btn_hospital->text() + " $" + QString::number(Hospital::cost));
    ui->btn_silver->setText(ui->btn_silver->text() + " $" + QString::number(SilverMine::cost));
    ui->btn_gold->setText(ui->btn_gold->text() + " $" + QString::number(GoldMine::cost));
    ui->btn_house->setText(ui->btn_house->text() + " $" + QString::number(House::cost));
    ui->btn_apartment->setText(ui->btn_apartment->text() + " $" + QString::number(Apartment::cost));

    // START OF YOUR IMPLEMENTATION
    ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
    // END OF YOUR IMPLEMENTATION
}

void MainWindow::initialize_overlay_buttons() {
    // START OF YOUR IMPLEMENTATION
    ui->btn_overlay_normal->setStyleSheet(BTN_SELECTED_STYLE);
    ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
    selected_overlay_button = OverlayButton::NORMAL;
    // END OF YOUR IMPLEMENTATION
}

MainWindow::~MainWindow() {
    delete ui;
    loop_timer->stop();
    delete loop_timer;
    delete city;
}

MainWindow::SideMenuButton MainWindow::get_selected_side_menu_button() {
    return selected_side_menu_button;
}

MainWindow::OverlayButton MainWindow::get_selected_overlay_button() {
    return selected_overlay_button;
}

MainWindow::SideMenuStatus MainWindow::get_side_menu_status() {
    return side_menu_status;
}

void MainWindow::set_side_menu_status(SideMenuStatus status) {
    side_menu_status = status;
}

void MainWindow::on_side_menu_button_clicked(SideMenuButton button) {
    // START OF YOUR IMPLEMENTATION
    ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
    switch (button) {
        case SideMenuButton::CLINIC:
            if(city->can_construct(Building::Type::CLINIC) == true){
                ui->btn_clinic->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::CLINIC;
            }
            else{
                ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::NAVIGATE;
            }
            break;
        case SideMenuButton::HOSPITAL:
            if(city->can_construct(Building::Type::HOSPITAL) == true){
                ui->btn_hospital->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::HOSPITAL;
            }
            else{
                ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::NAVIGATE;
            }
            break;
        case SideMenuButton::GOLD_MINE:
            if(city->can_construct(Building::Type::GOLD_MINE) == true){
                ui->btn_gold->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::GOLD_MINE;
            }
            else{
                ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::NAVIGATE;
            }
            break;
        case SideMenuButton::SILVER_MINE:
            if(city->can_construct(Building::Type::SILVER_MINE) == true){
                ui->btn_silver->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::SILVER_MINE;
            }
            else{
                ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::NAVIGATE;
            }
            break;
        case SideMenuButton::HOUSE:
            if(city->can_construct(Building::Type::HOUSE) == true){
                ui->btn_house->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::HOUSE;
            }
            else{
                ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::NAVIGATE;
            }
            break;
        case SideMenuButton::APARTMENT:
            if(city->can_construct(Building::Type::APARTMENT) == true){
                ui->btn_apartment->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::APARTMENT;
            }
            else{
                ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
                MainWindow::selected_side_menu_button = SideMenuButton::NAVIGATE;
            }
            break;
        case SideMenuButton::NAVIGATE:
            ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
            MainWindow::selected_side_menu_button = SideMenuButton::NAVIGATE;
            break;
        case SideMenuButton::DEMOLISH:
            ui->btn_destruct->setStyleSheet(BTN_SELECTED_STYLE);
            MainWindow::selected_side_menu_button = SideMenuButton::DEMOLISH;
            break;
    }

    // END OF YOUR IMPLEMENTATION
}

void MainWindow::on_overlay_button_clicked(OverlayButton button) {
    // START OF YOUR IMPLEMENTATION
    ui->btn_overlay_normal->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
    switch (button) {
        case OverlayButton::NORMAL:
            ui->btn_overlay_normal->setStyleSheet(BTN_SELECTED_STYLE);
            selected_overlay_button = OverlayButton::NORMAL;
            break;
        case OverlayButton::NEIGHBOR:
            ui->btn_overlay_neighbor->setStyleSheet(BTN_SELECTED_STYLE);
            selected_overlay_button = OverlayButton::NEIGHBOR;
            break;
        case OverlayButton::TYPE:
            ui->btn_overlay_type->setStyleSheet(BTN_SELECTED_STYLE);
            selected_overlay_button = OverlayButton::TYPE;
            break;
    }
    // END OF YOUR IMPLEMENTATION
}

// This is called 50 times per second
void MainWindow::main_loop() {
    switch (side_menu_status) {
        case SideMenuStatus::HIDDEN:
            break;
        case SideMenuStatus::HIDDEN_TO_VISIBLE:
            ui->side_menu->setMaximumWidth(400);
            // START OF YOUR IMPLEMENTATION
                if(ui->side_menu_move->x() > 0){
                    ui->side_menu_move->move(ui->side_menu_move->x()-10,ui->side_menu_move->y());
                }
                else{
                    MainWindow::side_menu_status = SideMenuStatus::VISIBLE;
                }
            // END OF YOUR IMPLEMENTATION
            break;
        case SideMenuStatus::VISIBLE:
            break;
        case SideMenuStatus::VISIBLE_TO_HIDDEN:
            // START OF YOUR IMPLEMENTATION
            if(ui->side_menu_move->x() < 400){
                ui->side_menu_move->move(ui->side_menu_move->x()+10,ui->side_menu_move->y());
            }
            else{
                MainWindow::side_menu_status = SideMenuStatus::HIDDEN;
                ui->side_menu->setMaximumWidth(0);
            }
            // END OF YOUR IMPLEMENTATION
            break;
    }
    ui->side_menu_move->setFixedWidth(ui->side_menu->width());
    ui->side_menu_move->setFixedHeight(ui->side_menu->height());

    ui->widget->loop();
}

void MainWindow::on_btn_next_clicked(){
    city->move_to_next_turn();
}
void MainWindow::on_btn_save_game_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save file"));
    if(fileName != ""){
        city->save(fileName.toStdString());
    }
}
void MainWindow::on_btn_overlay_normal_clicked(){
    MainWindow::on_overlay_button_clicked(OverlayButton::NORMAL);
}
void MainWindow::on_btn_overlay_neighbor_clicked(){
    MainWindow::on_overlay_button_clicked(OverlayButton::NEIGHBOR);
}
void MainWindow::on_btn_overlay_type_clicked(){
    MainWindow::on_overlay_button_clicked(OverlayButton::TYPE);
}

void MainWindow::on_btn_clinic_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::CLINIC);
}
void MainWindow::on_btn_hospital_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::HOSPITAL);
}
void MainWindow::on_btn_gold_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::GOLD_MINE);
}
void MainWindow::on_btn_silver_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::SILVER_MINE);
}
void MainWindow::on_btn_house_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::HOUSE);
}
void MainWindow::on_btn_apartment_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::APARTMENT);
}
void MainWindow::on_btn_navigate_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
}
void MainWindow::on_btn_destruct_clicked(){
    MainWindow::on_side_menu_button_clicked(SideMenuButton::DEMOLISH);
}
