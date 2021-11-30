#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "City.h"

#include <QPixmap>
#include <QFileDialog>

/**
 * Constructor of Menu Window.
 *
 * Initializes its data members.
 * Sets up UI.
 * Configures the graphics for the logo and increase/decrease size button.
 *
 * @param parent Pointer to its parent widget
 */
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

/**
 * Destructor of the menu window.
 *
 * Deallocates the UI pointer.
 */
MenuWindow::~MenuWindow()
{
    delete ui;
}

/**
 * Starts the game after pressing the Start Game button.
 *
 * Closes the current menu window and opens the main window.
 *
 * @param city Pointer to the current city.
 */
void MenuWindow::start_game(City *city) {
    MainWindow *m = new MainWindow{city, nullptr};
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->show();

    close();
}

/**
 * Function that handles the click event of the New Game button
 *
 * Switches the stack widget so it lets the user to select the size of the city to be created.
 */
void MenuWindow::on_btn_new_clicked(){
    // go to page_size_selection
    ui->pages->setCurrentWidget(MenuWindow::ui->page_size_selection);
}
/**
 * Function that handles the click event of the Load Game button
 *
 * Opens a file dialog.
 * Loads game from the text file selected if the filename is valid.
 */
void MenuWindow::on_btn_load_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load file"));
    if(fileName != ""){
        City* city = new City(fileName.toStdString());
        MenuWindow::start_game(city);
    }
}
/**
 * Function that handles the click event of the Increase Grid Size button
 *
 * Increases the grid size by 2 until a maximum of 30.
 * Updates the label and data members accordingly.
 */
void MenuWindow::on_btn_increase_size_clicked(){
    if(selected_grid_size<=28){
        selected_grid_size += 2;
        MenuWindow::ui->label_grid_size->setText(QString::number(selected_grid_size));
    }
}
/**
 * Function that handles the click event of the Decrease Grid Size button
 *
 * Decreases the grid size by 2 until a maximum of 10.
 * Updates the label and data members accordingly.
 */
void MenuWindow::on_btn_decrease_size_clicked(){
    if(selected_grid_size>=12){
        selected_grid_size -= 2;
        MenuWindow::ui->label_grid_size->setText(QString::number(selected_grid_size));
    }
}
/**
 * Function that handles the click event of the Start Game button
 *
 * Creates a new city and calls the start game function.
 */
void MenuWindow::on_btn_start_game_clicked(){
    City* city = new City(selected_grid_size);
    MenuWindow::start_game(city);
}



