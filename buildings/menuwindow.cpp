#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "City.h"

#include <QPixmap>
#include <QFileDialog>

MenuWindow::MenuWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MenuWindow),
        selected_grid_size(20)
{
    ui->setupUi(this);

    // Scale label logo pixmap
    const QPixmap *p = ui->label_logo->pixmap();
    const int SCALE = 4;
    ui->label_logo->setPixmap(p->scaled(p->width() * SCALE, p->height() * SCALE));

    // Set pixmap for increase and decrease size buttons
    QPixmap increase {":/resources/images/next.png"};
    QPixmap decrease = increase.transformed(QTransform().rotate(180));
    ui->btn_increase_size->setIcon(increase);
    ui->btn_decrease_size->setIcon(decrease);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::start_game(City *city) {
    MainWindow *m = new MainWindow{city, nullptr};
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->show();

    close();
}

void MenuWindow::on_btn_new_clicked(){
    // go to page_size_selection
    ui->pages->setCurrentWidget(MenuWindow::ui->page_size_selection);
}
void MenuWindow::on_btn_load_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load file"));
    if(fileName != ""){
        City* city = new City(fileName.toStdString());
        MenuWindow::start_game(city);
    }
}
void MenuWindow::on_btn_increase_size_clicked(){
    if(selected_grid_size<=28){
        selected_grid_size += 2;
        MenuWindow::ui->label_grid_size->setText(QString::number(selected_grid_size));
    }
}
void MenuWindow::on_btn_decrease_size_clicked(){
    if(selected_grid_size>=12){
        selected_grid_size -= 2;
        MenuWindow::ui->label_grid_size->setText(QString::number(selected_grid_size));
    }
}
void MenuWindow::on_btn_start_game_clicked(){
    City* city = new City(selected_grid_size);
    MenuWindow::start_game(city);
}



