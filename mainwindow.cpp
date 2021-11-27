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
    ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
    ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
    // END OF YOUR IMPLEMENTATION
}

void MainWindow::initialize_overlay_buttons() {
    // START OF YOUR IMPLEMENTATION
    ui->btn_overlay_normal->setStyleSheet(BTN_SELECTED_STYLE);
    ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_overlay_road->setStyleSheet(BTN_RELEASED_STYLE);
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
        if(city->get_budget() < 10){
            //insufficient money
            MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
            break;
        }
        MainWindow::selected_side_menu_button = SideMenuButton::SILVER_MINE;
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
        if(city->get_budget() < 30){
            //insufficient money
            MainWindow::on_side_menu_button_clicked(SideMenuButton::NAVIGATE);
            break;
        }
        MainWindow::selected_side_menu_button = SideMenuButton::SILVER_MINE;
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


// This is called 50 times per second
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



void MainWindow::on_btn_next_clicked(){
    city->move_to_next_turn();
}
void MainWindow::on_btn_overlay_neighbor_clicked(){
    on_overlay_button_clicked(OverlayButton::NEIGHBOR);
    MainWindow::selected_overlay_button = OverlayButton::NEIGHBOR;
}
void MainWindow::on_btn_overlay_normal_clicked(){
    on_overlay_button_clicked(OverlayButton::NORMAL);
    MainWindow::selected_overlay_button = OverlayButton::NORMAL;
}
void MainWindow::on_btn_overlay_type_clicked(){
    on_overlay_button_clicked(OverlayButton::TYPE);
    MainWindow::selected_overlay_button = OverlayButton::TYPE;
}
void MainWindow::on_btn_overlay_road_clicked(){
    on_overlay_button_clicked(OverlayButton::ROAD);
    MainWindow::selected_overlay_button = OverlayButton::ROAD;
}
void MainWindow::on_btn_save_game_clicked(){
    QString filename = QFileDialog::getSaveFileName(this,tr("Save File"),"/home",tr("text files (*.txt)"));
    if(!filename.isEmpty()&& !filename.isNull()){
        std::string filenamestr = filename.toStdString();
        city->save(filenamestr);
    }
}

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
    MainWindow::on_side_menu_button_clicked(SideMenuButton::SILVER_MINE);;
}
